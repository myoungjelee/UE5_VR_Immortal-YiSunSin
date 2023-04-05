// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RhythmBarWidget.generated.h"

/**
 *
 */
UCLASS()
class IMMORTAL_YISUNSIN_API URhythmBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* gaugeBar;

	void UpdateGauge(float curr, float max);
};
