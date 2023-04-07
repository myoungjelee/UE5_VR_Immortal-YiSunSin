// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetStart.h"
#include <Components/BoxComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "EasingLibrary.h"

// Sets default values
AWidgetStart::AWidgetStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(box);

	widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	widget->SetupAttachment(box);
}

// Called when the game starts or when spawned
void AWidgetStart::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWidgetStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




}

