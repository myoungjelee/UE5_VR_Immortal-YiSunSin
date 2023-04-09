// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "Components/CapsuleComponent.h"
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



// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

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

	widgetInt_L = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Left Widget Interaction"));
	widgetInt_L->SetupAttachment(leftController);
	widgetInt_L->SetRelativeRotation(FRotator(0, -60, 0));

	widgetInt_R = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Interaction"));
	widgetInt_R->SetupAttachment(rightController);
	widgetInt_R->SetRelativeRotation(FRotator(0, -60, 0));

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(myMapping, 0);

	if (widgetInt_L != nullptr)
	{
		widgetInt_L->InteractionDistance = 100000.0f;
		widgetInt_L->bEnableHitTesting = true;
		widgetInt_L->DebugColor = FColor::Red;
		widgetInt_L->bShowDebug = true;
	}

	if (widgetInt_R != nullptr)
	{
		widgetInt_R->InteractionDistance = 100000.0f;
		widgetInt_R->bEnableHitTesting = true;
		widgetInt_R->DebugColor = FColor::Red;
		widgetInt_R->bShowDebug = true;
	}
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(triggerRight, ETriggerEvent::Started, this, &APlayerBase::PressWidget_L);
		enhancedInputComponent->BindAction(triggerRight, ETriggerEvent::Completed, this, &APlayerBase::ReleaseWidget_L);
		enhancedInputComponent->BindAction(triggerLeft, ETriggerEvent::Started, this, &APlayerBase::PressWidget_R);
		enhancedInputComponent->BindAction(triggerLeft, ETriggerEvent::Completed, this, &APlayerBase::ReleaseWidget_R);
	}	
}

void APlayerBase::PressWidget_L()
{
	widgetInt_L->PressPointerKey(EKeys::LeftMouseButton);
}

void APlayerBase::ReleaseWidget_L()
{
	//widgetInt->bShowDebug = false;
	widgetInt_L->ReleasePointerKey(EKeys::LeftMouseButton);
}

void APlayerBase::PressWidget_R()
{
	widgetInt_R->PressPointerKey(EKeys::LeftMouseButton);
}

void APlayerBase::ReleaseWidget_R()
{
	//widgetInt->bShowDebug = false;
	widgetInt_R->ReleasePointerKey(EKeys::LeftMouseButton);
}
