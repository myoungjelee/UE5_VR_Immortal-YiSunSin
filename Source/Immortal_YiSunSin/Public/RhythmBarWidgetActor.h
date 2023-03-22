// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RhythmBarWidgetActor.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ARhythmBarWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhythmBarWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
		class UWidgetComponent* compWidget;

	UPROPERTY(EditAnywhere)
		class URhythmBarWidget* gaugeUI;

// 	void ReceiveBlueScore(int32 score);
// 	void ReceiveRedScore(int32 score);

};
