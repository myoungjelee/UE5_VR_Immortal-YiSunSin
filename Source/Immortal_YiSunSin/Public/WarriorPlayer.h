// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "WarriorPlayer.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AWarriorPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AWarriorPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UCameraComponent* cam;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UStaticMeshComponent* headMesh;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UInputMappingContext* myMapping;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|ModuleSetting")
	TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* rightThumbstick;

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* leftThumbstick;

public:

	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);

};
