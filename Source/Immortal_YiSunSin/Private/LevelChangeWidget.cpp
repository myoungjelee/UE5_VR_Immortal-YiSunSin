// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelChangeWidget.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Components/Button.h>
#include <UMG/Public/Components/TextBlock.h>

void ULevelChangeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	changeLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("_changeLevel")));
	
	BtnChange->OnClicked.AddDynamic(this, &ULevelChangeWidget::OnClick);
}

void ULevelChangeWidget::OnClick()
{
	if (GetWorld()->GetName().Contains(TEXT("Archery")))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("WarriorLevel"));
	}
	else if (GetWorld()->GetName().Contains(TEXT("Warrior")))
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("ArcheryLevel"));
	}
}

void ULevelChangeWidget::ChangeLevel()
{
	if (GetWorld()->GetName().Contains(TEXT("Archery")))
	{
		FString currLevel = FString::Printf(TEXT("검술 시험으로"));
		changeLevel->SetText(FText::FromString(currLevel));
	}
	else if (GetWorld()->GetName().Contains(TEXT("Warrior")))
	{
		FString currLevel = FString::Printf(TEXT("궁술 시험으로"));
		changeLevel->SetText(FText::FromString(currLevel));
	}
}
