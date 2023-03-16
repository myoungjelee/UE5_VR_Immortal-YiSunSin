// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwordTrainingActor.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ASwordTrainingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASwordTrainingActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dummy")
	class UProceduralMeshComponent* proComp;


};
