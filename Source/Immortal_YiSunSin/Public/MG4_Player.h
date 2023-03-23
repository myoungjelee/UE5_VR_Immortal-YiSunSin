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
		class UStaticMeshComponent* cannon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* controllerLeft;

	UPROPERTY(EditAnywhere)
		class UMotionControllerComponent* controllerRight;

	//Input
	UPROPERTY(EditAnywhere, Category = Inputs)
		FColor debugColor;

	UPROPERTY(EditAnywhere)
		class UInputMappingContext* inputMapping;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class USkeletalMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = "VR_Setting|Components")
		class USkeletalMeshComponent* rightHand;
	
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* thumbstickLeft;
		
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* thumbstickRight;

	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* btnA;
	
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* btnX;

	//cannon
	UPROPERTY(EditAnywhere)
		class UParticleSystem* exploEffect;
		
	UPROPERTY(EditAnywhere)
		class UUserWidgetBlueprint* PauseUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyFSM* fsm;

	UPROPERTY(EditAnywhere, Category = Inputs)
		float reachDistance = 100000;

	/*UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* gripLeft;
	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* gripRight;
	UPROPERTY(EditAnywhere, Category = Inputs)
		float grabDistance = 30.0f;
	class AActor* grabbedObject_R;
	class AActor* grabbedObject_L;
	class AActor* grabedObject;
	bool bIsGrab = false;*/
	
private:
	bool physicsState = false;
	FRotator lockRot;

public:
	void Recenter();
	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);
	void LaserPoint();
	void APressed();
	void AReleased();
	void InputFire(bool bFire);
	void OpenWidget();
	
	/*void TriggerRightAction(const struct FInputActionValue& value);
	void TriggerRightReleased(const struct FInputActionValue& value);
	void TriggerLeftAction(const struct FInputActionValue& value);
	void TriggerLeftReleased(const struct FInputActionValue& value);*/

	/*void GripRightAction(const struct FInputActionValue& value);
	void GripRightReleased(const struct FInputActionValue& value);
	void GripLeftAction(const struct FInputActionValue& value);
	void GripLeftReleased(const struct FInputActionValue& value);
	void GrabObject(USkeletalMeshComponent* selectHand);*/

};
