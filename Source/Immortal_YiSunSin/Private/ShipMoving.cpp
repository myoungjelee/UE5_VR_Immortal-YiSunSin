// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipMoving.h"
#include <Components/BoxComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Sound/SoundBase.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AShipMoving::AShipMoving()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(box);

	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	body->SetupAttachment(box);
	body->SetRelativeScale3D(FVector(0.3));

	paddle = CreateDefaultSubobject<UStaticMeshComponent>("Paddle");
	paddle->SetupAttachment(body);

	ConstructorHelpers::FObjectFinder<UStaticMesh>	tempBody(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/TurtleShip/SM_TurtleShip_Body.SM_TurtleShip_Body'"));
	if (tempBody.Succeeded())
	{
		body->SetStaticMesh(tempBody.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>	tempPaddle(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/TurtleShip/SM_TurtleShip_Paddle.SM_TurtleShip_Paddle'"));
	if (tempPaddle.Succeeded())
	{
		paddle->SetStaticMesh(tempPaddle.Object);
	}

	particle = CreateDefaultSubobject<UParticleSystemComponent>("FireParticle");
	particle->SetupAttachment(body, TEXT("Fire"));
	particle->SetRelativeLocation(FVector(0, 200, 0));
	particle->SetRelativeRotation(FRotator(0, 0, -90));
	particle->SetRelativeScale3D(FVector(5));
	particle->SetVisibility(false);

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempFire(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));
	if (tempFire.Succeeded())
	{
		particle->SetTemplate(tempFire.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Audios/MJ/firebreath.firebreath'"));
	if (tempSound.Succeeded())
	{
		fireSound = tempSound.Object;
	}
}


// Called when the game starts or when spawned
void AShipMoving::BeginPlay()
{
	Super::BeginPlay();

	loc = paddle->GetRelativeLocation();
	rot = GetActorRotation();

// 	bodyMove = true;
// 	paddleMove = true;
// 	fire = true;
}

// Called every frame
void AShipMoving::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bodyMove)
	{
		

		float roll = FMath::Sin(GetGameTimeSinceCreation()) * 5;
		FRotator moverot = FRotator(rot.Pitch, rot.Yaw, roll);
		SetActorRotation(moverot);

		// 현재 위치 저장
		FVector currLoc = GetActorLocation();
		
		// Z 값 변경 (범위 내에서 스무스하게)
		float posZ = FMath::Lerp(currLoc.Z, currLoc.Z + 5, FMath::Sin(GetGameTimeSinceCreation()));
		FVector TargetLocation = FVector(currLoc.X, currLoc.Y, posZ);

		// 위치 보간
		FVector bodyLoc = FMath::Lerp(currLoc, TargetLocation, DeltaTime * 5);

		// 액터 위치 갱신
		SetActorLocation(bodyLoc);
	}

	if (paddleMove)
	{
		

		// 2초 주기로 이동
		float moveTime = 2;
		currTime += DeltaTime;
		float posY = FMath::Sin(currTime / moveTime * 2 * PI) * 100;

		// 위치 변경
		FVector paddleLoc = loc + FVector(0, posY, 0);
		paddle->SetRelativeLocation(paddleLoc);
	}

	if (fire)
	{
		particle->SetVisibility(true);
		if(fireSoundComponent == nullptr)
		{
			fireSoundComponent = UGameplayStatics::SpawnSound2D(GetWorld(), fireSound);
		}
	}	
	else
	{
		particle->SetVisibility(false);
		if(fireSoundComponent != nullptr)
		{
			fireSoundComponent->Stop();
			fireSoundComponent = nullptr;
		}

	}
}

