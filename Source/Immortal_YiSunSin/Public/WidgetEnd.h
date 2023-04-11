// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetEnd.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AWidgetEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetEnd();

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
		class UWidgetComponent* widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float param;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AmainPlayer* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* infoSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* audio;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool open;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool end;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector startPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector endPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector leftPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 soundState;
};
