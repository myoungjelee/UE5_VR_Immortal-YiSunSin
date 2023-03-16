// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowTargetActor.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AArrowTargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrowTargetActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
};
