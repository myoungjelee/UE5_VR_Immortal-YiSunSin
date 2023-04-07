// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBtn.h"
#include <Components/BoxComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "EasingLibrary.h"
#include "mainPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>

// Sets default values
AWidgetBtn::AWidgetBtn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(box);

	widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	widget->SetupAttachment(box);
	widget->SetVisibility(false);
	//widget->SetRelativeLocation(FVector(0, 0, 250));
	widget->SetCollisionProfileName(TEXT("interactionUI"));

}

// Called when the game starts or when spawned
void AWidgetBtn::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AmainPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AmainPlayer::StaticClass()));
}

// Called every frame
void AWidgetBtn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((GetActorLocation() - player->GetActorLocation()).Length() <= 400)
	{
		widget->SetVisibility(true);
		near = true;
		player->widgetInteractionL->bShowDebug = true;
		player->widgetInteractionR->bShowDebug = true;
	}
	if ((GetActorLocation() - player->GetActorLocation()).Length() >= 450)
	{
		widget->SetVisibility(false);
		near = false;
		player->widgetInteractionL->bShowDebug = false;
		player->widgetInteractionR->bShowDebug = false;
	}
}

