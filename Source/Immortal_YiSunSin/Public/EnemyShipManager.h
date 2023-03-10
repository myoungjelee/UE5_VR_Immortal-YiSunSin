// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyShipManager.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AEnemyShipManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyShipManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	float spawnTime = 0;
	float currTime = 0;
	float minTime = 1;
	float maxTime = 5;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyShip> enemyFactory;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> spawnPosArray;
	UPROPERTY(EditAnywhere)
		TArray<class AEnemyShip*> enemyArray;

public:
	int32 spawnIdx = 0;
	void FindSpawnPos();

	UFUNCTION()
		void AddEnemy(class AEnemyShip* e);


};
