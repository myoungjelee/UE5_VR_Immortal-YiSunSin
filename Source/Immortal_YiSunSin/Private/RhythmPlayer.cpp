// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmPlayer.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <HeadMountedDisplayFunctionLibrary.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>

// Sets default values
ARhythmPlayer::ARhythmPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	l_Controller = CreateDefaultSubobject<UMotionControllerComponent>("LeftController");
	l_Controller->SetupAttachment(RootComponent);
	l_Controller->MotionSource = "Left";

	l_Stick = CreateDefaultSubobject<USphereComponent>("LeftStick");
	l_Stick->SetupAttachment(l_Controller);
	l_Stick->SetSphereRadius(10);
	l_Stick->SetRelativeLocation(FVector(17, 0, -10));
	l_Stick->SetRelativeRotation(FRotator(-110, 0, 0));

	l_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftMesh");
	l_Mesh->SetupAttachment(l_Stick);
	l_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	l_Mesh->SetRelativeScale3D(FVector(0.1f));
	l_Mesh->SetRelativeLocation(FVector(0, 0, -17.5f));

	r_Controller = CreateDefaultSubobject<UMotionControllerComponent>("RightController");
	r_Controller->SetupAttachment(RootComponent);
	r_Controller->MotionSource = "Right";

	r_Stick = CreateDefaultSubobject<USphereComponent>("RightStick");
	r_Stick->SetupAttachment(r_Controller);
	r_Stick->SetSphereRadius(10);
	r_Stick->SetRelativeLocation(FVector(17, 0, -10));
	r_Stick->SetRelativeRotation(FRotator(-110, 0, 0));

	r_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RightMesh");
	r_Mesh->SetupAttachment(r_Stick);
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

// 	ConstructorHelpers::FObjectFinder<UParticleSystem> tempLeftHit(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/MJ/Drum/P_HitDrum_Left.P_HitDrum_Left'"));
// 	if (tempLeftHit.Succeeded())
// 	{
// 		hit_Left = tempLeftHit.Object;
// 	}
// 
// 	ConstructorHelpers::FObjectFinder<UParticleSystem> tempRightHit(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/MJ/Drum/P_HitDrum_Right.P_HitDrum_Right'"));
// 	if (tempRightHit.Succeeded())
// 	{
// 		hit_Right = tempRightHit.Object;
// 	}
}

// Called when the game starts or when spawned
void ARhythmPlayer::BeginPlay()
{
	Super::BeginPlay();

	l_Stick->OnComponentBeginOverlap.AddDynamic(this, &ARhythmPlayer::OnDrum_Left);
	r_Stick->OnComponentBeginOverlap.AddDynamic(this, &ARhythmPlayer::OnDrum_Right);

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(inputMapping, 4);
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

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(grip_Left, ETriggerEvent::Triggered, this, &ARhythmPlayer::Recenter);
	}
}

void ARhythmPlayer::OnDrum_Left(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Drum")))
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitHaptic, EControllerHand::Left, 1, false);

// 		//이펙트를 생성한다
// 		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hit_Left, GetActorLocation(), GetActorRotation(), FVector3d(0.5));
	}	
}

void ARhythmPlayer::OnDrum_Right(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Drum")))
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitHaptic, EControllerHand::Right, 1, false);

// 		//이펙트를 생성한다
// 		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hit_Right, GetActorLocation(), GetActorRotation(), FVector3d(0.5));
	}
}

void ARhythmPlayer::Recenter()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

