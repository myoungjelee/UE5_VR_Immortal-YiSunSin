// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBtn.h"
#include <Components/BoxComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "EasingLibrary.h"
#include "mainPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include "YiSunSinInstance.h"

// Sets default values
AWidgetBtn::AWidgetBtn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(box);
	box->SetBoxExtent(FVector(200));

	widget = CreateDefaultSubobject<UWidgetComponent>("Widget");
	widget->SetupAttachment(box);
	widget->SetVisibility(false);
	//widget->SetRelativeLocation(FVector(0, 0, 250));
	widget->SetCollisionProfileName(TEXT("interactionUI"));
	widget->SetRelativeLocation(FVector(200, 0, -120));
	widget->SetRelativeRotation(FRotator(0, 180, 0));
	widget->SetRelativeScale3D(FVector(0.2f));

}

// Called when the game starts or when spawned
void AWidgetBtn::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AmainPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AmainPlayer::StaticClass()));

	instance = Cast<UYiSunSinInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	box->OnComponentBeginOverlap.AddDynamic(this, &AWidgetBtn::BeginOverlap);
	box->OnComponentEndOverlap.AddDynamic(this, &AWidgetBtn::EndOverlap);
}

// Called every frame
void AWidgetBtn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 	if ((GetActorLocation() - player->GetActorLocation()).Length() <= 400)
	// 	{
	// 		
	// 	}
	// 	if ((GetActorLocation() - player->GetActorLocation()).Length() >= 450)
	// 	{
	// 		widget->SetVisibility(false);
	// 		near = false;
	// 		player->widgetInteractionL->bShowDebug = false;
	// 		player->widgetInteractionR->bShowDebug = false;
	// 	}
}

// void AWidgetBtn::NotifyActorBeginOverlap(AActor* OtherActor)
// {
// 	Super::NotifyActorBeginOverlap(OtherActor);
// 
// 	if (OtherActor->GetName().Contains(TEXT("Player")))
// 	{
// 	
// 	}
// }

// void AWidgetBtn::NotifyActorEndOverlap(AActor* OtherActor)
// {
// 	Super::NotifyActorEndOverlap(OtherActor);
// 
// 	if (OtherActor->GetName().Contains(TEXT("Player")))
// 	{
// 		widget->SetVisibility(false);
// 		near = false;
// 		player->widgetInteractionL->bShowDebug = false;
// 		player->widgetInteractionR->bShowDebug = false;
// 	}
// }

void AWidgetBtn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Contains(TEXT("Head")))
	{
		widget->SetVisibility(true);
		near = true;
		player->widgetInteractionL->bShowDebug = true;
		player->widgetInteractionR->bShowDebug = true;

		instance->pos = player->GetActorLocation();
		instance->rot = player->GetController()->GetControlRotation();
	}
}

void AWidgetBtn::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->GetName().Contains(TEXT("Head")))
	{
		widget->SetVisibility(false);
		near = false;
		player->widgetInteractionL->bShowDebug = false;
		player->widgetInteractionR->bShowDebug = false;
	}
}

