// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetPointerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class IMMORTAL_YISUNSIN_API UWidgetPointerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWidgetPointerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);


	UPROPERTY(EditAnywhere)
		class UInputAction* left_Grib;

	UPROPERTY(EditAnywhere)
		class UInputAction* right_Grib;

	UPROPERTY(EditAnywhere)
		class UInputAction* x_Btn;

	UPROPERTY(EditAnywhere)
		class UInputAction* left_Trigger;

	UPROPERTY(EditAnywhere)
		class UInputAction* right_Trigger;

	UPROPERTY(EditAnywhere)
		TArray<class APutPuzzle*> putArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMoviePlayerActor* moviePlayer;

	class APuzzlePlayer* player;
	class AActor* grabedPuzzle_L;
	class AActor* grabedPuzzle_R;
	class AActor* hitPuzzle_L;
	class AActor* hitPuzzle_R;

	bool hit_L = false;
	FVector startLoc_L;
	FVector endLoc_L;
	FHitResult hitInfo_L;
	FCollisionQueryParams params_L;

	bool hit_R = false;
	FVector startLoc_R;
	FVector endLoc_R;
	FHitResult hitInfo_R;
	FCollisionQueryParams params_R;

	bool bPut_L = false;
	bool bPut_R = false;

	void GribedPuzzle_L();
	void ReleasedPuzzle_L();
	void GribedPuzzle_R();
	void ReleasedPuzzle_R();
	void GamePause();
	void ClickWidget_L();
	void ReleaseWidget_L();
	void ClickWidget_R();
	void ReleaseWidget_R();
};
