// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowActor.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AArrowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrowActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* projectileComp;

	bool bIsShoot = false;

	void Shoot();
	void OnTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
