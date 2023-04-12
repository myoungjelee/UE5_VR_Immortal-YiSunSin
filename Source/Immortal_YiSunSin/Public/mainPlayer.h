// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <HeadMountedDisplayTypes.h>
#include "mainPlayer.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AmainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AmainPlayer();

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

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class USkeletalMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* widgetInteractionL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* widgetInteractionR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* rightColl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* leftColl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AWidgetBtn* btn;

	//Input
	UPROPERTY(EditAnywhere)
		class UInputMappingContext* inputMapping;

	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* btnX;
		
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* btnB;

	UPROPERTY(EditAnywhere, Category = Inputs)
		FColor debugColor;

	//teleport
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* thumbstickR;
	
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* thumbstickL;

	UPROPERTY(EditAnywhere, Category = Inputs)
		float power = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UYiSunSinInstance* instance;

	UPROPERTY(EditAnywhere, Category = Effect)
		TSubclassOf<class ATeleportRingActor> teleport_fx;

	UPROPERTY(EditAnywhere, Category = Effect)
		class ATeleportRingActor* spawned_fx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
		class UNiagaraComponent* trace;

	bool bIsShowLine = false;
	TArray<FVector> lineLoc;

public:
	void Recenter();
	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);
	void Teleport();
	void DrawMoveLine();
	void ShowLine();
	void HideLine();
	void TeleportFade();
	void GamePause();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector startLoc;
};
