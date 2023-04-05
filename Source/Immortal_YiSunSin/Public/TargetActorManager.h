// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActorManager.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ATargetActorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetActorManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AArrowTargetActor> targetFactory;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> spawnPosArray;

	UPROPERTY(EditAnywhere)
	TArray<class AArrowTargetActor*> targetArray;

	UPROPERTY(EditAnywhere)
	class AArcherPlayer* player;

	float currTime = 0;
	float spawnTime = 5.0f;
	int32 spawnIdx = 0;
	void FindSpawnPos();

	UFUNCTION()
	void AddTarget(class AArrowTargetActor* a);

};
