// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintEndText.h"
#include <UMG/Public/Components/TextBlock.h>

void UPrintEndText::NativeConstruct()
{
	Super::NativeConstruct();

	text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_0")));

	sampleText = TEXT("충무공 이순신에 대하여 배우는 유익한 시간이 되셨나요?  \n  다음에도 다른 전시로 만나뵙길 바랍니다 ^^");

}


void UPrintEndText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	currTime += InDeltaTime;
	if (index <= sampleText.Len() && currTime > showTime)
	{
		currTime = 0;

		text->SetText(FText::FromString(sampleText.Mid(0, index)));
		index++;
	}
}