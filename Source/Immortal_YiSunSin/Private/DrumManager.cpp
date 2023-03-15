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

	
	ConstructorHelpers::FClassFinder<ADrumActor> tempDrum0(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/Drums/BP_Drum0.BP_Drum0_C'"));
	if (tempDrum0.Succeeded())
	{
		drumFactory0 = tempDrum0.Class;
	}

	ConstructorHelpers::FClassFinder<ADrumActor> tempDrum1(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/Drums/BP_Drum1.BP_Drum1_C'"));
	if (tempDrum1.Succeeded())
	{
		drumFactory1 = tempDrum1.Class;
	}

	ConstructorHelpers::FClassFinder<ADrumActor> tempDrum2(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/Drums/BP_Drum2.BP_Drum2_C'"));
	if (tempDrum2.Succeeded())
	{
		drumFactory2 = tempDrum2.Class;
	}

	ConstructorHelpers::FClassFinder<ADrumActor> tempDrum3(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/Drums/BP_Drum3.BP_Drum3_C'"));
	if (tempDrum3.Succeeded())
	{
		drumFactory3 = tempDrum3.Class;
	}
}

// Called when the game starts or when spawned
void ADrumManager::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<ARhythmPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARhythmPlayer::StaticClass()));

	LoadNode();
}

// Called every frame
void ADrumManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currTime += DeltaTime;

	for (int32 i = 0; i < nodeArray.Num(); i++)
	{
		makeTime = nodeArray[i].makeTime;
			if (currTime > makeTime - 3.5f)
			{
				
					if (nodeArray[i].type == 0)
					{
						GetWorld()->SpawnActor<ADrumActor>(drumFactory0, player->GetActorLocation() + FVector(2000, -40, 150), GetActorRotation());
						UE_LOG(LogTemp, Warning ,TEXT("%d"), i);
					}
					else if (nodeArray[i].type == 1)
					{
						GetWorld()->SpawnActor<ADrumActor>(drumFactory1, player->GetActorLocation() + FVector(2000, -20, 150), GetActorRotation());
						UE_LOG(LogTemp, Error, TEXT("%d"), i);
					}
					else if (nodeArray[i].type == 2)
					{
						GetWorld()->SpawnActor<ADrumActor>(drumFactory2, player->GetActorLocation() + FVector(2000, 20, 150), GetActorRotation());
						UE_LOG(LogTemp, Log, TEXT("%d"), i);
					}
					else if (nodeArray[i].type == 3)
					{
						GetWorld()->SpawnActor<ADrumActor>(drumFactory3, player->GetActorLocation() + FVector(2000, 40, 150), GetActorRotation());
						UE_LOG(LogTemp, Warning, TEXT("%d"), i);
					}
				
			}
	}
}

void ADrumManager::LoadNode()
{
	FString jsonString;
	FString filePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Node.txt"));
	FFileHelper::LoadFileToString(jsonString, *filePath);
	//UE_LOG(LogTemp, Warning, TEXT("jsonString : %s"), *jsonString);

	TArray<TSharedPtr<FJsonValue>> jsonArray;
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	FJsonSerializer::Deserialize(jsonReader, jsonArray);
	for (int32 i = 0; i < jsonArray.Num(); i++)
	{
		FNodeInfo info;
		info.type = jsonArray[i]->AsObject()->GetIntegerField("type");
		info.makeTime = jsonArray[i]->AsObject()->GetNumberField("time");

		nodeArray.Add(info);
	}

	for (int32 i = 0; i < nodeArray.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %d , %f"), i, nodeArray[i].type, nodeArray[i].makeTime);
	}
}

