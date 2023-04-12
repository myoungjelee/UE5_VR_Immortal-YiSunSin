// Fill out your copyright notice in the Description page of Project Settings.


#include "OpeningPlayer.h"

// Sets default values
AOpeningPlayer::AOpeningPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	headMesh->SetupAttachment(cam);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	controllerLeft = CreateDefaultSubobject<UMotionControllerComponent>("Left Controller");
	controllerLeft->SetupAttachment(RootComponent);
	controllerLeft->MotionSource = "Left";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(controllerLeft);
	leftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	controllerRight = CreateDefaultSubobject<UMotionControllerComponent>("Right Controller");
	controllerRight->SetupAttachment(RootComponent);
	controllerRight->MotionSource = "Right";

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(controllerRight);
	rightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void AOpeningPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOpeningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOpeningPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOpeningPlayer::Recenter()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AOpeningPlayer::Move(const struct FInputActionValue& value)
{
	FVector2D val = value.Get<FVector2D>();
	FVector direction = FVector(val.Y, val.X, 0);

	AddMovementInput(direction.GetSafeNormal(), 1, false);
}

void AOpeningPlayer::RotateAxis(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	//axis 값을 이용해서 캐릭터(콘트롤러)를 회전한다.
	AddControllerYawInput(axis.X);
	AddControllerPitchInput(axis.Y * -1.0f);
}

