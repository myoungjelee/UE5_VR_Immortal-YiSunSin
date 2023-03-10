// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "BowActor.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API ABowActor : public APickupActor
{
	GENERATED_BODY()
	
public:
	ABowActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* bowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* handleMesh;

	void ShootArrow();
};
