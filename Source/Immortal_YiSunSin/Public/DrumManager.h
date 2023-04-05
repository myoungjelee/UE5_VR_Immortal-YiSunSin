// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrumManager.generated.h"

USTRUCT(BlueprintType)
struct FNodeInfo
{
	GENERATED_BODY()

public:
	//0 : q, 1 : w, 2 : e, 3 :r
	UPROPERTY()
		int32 type = 0;

	UPROPERTY()
		float makeTime = 0;
};

USTRUCT(BlueprintType)
struct FNodeCreateInfo
{
	GENERATED_BODY()

public:
	//0 : q, 1 : w, 2 : e, 3 :r
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADrumActor> drumActor;

	UPROPERTY(EditAnywhere)
		FVector pos = FVector(0);
};



UCLASS()
class IMMORTAL_YISUNSIN_API ADrumManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrumManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
		class ARhythmPlayer* player;

	UPROPERTY(EditAnywhere)
		class ADrumActor* drum;


public:

	float currTime = 0;

	TArray<FNodeInfo> nodeArray;
	UPROPERTY(EditAnywhere)
		TArray<FNodeCreateInfo> nodeCreateArray;

	float makeTime = 0;

	float delayTime;

	int32 spawnDrum = 0;

	int32 nodeIndex = 0;

	int32 nodeMax = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bEnd = false;

public:

	void LoadNode();
	void CreateNode();
};
