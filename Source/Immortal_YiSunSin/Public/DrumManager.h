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
		int32 type;

	UPROPERTY()
		float makeTime;
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
		TSubclassOf<class ADrumActor> drumFactory0;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADrumActor> drumFactory1;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADrumActor> drumFactory2;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ADrumActor> drumFactory3;

public:

	float currTime = 0;

	TArray<FNodeInfo> nodeArray;

	float makeTime = 0;

	int32 spawnDrum = 0;


public:

	void LoadNode();
};
