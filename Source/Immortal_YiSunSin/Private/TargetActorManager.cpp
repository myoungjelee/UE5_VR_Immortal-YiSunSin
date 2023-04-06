// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActorManager.h"
#include <Kismet/GameplayStatics.h>
#include "ArrowTargetActor.h"
#include "ArcherPlayer.h"
#include <Kismet/KismetMathLibrary.h>

ATargetActorManager::ATargetActorManager()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AArrowTargetActor> tempTarget(TEXT("/Script/Engine.Blueprint'/Game/SC/Blueprints/BP_ArrowTarget.BP_ArrowTarget_C'"));
	if (tempTarget.Succeeded())
	{
		targetFactory = tempTarget.Class;
	}
}

void ATargetActorManager::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AArcherPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AArcherPlayer::StaticClass()));

	FindSpawnPos();

	for (int32 i = 0; i < 18; i++)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AArrowTargetActor* a = GetWorld()->SpawnActor<AArrowTargetActor>(targetFactory, GetActorLocation(), GetActorRotation(), param);
		a->targetHit.BindUObject(this, &ATargetActorManager::AddTarget);
		a->SetActive(false);
	}
}

void ATargetActorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (targetArray.Num() == 0)
	{
		return;
	}
	currTime += DeltaTime;
	if (currTime > spawnTime)
	{
		AActor* spawn = spawnPosArray[spawnIdx];

		float yaw = FMath::RandRange(0.0f, 360.0f);
		spawn->SetActorRotation(FRotator(0, yaw, 0));
		float length = FMath::RandRange(150.0f, 500.0f);
		FVector pos = spawn->GetActorForwardVector() * length;

		FVector dir = player->GetActorLocation() - (spawn->GetActorLocation() + pos);
		float dotValue = FVector::DotProduct(targetArray[0]->GetActorRightVector(), dir.GetSafeNormal());
		float angle = UKismetMathLibrary::DegAcos(dotValue);

		targetArray[0]->SetActorLocation(spawn->GetActorLocation() + pos);
		targetArray[0]->SetActorRotation(FRotator(0, angle, 0));
		targetArray[0]->SetActive(true);
		targetArray.RemoveAt(0);

		spawnIdx++;
		spawnIdx = spawnIdx % spawnPosArray.Num();

		currTime = 0;
	}
}

void ATargetActorManager::FindSpawnPos()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), actors);

	for (int32 i = 0; i < actors.Num(); i++)
	{
		if (actors[i]->GetName().Contains(TEXT("Spawnpos")))
		{
			spawnPosArray.Add(actors[i]);
		}
	}
}

void ATargetActorManager::AddTarget(class AArrowTargetActor* a)
{
	targetArray.Add(a);
}

