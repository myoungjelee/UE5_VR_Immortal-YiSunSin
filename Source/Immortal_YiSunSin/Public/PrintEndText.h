// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PrintEndText.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API UPrintEndText : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTextBlock* text;

	FString sampleText;

	float currTime;

	float showTime = 0.06f;

	int32 index = 1;
	
};
