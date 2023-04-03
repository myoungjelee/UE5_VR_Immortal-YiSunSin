// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <GameFramework/PlayerController.h>
#include "ArrowActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>
#include "ScoreUI.h"
#include "GameResultWidget.h"

AArcherPlayer::AArcherPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	cam->SetupAttachment(RootComponent);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	leftController->MotionSource = "Left";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftHand->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f));

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->MotionSource = "Right";

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	rightHand->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f));

	bowComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bow Mesh"));
	bowComp->SetupAttachment(leftHand);
	bowComp->SetRelativeLocation(FVector(0, 2.2, -3.84));
	bowComp->SetRelativeRotation(FRotator(0, -90, 0));

	handleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle Mesh"));
	handleMesh->SetupAttachment(bowComp);
	handleMesh->SetRelativeLocation(FVector(14.5, 0, 0.12));
	handleMesh->SetRelativeRotation(FRotator(0, 180, 0));
	handleMesh->SetRelativeScale3D(FVector(0.05));

	widgetInt = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Interaction"));
	widgetInt->SetupAttachment(rightController);

	pauseUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Pause UI"));
	pauseUI->SetupAttachment(RootComponent);
	pauseUI->SetRelativeLocation(FVector(765, 0, 300));
	pauseUI->SetWorldRotation(FRotator(0, 180, 0));

	scoreUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Score UI"));
	scoreUI->SetupAttachment(RootComponent);
	scoreUI->SetRelativeLocation(FVector(1200, 0, 0));
	scoreUI->SetRelativeRotation(FRotator(0, 180, 0));

	resultUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Result UI"));
	resultUI->SetupAttachment(RootComponent);
	resultUI->SetRelativeLocation(FVector(765, 0, 300));
	resultUI->SetRelativeRotation(FRotator(0, 180, 0));

	gameoverUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Gameover UI"));
	gameoverUI->SetupAttachment(RootComponent);
	gameoverUI->SetRelativeLocation(FVector(765, 0, 300));
	gameoverUI->SetRelativeRotation(FRotator(0, 180, 0));
}

void AArcherPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(myMapping, 0);

	score = Cast<UScoreUI>(scoreUI->GetUserWidgetObject());
	result = Cast<UGameResultWidget>(resultUI->GetUserWidgetObject());

	if (widgetInt != nullptr)
	{
		widgetInt->InteractionDistance = 100000.0f;
		widgetInt->bEnableHitTesting = true;
		widgetInt->DebugColor = FColor::Red;
		widgetInt->bShowDebug = false;
	}

	handleMesh->SetVisibility(false);
	resultUI->SetVisibility(false);
	gameoverUI->SetVisibility(false);
	startLoc = handleMesh->GetComponentLocation();
	tempLoc = handleMesh->GetRelativeLocation();

}

void AArcherPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector temp = rightHand->GetComponentLocation() - startLoc;
	handLoc = rightHand->GetComponentLocation();


	if (temp.Length() < 120 && temp.Length() > 70)
	{
		if (bBowPulling == true)
		{
			handleMesh->SetWorldLocation(handLoc);
			arrow->SetActorLocation(handleMesh->GetComponentLocation() + arrow->GetActorForwardVector() * 40);
			arrow->SetActorRotation(handleMesh->GetComponentRotation());
		}
	}

	FindWidget();

	if (shootCnt >= 3)
	{
		if (score->score > 10)
		{
			// 게임을 일시중지하고 UI를 띄운다.
			result->SetScore(score->score);
			resultUI->SetVisibility(true);
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
			widgetInt->bShowDebug = true;
		}
		else
		{
			gameoverUI->SetVisibility(true);
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
			widgetInt->bShowDebug = true;
		}
	}
}

void AArcherPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(GripRight, ETriggerEvent::Started, this, &AArcherPlayer::BowRelease);
		enhancedInputComponent->BindAction(GripRight, ETriggerEvent::Completed, this, &AArcherPlayer::ShootArrow);
		enhancedInputComponent->BindAction(triggerRight, ETriggerEvent::Started, this, &AArcherPlayer::PressWidget);
		enhancedInputComponent->BindAction(triggerRight, ETriggerEvent::Completed, this, &AArcherPlayer::ReleaseWidget);
		enhancedInputComponent->BindAction(thumbstickLeft, ETriggerEvent::Triggered, this, &AArcherPlayer::Move);
		enhancedInputComponent->BindAction(thumbstickRight, ETriggerEvent::Triggered, this, &AArcherPlayer::RotateAxis);
		enhancedInputComponent->BindAction(btnX, ETriggerEvent::Started, this, &AArcherPlayer::PauseUIOpen);
	}
}

void AArcherPlayer::BowRelease()
{
	bBowPulling = true;

	// 화살 스폰 --
	FVector shootLoc = handleMesh->GetComponentLocation();
	FRotator shootRot = handleMesh->GetComponentRotation();
	arrow = Cast<AArrowActor>(GetWorld()->SpawnActor<AArrowActor>(arrowFactory, shootLoc, shootRot));
	arrow->projectileComp->SetActive(!bBowPulling);
}

void AArcherPlayer::ShootArrow()
{
	bBowPulling = false;
	handleMesh->SetRelativeLocation(tempLoc);

	arrow->Shoot();
	UGameplayStatics::PlaySound2D(GetWorld(), bowRelease);
}

void AArcherPlayer::PressWidget()
{
	widgetInt->PressPointerKey(EKeys::LeftMouseButton);
}

void AArcherPlayer::ReleaseWidget()
{
	widgetInt->bShowDebug = false;
	widgetInt->ReleasePointerKey(EKeys::LeftMouseButton);
}

void AArcherPlayer::Move(const struct FInputActionValue& value)
{
	FVector2D val = value.Get<FVector2D>();
	FVector direction = FVector(val.Y, val.X, 0);

	AddMovementInput(direction.GetSafeNormal(), 1, false);
}

void AArcherPlayer::RotateAxis(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	//axis 값을 이용해서 캐릭터(콘트롤러)를 회전한다.
	AddControllerPitchInput(axis.Y * -1.0f);
	AddControllerYawInput(axis.X);
}

void AArcherPlayer::FindWidget()
{
	FVector start = widgetInt->GetComponentLocation();
	FVector endLoc = start + widgetInt->GetForwardVector() * 10000.0f;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	//DrawDebugLine(GetWorld(), start, endLoc, FColor::Cyan, false, -1, 0, 2);

	if (GetWorld()->LineTraceSingleByChannel(hitInfo, start, endLoc, ECC_Visibility, params))
	{
		if (hitInfo.GetActor()->GetName().Contains(TEXT("UI")))
		{
			widgetInt->bShowDebug = true;
		}
	}
}

void AArcherPlayer::PauseUIOpen()
{
	pauseUI->SetVisibility(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
	widgetInt->bShowDebug = true;
}
