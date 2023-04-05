// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoviePlayerActor.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AMoviePlayerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMoviePlayerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterial* mediaMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMediaPlayer* mediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMediaSource* mediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* plane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMediaSoundComponent* mediaSound;

public:

	UFUNCTION(BlueprintCallable)
		void OpenMovie();
	UFUNCTION(BlueprintCallable)
		void PlayMovie();
	UFUNCTION(BlueprintCallable)
		void PausedMovie();
	UFUNCTION(BlueprintCallable)
		void OnMediaPlayerEndReached();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bEnd = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float currTime = 0;
};
