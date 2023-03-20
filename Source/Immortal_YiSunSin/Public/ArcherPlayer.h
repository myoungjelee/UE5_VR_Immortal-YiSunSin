// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ArcherPlayer.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AArcherPlayer : public APawn
{
	GENERATED_BODY()

public:
	AArcherPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UCapsuleComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UCameraComponent* cam;

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

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class USkeletalMeshComponent* bowComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Components")
	class UStaticMeshComponent* handleMesh;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* GripRight;

	UPROPERTY(EditAnywhere, Category = "ArrowSpawn")
	class AArrowActor* arrow;

	UPROPERTY(EditAnywhere, Category = "ArrowSpawn")
	TSubclassOf<class AArrowActor> arrowFactory;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UInputAction* thumbstickLeft;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
class UInputAction* thumbstickRight;

	FVector startLoc;
	FVector handLoc;
	FVector tempLoc;
	bool bBowPulling = false;

	void BowRelease();
	void ShootArrow();
	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);
};
