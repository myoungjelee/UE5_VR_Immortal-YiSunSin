// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUI.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API UScoreUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* scoreBinding;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 score;

	UFUNCTION()
	void UpdateScore(int32 point);
};
