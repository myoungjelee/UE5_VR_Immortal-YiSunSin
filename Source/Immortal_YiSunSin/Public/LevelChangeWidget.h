// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelChangeWidget.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API ULevelChangeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnChange;

	UPROPERTY()
	class UTextBlock* changeLevel;

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void ChangeLevel();

};
