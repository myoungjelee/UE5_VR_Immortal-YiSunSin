// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Buttons.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AButtons : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtons();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* btn1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* btn2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* btn3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* bottom1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* bottom2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* bottom3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* box1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* box2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* box3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AmainPlayer* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AShipMoving* ship;

public:

	UFUNCTION()
		void BeginOverlapBtn1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BeginOverlapBtn2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BeginOverlapBtn3(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		void ReturnBtn();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector pos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator rot;
	
};
