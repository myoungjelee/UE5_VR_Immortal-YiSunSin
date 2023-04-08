// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetStart.h"
#include <Components/BoxComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "EasingLibrary.h"
#include "mainPlayer.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AWidgetStart::AWidgetStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(box);

	widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	widget->SetupAttachment(box);
	widget->SetVisibility(false);
	widget->SetRelativeLocation(FVector(0,0,250));
	widget->SetCollisionProfileName(TEXT("interactionUI"));

}

// Called when the game starts or when spawned
void AWidgetStart::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AmainPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AmainPlayer::StaticClass()));

	startPos = GetActorLocation();
	endPos = GetActorLocation() + GetActorUpVector()*-100;
}

// Called every frame
void AWidgetStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((GetActorLocation() - player->GetActorLocation()).Length() >= 450)
	{
		widget->SetVisibility(false);
	}
	
	if (open)
	{
		widget->SetVisibility(true);
		//widget->SetCollisionProfileName(TEXT("interactionUI"));

		currTime += DeltaTime;
		param = FMath::Clamp(currTime * 1.8f, 0, 1);
		float easy = UEasingLibrary::BounceEaseOut(param);
		
		FVector newLoc = FMath::Lerp(endPos, startPos, easy);

		SetActorLocation(newLoc);

		if (param == 1)
		{
			currTime = 0;
			open = false;
		}
	}
}

