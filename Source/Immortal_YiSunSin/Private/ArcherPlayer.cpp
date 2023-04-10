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
#include "EasingLibrary.h"
#include "MoviePlayerActor.h"
#include <LevelSequence/Public/LevelSequence.h>

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
	widgetInt->SetRelativeRotation(FRotator(-45, 0, 0));

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

	timerUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Timer UI"));
	timerUI->SetupAttachment(RootComponent);
	timerUI->SetRelativeLocation(FVector(1200, 0, 0));
	timerUI->SetRelativeRotation(FRotator(0, 180, 0));
	timerUI->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	movies = Cast<AMoviePlayerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMoviePlayerActor::StaticClass()));

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
	FVector handleLoc = handleMesh->GetComponentLocation();


	if (temp.Length() < 120 && temp.Length() > 70)
	{
		if (bBowPulling == true)
		{
			handleMesh->SetWorldLocation(FVector(handLoc.X, handleLoc.Y, handleLoc.Z));
			/*arrow->SetActorLocation(handleMesh->GetComponentLocation() + arrow->GetActorForwardVector() * 40);*/
			arrow->SetActorLocation(FVector(handleMesh->GetComponentLocation().X + 40, bowComp->GetComponentLocation().Y + 3, bowComp->GetComponentLocation().Z));
			arrow->SetActorRotation(handleMesh->GetComponentRotation());
		}
	}

	FindWidget();

	if (bIsShowLine)
	{
		DrawMoveLine();
	}

	if (score->score == 1)
	{
		movies->plane->SetVisibility(true);
		if (movieplays == 2)
		{
			movies->OpenMovie();
			UE_LOG(LogTemp, Warning, TEXT("111111111111"));
			movieplays = 3;
		}
		if (movieplays == 0)
		{
			FTimerHandle movieTimer;
			GetWorld()->GetTimerManager().SetTimer(movieTimer, this, &AArcherPlayer::CheckMovie, 1.0f, false);
			movieplays = 2;
		}
		if (movies->currTime >= 2.0f)
		{
			FTimerHandle levelTimer;
			GetWorld()->GetTimerManager().SetTimer(levelTimer, this, &AArcherPlayer::OpenMainLevel, 2.0f, false);
			movies->currTime = 0;
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
	bIsShowLine = true;
	// 화살 스폰 --
	FVector shootLoc = handleMesh->GetComponentLocation();
	FRotator shootRot = handleMesh->GetComponentRotation();
	arrow = Cast<AArrowActor>(GetWorld()->SpawnActor<AArrowActor>(arrowFactory, shootLoc, shootRot));
	arrow->projectileComp->SetActive(!bBowPulling);
}

void AArcherPlayer::ShootArrow()
{
	bBowPulling = false;
	bIsShowLine = false;
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
	movies->PausedMovie();
	widgetInt->bShowDebug = true;
}

void AArcherPlayer::DrawMoveLine()
{
	float timeInterval = 0.02f;
	int32 timeSegment = 50;

	FVector handForward = arrow->GetActorForwardVector();// FRotationMatrix(testActor->GetComponentRotation()).GetUnitAxis(EAxis::Y);
	FVector handUp = FVector(0,0,1);// FRotationMatrix(testActor->GetComponentRotation()).GetUnitAxis(EAxis::X) * -1;

	FVector dir = handForward ;

	lineLoc.Empty();
	for (int32 i = 0; i < timeSegment; i++)
	{
		float timeTaken = timeInterval * i;
		FVector prediction = (arrow->GetActorLocation() + arrow->GetActorForwardVector() * 40) + dir.GetSafeNormal() * arrow->projectileComp->InitialSpeed * timeTaken;

		prediction.Z += 0.5f * GetWorld()->GetDefaultGravityZ() * timeTaken * timeTaken;

		lineLoc.Add(prediction);
	}

	for (int32 i = 0; i < lineLoc.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), lineLoc[i], lineLoc[i + 1], FColor::Red, false, -1, 0, 2);
	}

}

void AArcherPlayer::CheckMovie()
{
	movieplays = 2;
}

void AArcherPlayer::OpenMainLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gallery"));
}
