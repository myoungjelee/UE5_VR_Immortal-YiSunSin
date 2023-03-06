// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GraspComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_YISUNSIN_API UGraspComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGraspComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* grip_left;

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* grip_right;

	UPROPERTY(EditAnywhere, Category = Inputs)
	float grabDistance = 30.0f;

private:
	class APlayerBase* player;
	class APickupActor* grabedObject;
	bool bIsGrab = false;
	bool physicsState = false;

	void GripRightAction(const struct FInputActionValue& value);
	void GripRightReleased(const struct FInputActionValue& value);
	void GripLeftAction(const struct FInputActionValue& value);
	void GripLeftReleased(const struct FInputActionValue& value);
	void GrabObject(USkeletalMeshComponent* selectHand);
	void ReleaseObject(USkeletalMeshComponent* selectHand);
};
