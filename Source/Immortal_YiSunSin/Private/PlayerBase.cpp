// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GraspComponent.h"
#include "MoveComponent.h"
#include "Components/TextRenderComponent.h"
#include "ArcherGraspComponent.h"



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

	// 디버그용 로그
	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log Text"));
	leftLog->SetupAttachment(leftController);
	leftLog->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	leftLog->SetTextRenderColor(FColor::Yellow);
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);

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

	// 액터 컴포넌트
/*	graspComp = CreateDefaultSubobject<UGraspComponent>(TEXT("Grasp Component"));*/
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("Move Component"));

}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(myMapping, 0);
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
/*		graspComp->SetupPlayerInputComponent(enhancedInputComponent);*/
		moveComp->SetupPlayerInputComponent(enhancedInputComponent);
	}

	
}
