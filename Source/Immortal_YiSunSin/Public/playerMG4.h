// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBase.h"
#include "playerMG4.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API AplayerMG4 : public APlayerBase
{
	GENERATED_BODY()
	
	/*void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) ;*/
	
	/*UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* trigger_left;

	UPROPERTY(EditAnywhere, Category = Inputs)
		class UInputAction* trigger_right;*/

	void TriggerRightAction(const struct FInputActionValue& value);
	void TriggerRightReleased(const struct FInputActionValue& value);
	void TriggerLeftAction(const struct FInputActionValue& value);
	void TriggerLeftReleased(const struct FInputActionValue& value);
};
