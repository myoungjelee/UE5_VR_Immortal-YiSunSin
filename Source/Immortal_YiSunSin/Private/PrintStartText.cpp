// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintStartText.h"
#include <UMG/Public/Components/TextBlock.h>

void UPrintStartText::NativeConstruct()
{
	Super::NativeConstruct();

	text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_271")));

	sampleText = TEXT("충무공 이순신 VR 전시관에 오신 여러분을 환영합니다.  \n  전시를 둘러보시는데에 어려움이 없도록 조작 법에  \n 대하여 알아보겠습니다. 우측 하단 버튼을 눌러보세요.");

}


void UPrintStartText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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