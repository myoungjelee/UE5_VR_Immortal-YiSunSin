// Fill out your copyright notice in the Description page of Project Settings.


#include "GameResultWidget.h"
#include <UMG/Public/Components/TextBlock.h>

void UGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	scoreResult = Cast<UTextBlock>(GetWidgetFromName(TEXT("scoreResult")));

}

void UGameResultWidget::SetScore(int32 point)
{
	FString resultScore = FString::Printf(TEXT("%d"), point);
	scoreResult->SetText(FText::FromString(resultScore));
}
