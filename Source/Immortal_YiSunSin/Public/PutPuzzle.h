// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PutPuzzle.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API APutPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APutPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;

	UPROPERTY(EditAnywhere)
		class AActor* overlapPuzzle;

	UPROPERTY(EditAnywhere)
		class AActor* setPuzzle;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* completePuzzle;
public:

	bool hit = false;
	FVector startLoc;
	FVector endLoc;
	FHitResult hitInfo;
	//FCollisionQueryParams params;

public:

	UFUNCTION()
		void OnPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		void SettingPuzzle();
};
