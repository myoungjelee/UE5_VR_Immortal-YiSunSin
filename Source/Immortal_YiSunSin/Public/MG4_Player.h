// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <HeadMountedDisplayTypes.h>
#include "MG4_Player.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AMG4_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMG4_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;
	
	UPROPERTY(EditAnywhere)
		class UCameraComponent* cam;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class UStaticMeshComponent* headMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* controllerLeft;

	UPROPERTY(EditAnywhere)
		class UMotionControllerComponent* controllerRight;

	UPROPERTY(EditAnywhere)
		class UInputMappingContext* inputMapping;

	//Grip Input

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* gripLeft;

	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* gripRight;

	UPROPERTY(EditAnywhere, Category = Inputs)
		float grabDistance = 30.0f;

private:
	class APickupActor* grabedObject;
	bool bIsGrab = false;
	bool physicsState = false;

	void GripRightAction(const struct FInputActionValue& value);
	void GripRightReleased(const struct FInputActionValue& value);
	void GripLeftAction(const struct FInputActionValue& value);
	void GripLeftReleased(const struct FInputActionValue& value);
	void GrabObject(USkeletalMeshComponent* selectHand);

	/*void TriggerRightAction(const struct FInputActionValue& value);
	void TriggerRightReleased(const struct FInputActionValue& value);
	void TriggerLeftAction(const struct FInputActionValue& value);
	void TriggerLeftReleased(const struct FInputActionValue& value);*/

};
