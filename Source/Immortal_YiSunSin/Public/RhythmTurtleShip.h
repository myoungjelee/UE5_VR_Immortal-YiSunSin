// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RhythmTurtleShip.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ARhythmTurtleShip : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARhythmTurtleShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* compBox;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* bottom;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* head;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* top;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* sail;

	UPROPERTY(EditAnywhere)
		class ARhythmBarWidgetActor* widgetActor;

	UPROPERTY(EditAnywhere)
		class URhythmBarWidget* gaugeWidget;

	UPROPERTY(EditAnywhere)
		class ADrumManager* manager;

	UPROPERTY(EditAnywhere)
		class ALevelSequenceActor* levelSequence;

		UPROPERTY(EditAnywhere)
		class ARhythmPlayer* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMoviePlayerActor* moviePlayer;

	UPROPERTY(EditAnywhere)
	bool bComplete = false;
	UPROPERTY(EditAnywhere)
	float a = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float max = 68;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float curr;

	void FadeOut();
	void OpenMainLevel();
	void GameOver();
	void OpenMovie();

};
