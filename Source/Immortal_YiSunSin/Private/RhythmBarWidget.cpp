// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmBarWidget.h"
#include <UMG/Public/Components/ProgressBar.h>

void URhythmBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//gaugeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Gauge")));

}

void URhythmBarWidget::UpdateGauge(float curr, float max)
{
	float guage = curr / max;

	gaugeBar->SetPercent(guage);
}
