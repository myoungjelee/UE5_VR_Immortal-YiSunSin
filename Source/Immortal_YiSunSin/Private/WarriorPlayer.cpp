// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MoveComponent.h"
#include "Components/TextRenderComponent.h"
#include "ArcherGraspComponent.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

AWarriorPlayer::AWarriorPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	cam->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	headMesh->SetupAttachment(cam);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	// 디버그용 로그
	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log Text"));
	rightLog->SetupAttachment(rightController);
	rightLog->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	rightLog->SetTextRenderColor(FColor::Yellow);
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);

	widgetInt = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Interaction"));
	widgetInt->SetupAttachment(leftController);
	widgetInt->SetRelativeRotation(FRotator(0, -60, 0));

	pauseUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("Pause UI"));
	pauseUI->SetupAttachment(RootComponent);
	pauseUI->SetRelativeLocation(FVector(765, 0, 300));
	pauseUI->SetWorldRotation(FRotator(0, 180, 0));

	// 액터 컴포넌트
	graspComp = CreateDefaultSubobject<UArcherGraspComponent>(TEXT("Grasp Component"));

	bUseControllerRotationPitch = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

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
}

void AWarriorPlayer::BeginPlay()
{
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(myMapping, 0);

	if (widgetInt != nullptr)
	{
		widgetInt->InteractionDistance = 100000.0f;
		widgetInt->bEnableHitTesting = true;
		widgetInt->DebugColor = FColor::Red;
		widgetInt->bShowDebug = true;
	}
	
}

void AWarriorPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindWidget();
}

void AWarriorPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		graspComp->SetupPlayerInputComponent(enhancedInputComponent);
		enhancedInputComponent->BindAction(triggerRight, ETriggerEvent::Started, this, &AWarriorPlayer::PressWidget);
		enhancedInputComponent->BindAction(triggerRight, ETriggerEvent::Completed, this, &AWarriorPlayer::ReleaseWidget);
		enhancedInputComponent->BindAction(btnX, ETriggerEvent::Started, this, &AWarriorPlayer::PauseUIOpen);
		//enhancedInputComponent->BindAction(rightThumbstick, ETriggerEvent::Triggered, this, &AWarriorPlayer::RotateAxis);
		//enhancedInputComponent->BindAction(leftThumbstick, ETriggerEvent::Triggered, this, &AWarriorPlayer::Move);
	}
}

void AWarriorPlayer::PressWidget()
{
	widgetInt->PressPointerKey(EKeys::LeftMouseButton);
}

void AWarriorPlayer::ReleaseWidget()
{
	//widgetInt->bShowDebug = false;
	widgetInt->ReleasePointerKey(EKeys::LeftMouseButton);
}

void AWarriorPlayer::FindWidget()
{
	FVector start = widgetInt->GetComponentLocation();
	FVector endLoc = start + widgetInt->GetForwardVector() * 10000.0f;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	//DrawDebugLine(GetWorld(), start, endLoc, FColor::Cyan, false, -1, 0, 2);

	if (GetWorld()->LineTraceSingleByChannel(hitInfo, start, endLoc, ECC_Visibility, params))
	{
		if (hitInfo.GetComponent()->GetName().Contains(TEXT("UI")))
		{
			widgetInt->bShowDebug = true;
		}
	}
}

void AWarriorPlayer::PauseUIOpen()
{
	pauseUI->SetVisibility(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
	widgetInt->bShowDebug = true;
}

void AWarriorPlayer::Move(const FInputActionValue& value)
{
	FVector2D val = value.Get<FVector2D>();
	FVector direction = FVector(val.Y, val.X, 0);

	AddMovementInput(direction.GetSafeNormal(), 1, false);
}

// 플레이어 회전
void AWarriorPlayer::RotateAxis(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	AddControllerYawInput(axis.X);
}