// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrumActor.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ADrumActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrumActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = Drum)
		class USphereComponent* compDrum;

	UPROPERTY(EditAnywhere, Category = Drum)
		class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere, Category = Drum)
		FLinearColor keyColor;

	UPROPERTY(EditAnywhere, Category = Drum)
		float glowPower;

	UPROPERTY(EditAnywhere)
		float drumSpeed = 500;

	class UMaterialInstanceDynamic* keyMat;
	FTimerHandle colorHandle;

	UFUNCTION()
		void OnDrum(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		class UParticleSystem* drumEffect;

	UPROPERTY(EditAnywhere)
		class ARhythmTurtleShip* turtleShip;

};
