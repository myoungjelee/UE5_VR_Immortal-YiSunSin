// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"
#include <UMG/Public/Components/TextBlock.h>
#include "MG4_Player.h"
#include "EnemyFSM.h"
#include <Kismet/GameplayStatics.h>

void UScoreUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	scoreBinding = Cast<UTextBlock>(GetWidgetFromName(TEXT("scoreBinding")));
}

void UScoreUI::UpdateScore(int32 point)
{
	score = point;
	FString playerScore = FString::Printf(TEXT("%d"), score);
	scoreBinding->SetText(FText::FromString(playerScore));
}
