// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrumManager.generated.h"

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
		TSubclassOf<class ADrumActor> drumFactory;


	float currTime = 0;

	float makeTime = 2;

};
