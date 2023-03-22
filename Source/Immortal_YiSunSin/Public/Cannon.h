// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere, Category = Inputs)
		float grabDistance = 100000;
	UPROPERTY(EditAnywhere, Category = Inputs)
		FColor debugColor;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* exploEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyFSM* fsm;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
 
 void LaserPoint();

 UFUNCTION(BlueprintCallable)
 void InputFire();

};