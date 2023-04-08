// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipMoving.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AShipMoving : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipMoving();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* paddle;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator rot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bodyMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool paddleMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector loc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currTime;

};
