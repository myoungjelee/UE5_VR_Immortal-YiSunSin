// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetPointerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
		class UInputAction* right_Trigger;

	UPROPERTY(EditAnywhere)
		class UInputAction* left_Trigger;
		

	class APuzzlePlayer* player;

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

	void TriggedPuzzle_L();
	void ReleasedPuzzle_L();
	void TriggedPuzzle_R();
	void ReleasedPuzzle_R();
};
