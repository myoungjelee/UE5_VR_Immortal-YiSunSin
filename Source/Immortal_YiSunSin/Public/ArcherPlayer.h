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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Components")
	class USkeletalMeshComponent* bowComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Components")
	class UStaticMeshComponent* handleMesh;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* GripRight;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* triggerRight;

	UPROPERTY(EditAnywhere, Category = "ArrowSpawn")
	class AArrowActor* arrow;

	UPROPERTY(EditAnywhere, Category = "ArrowSpawn")
	TSubclassOf<class AArrowActor> arrowFactory;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* thumbstickLeft;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
	class UInputAction* thumbstickRight;

 	UPROPERTY(EditAnywhere, Category = "VR_Setting|Input")
 	class UInputAction* btnX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Components")
	class UWidgetInteractionComponent* widgetInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* pauseUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* scoreUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* gameoverUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Widget")
	class UWidgetComponent* timerUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	class UScoreUI* score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Sound")
	class USoundBase* bowRelease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR_Setting|Sound")
	class USoundBase* bowPull;

	UPROPERTY(EditAnywhere)
	class AMoviePlayerActor* movies;

	FVector startLoc;
	FVector handLoc;
	FVector tempLoc;
	bool bBowPulling = false;
	int32 shootCnt = 0;

	int32 movieplays = 0;

	bool bIsShowLine = false;
	TArray<FVector> lineLoc;

	void BowRelease();
	void ShootArrow();
	void PressWidget();
	void ReleaseWidget();
	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);
	void FindWidget();
	void PauseUIOpen();
	void DrawMoveLine();

	void CheckMovie();
	void OpenMainLevel();
};
