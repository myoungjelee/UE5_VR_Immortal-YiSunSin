// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumManager.h"
#include "DrumActor.h"
#include "RhythmPlayer.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADrumManager::ADrumManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<ADrumActor> tempDrum(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/BP_Drum.BP_Drum_C'"));
	if (tempDrum.Succeeded())
	{
		drumFactory = tempDrum.Class;
	}
}

// Called when the game starts or when spawned
void ADrumManager::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<ARhythmPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARhythmPlayer::StaticClass()));
}

// Called every frame
void ADrumManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currTime += DeltaTime;

	if (currTime > makeTime)
	{
		float randY = FMath::RandRange(-80,80);
		float randZ = FMath::RandRange(0,50);
		GetWorld()->SpawnActor<ADrumActor>(drumFactory, player->GetActorLocation() + FVector(2000, randY, randZ), GetActorRotation());

		currTime = 0;
	}
	/*if (currTime == JsonArrayTime)
	{
		if (JsonArrayType == 1)
		{
			GetWorld()->SpawnActor<ADrumActor>(drumFactory, player->GetActorLocation()+FVector(2000,-40,150), GetActorRotation());
		}
		else if(JsonArrayType == 2)
		{
			GetWorld()->SpawnActor<ADrumActor>(drumFactory, player->GetActorLocation() + FVector(2000, -20, 150), GetActorRotation());
		}
		else if (JsonArrayType == 3)
		{
			GetWorld()->SpawnActor<ADrumActor>(drumFactory, player->GetActorLocation() + FVector(2000, 20, 150), GetActorRotation());
		}
		else if (JsonArrayType == 4)
		{
			GetWorld()->SpawnActor<ADrumActor>(drumFactory, player->GetActorLocation() + FVector(2000, 40, 150), GetActorRotation());
		}
	}*/
	
}

