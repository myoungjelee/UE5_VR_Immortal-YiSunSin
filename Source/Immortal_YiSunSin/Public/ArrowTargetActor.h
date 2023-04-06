// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArrowTargetActor.generated.h"

DECLARE_DELEGATE_OneParam(FHitTarget, class AArrowTargetActor*);

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
	class UStaticMeshComponent* bracket;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring1;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring2;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring3;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring4;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring5;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring6;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring7;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring8;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring9;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ring10;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* hit;

	UPROPERTY(EditAnywhere)
	class AArcherPlayer* player;

	UPROPERTY(EditAnywhere)
	class UScoreUI* scoreUI;

	UPROPERTY()
	class AArrowActor* arrow;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* hitTarget;

	TArray<UStaticMeshComponent*> rings;

	int32 point = 0;
	float setTime = 0;
	FHitTarget targetHit;
	bool bSpawn = false;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool IsShoot(AActor* OtherActor, UPrimitiveComponent* OtherComp);

	void SetActive(bool bActive);
	void SetDisable(float time);
};
