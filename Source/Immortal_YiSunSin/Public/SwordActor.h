// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "SwordActor.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API ASwordActor : public APickupActor
{
	GENERATED_BODY()
	
public:
	ASwordActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* planeComp;
};
