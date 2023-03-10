// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlayer.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "GraspComponent.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include <GameFramework/PlayerController.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include "WidgetPointerComponent.h"

// Sets default values
APuzzlePlayer::APuzzlePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	controller_Left = CreateDefaultSubobject<UMotionControllerComponent>("Left Controller");
	controller_Left->SetupAttachment(RootComponent);
	controller_Left->MotionSource = "Left";

	mesh_Left = CreateDefaultSubobject<USkeletalMeshComponent>("Left Hand");
	mesh_Left->SetupAttachment(controller_Left);
	mesh_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh_Left->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f));

	widgetPointer_Left = CreateDefaultSubobject<UWidgetInteractionComponent>("Left Pointer");
	widgetPointer_Left->SetupAttachment(controller_Left);
	widgetPointer_Left->InteractionDistance = 2000;
	widgetPointer_Left->bShowDebug = true;
	widgetPointer_Left->DebugColor = FColor::Red;
	widgetPointer_Left->SetRelativeRotation(FRotator(-45,0,0));

	controller_Right = CreateDefaultSubobject<UMotionControllerComponent>("Right Controller");
	controller_Right->SetupAttachment(RootComponent);
	controller_Right->MotionSource = "Right";

	mesh_Right = CreateDefaultSubobject<USkeletalMeshComponent>("Right Hand");
	mesh_Right->SetupAttachment(controller_Right);
	mesh_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh_Right->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f));

	widgetPointer_Right = CreateDefaultSubobject<UWidgetInteractionComponent>("Right Pointer");
	widgetPointer_Right->SetupAttachment(controller_Right);
	widgetPointer_Right->InteractionDistance = 2000;
	widgetPointer_Right->bShowDebug = true;
	widgetPointer_Right->DebugColor = FColor::Red;
	widgetPointer_Right->SetRelativeRotation(FRotator(-45, 0, 0));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	graspComp = CreateDefaultSubobject<UGraspComponent>("Grasp Component");
	widgetPointerComp = CreateDefaultSubobject<UWidgetPointerComponent>("Pointer Component");
}

// Called when the game starts or when spawned
void APuzzlePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(inputMapping, 0);
}

// Called every frame
void APuzzlePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzlePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		graspComp->SetupPlayerInputComponent(enhancedInputComponent);
		widgetPointerComp->SetupPlayerInputComponent(enhancedInputComponent);
	}
}

