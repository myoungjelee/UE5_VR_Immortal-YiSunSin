// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OpeningPlayer.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API AOpeningPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOpeningPlayer();

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
	
	UPROPERTY(EditAnywhere, Category = Inputs)
		float reachDistance = 100000;

	
private:
	bool physicsState = false;
	FRotator lockRot;

public:
	void Recenter();
	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);

};
