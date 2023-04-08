// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetStart.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AWidgetStart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetStart();

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

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool open;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector startPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector endPos;
};
