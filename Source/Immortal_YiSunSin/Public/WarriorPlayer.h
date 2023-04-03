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

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
	class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
	class UTextRenderComponent* rightLog;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UInputMappingContext* myMapping;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|ModuleSetting")
	TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
	class UArcherGraspComponent* graspComp;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
	class UWidgetInteractionComponent* widgetInt;

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* rightThumbstick;

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* leftThumbstick;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* triggerRight;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* btnX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* pauseUI;
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* gameoverUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* resultUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* timerUI;

public:
	void PressWidget();
	void ReleaseWidget();
	void FindWidget();
	void PauseUIOpen();

	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);

};
