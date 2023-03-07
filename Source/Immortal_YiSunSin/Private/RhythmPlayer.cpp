// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmPlayer.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ARhythmPlayer::ARhythmPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	l_Controller = CreateDefaultSubobject<UMotionControllerComponent>("LeftController");
	l_Controller->SetupAttachment(RootComponent);

	l_Stick = CreateDefaultSubobject<USphereComponent>("LeftStick");
	l_Stick->SetupAttachment(l_Controller);
	l_Stick->SetSphereRadius(10);

	l_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftMesh");
	l_Mesh->SetupAttachment(l_Controller);
	l_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	l_Mesh->SetRelativeScale3D(FVector(0.1f));
	l_Mesh->SetRelativeLocation(FVector(0, 0, -17.5f));

	r_Controller = CreateDefaultSubobject<UMotionControllerComponent>("RightController");
	r_Controller->SetupAttachment(RootComponent);

	r_Stick = CreateDefaultSubobject<USphereComponent>("RightStick");
	r_Stick->SetupAttachment(r_Controller);
	r_Stick->SetSphereRadius(10);

	r_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RightMesh");
	r_Mesh->SetupAttachment(r_Controller);
	r_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	r_Mesh->SetRelativeScale3D(FVector(0.1f));
	r_Mesh->SetRelativeLocation(FVector(0, 0, -17.5f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> leftMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Drum/SM_DrumStick.SM_DrumStick'"));
	if (leftMesh.Succeeded())
	{
		l_Mesh->SetStaticMesh(leftMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> rightMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Drum/SM_DrumStick.SM_DrumStick'"));
	if (rightMesh.Succeeded())
	{
		r_Mesh->SetStaticMesh(rightMesh.Object);
	}
}

// Called when the game starts or when spawned
void ARhythmPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARhythmPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARhythmPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

