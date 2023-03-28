// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumManager.h"
#include "DrumActor.h"
#include "RhythmPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <MotionControllerComponent.h>

// Sets default values
ADrumManager::ADrumManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TArray<FVector> startPos = { FVector(2000, -60, 75), FVector(2000, -30, 125), FVector(2000, 30, 125), FVector(2000, 60, 75) };
	//FVector startPos[NODE_MAX] = { FVector(2000, -40, 150), FVector(2000, -20, 150), FVector(2000, 20, 150), FVector(2000, 40, 150) };

	for (int32 i = 0; i < nodeMax; i++)
	{
		FNodeCreateInfo info;
		FString path = FString::Printf(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/Drums/BP_Drum%d.BP_Drum%d_C'"), i, i);

		ConstructorHelpers::FClassFinder<ADrumActor> tempDrum(*path);
		if (tempDrum.Succeeded())
		{
			info.drumActor = tempDrum.Class;
			info.pos = startPos[i];
			nodeCreateArray.Add(info);
		}
	}

	/*ConstructorHelpers::FClassFinder<ADrumActor> tempDrum0(TEXT("/Script/Engine.Blueprint'/Game/MJ_Blueprint/Rhythm/Drums/BP_Drum0.BP_Drum0_C'"));
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
	}*/


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

	//시간 = 거리/속력
	FVector hitPos = player->GetActorLocation() + FVector(100, 0, 0);
	delayTime = (FVector(2000, 0, 0).X - hitPos.X) / 500;
	if (currTime > nodeArray[nodeIndex].makeTime - delayTime)
	{
		CreateNode();
		if (nodeIndex < 84)
		{
			nodeIndex++;
		}
		else
		{
			nodeArray[nodeIndex].makeTime = 1000;

			FTimerHandle WaitHandle;
			float WaitTime = 4; //시간을 설정하고
			GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
				{
					bEnd = true;
				}), WaitTime, false);
		}
	}
}

void ADrumManager::CreateNode()
{
	int32 type = nodeArray[nodeIndex].type;
	GetWorld()->SpawnActor<ADrumActor>(nodeCreateArray[type].drumActor, player->GetActorLocation() + nodeCreateArray[type].pos, GetActorRotation());

	/*if (nodeArray[nodeIndex].type == 0)
	{
		GetWorld()->SpawnActor<ADrumActor>(drumFactory0, player->GetActorLocation() + FVector(2000, -40, 150), GetActorRotation());
	}
	else if (nodeArray[nodeIndex].type == 1)
	{
		GetWorld()->SpawnActor<ADrumActor>(drumFactory1, player->GetActorLocation() + FVector(2000, -20, 150), GetActorRotation());
	}
	else if (nodeArray[nodeIndex].type == 2)
	{
		GetWorld()->SpawnActor<ADrumActor>(drumFactory2, player->GetActorLocation() + FVector(2000, 20, 150), GetActorRotation());
	}
	else if (nodeArray[nodeIndex].type == 3)
	{
		GetWorld()->SpawnActor<ADrumActor>(drumFactory3, player->GetActorLocation() + FVector(2000, 40, 150), GetActorRotation());
	}*/
}

void ADrumManager::LoadNode()
{
	FString jsonString;
	FString filePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Node.txt"));
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

	// 	for (int32 i = 0; i < nodeArray.Num(); i++)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("%d : %d , %f"), i, nodeArray[i].type, nodeArray[i].makeTime);
	// 	}
}

