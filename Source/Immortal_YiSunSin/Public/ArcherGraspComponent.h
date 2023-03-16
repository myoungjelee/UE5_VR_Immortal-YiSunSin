// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArcherGraspComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_YISUNSIN_API UArcherGraspComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UArcherGraspComponent();

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
	float grabDistance = 15.0f;

private:
	class APlayerBase* player;
	class APickupActor* grabedObject;
	class ABowActor* bow;
	class ASwordActor* sword;
	class UStaticMeshComponent* grabedComp;

	bool bIsGrab = false;
	bool physicsState = false;
	bool bBowGrab = false;

	void GripRightAction(const struct FInputActionValue& value);
	void GripRightReleased(const struct FInputActionValue& value);
	void GrabObject(USkeletalMeshComponent* selectHand);
	void ReleaseObject(USkeletalMeshComponent* selectHand);
};
