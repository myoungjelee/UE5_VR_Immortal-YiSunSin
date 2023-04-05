// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmBarWidgetActor.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Blueprint/UserWidget.h>
#include "RhythmBarWidget.h"

// Sets default values
ARhythmBarWidgetActor::ARhythmBarWidgetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));

	ConstructorHelpers::FClassFinder<UUserWidget>UserWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MJ_Blueprint/Rhythm/BP_GaugeBar.BP_GaugeBar_C'"));
	if (UserWidget.Succeeded())
	{
		compWidget->SetWidgetClass(UserWidget.Class);
		compWidget->SetDrawSize(FVector2D(100.0f, 500.0f));
	}
}

// Called when the game starts or when spawned
void ARhythmBarWidgetActor::BeginPlay()
{
	Super::BeginPlay();

	gaugeUI = Cast<URhythmBarWidget>(compWidget->GetUserWidgetObject());
}

// Called every frame
void ARhythmBarWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

