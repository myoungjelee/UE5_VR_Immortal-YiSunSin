// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <HeadMountedDisplayTypes.h>
#include "PuzzlePlayer.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API APuzzlePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuzzlePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: 

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMotionControllerComponent* controller_Left;

	UPROPERTY(EditAnywhere)
	class UMotionControllerComponent* controller_Right;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* mesh_Left;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* mesh_Right;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* inputMapping;

	UPROPERTY(EditAnywhere)
	class UWidgetInteractionComponent* widgetPointer_Left;

	UPROPERTY(EditAnywhere)
	class UWidgetInteractionComponent* widgetPointer_Right;

	UPROPERTY(EditAnywhere)
	class UWidgetPointerComponent* widgetPointerComp;
};
