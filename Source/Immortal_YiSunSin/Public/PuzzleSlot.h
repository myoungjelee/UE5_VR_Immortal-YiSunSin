// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSlot.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API APuzzleSlot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuzzleSlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector end;

	UPROPERTY(EditAnywhere)
		int32 idx;
};
