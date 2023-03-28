// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmTurtleShip.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "RhythmBarWidgetActor.h"
#include "RhythmBarWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <UMG/Public/Components/ProgressBar.h>
#include "DrumManager.h"

// Sets default values
ARhythmTurtleShip::ARhythmTurtleShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>("Root");
	SetRootComponent(compBox);

	bottom = CreateDefaultSubobject<UStaticMeshComponent>("Bottom");
	bottom->SetupAttachment(RootComponent);
	bottom->SetVisibility(false);

	top = CreateDefaultSubobject<UStaticMeshComponent>("Top");
	top->SetupAttachment(RootComponent);
	top->SetVisibility(false);

	head = CreateDefaultSubobject<UStaticMeshComponent>("Head");
	head->SetupAttachment(RootComponent);
	head->SetVisibility(false);

	sail = CreateDefaultSubobject<UStaticMeshComponent>("Sail");
	sail->SetupAttachment(RootComponent);
	sail->SetVisibility(false);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBottom(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/TurtleShip/SM_TurtleShip_Bottom.SM_TurtleShip_Bottom'"));
	if (tempBottom.Succeeded())
	{
		bottom->SetStaticMesh(tempBottom.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempTop(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/TurtleShip/SM_TurtleShip_Top.SM_TurtleShip_Top'"));
	if (tempTop.Succeeded())
	{
		top->SetStaticMesh(tempTop.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempHead(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/TurtleShip/SM_TurtleShip_Head.SM_TurtleShip_Head'"));
	if (tempHead.Succeeded())
	{
		head->SetStaticMesh(tempHead.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempSail(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/TurtleShip/SM_TurtleShip_Sail.SM_TurtleShip_Sail'"));
	if (tempSail.Succeeded())
	{
		sail->SetStaticMesh(tempSail.Object);
	}
}

// Called when the game starts or when spawned
void ARhythmTurtleShip::BeginPlay()
{
	Super::BeginPlay();
	
	widgetActor = Cast<ARhythmBarWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ARhythmBarWidgetActor::StaticClass()));
	gaugeWidget = Cast<URhythmBarWidget>(widgetActor->compWidget->GetUserWidgetObject());
	manager = Cast<ADrumManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADrumManager::StaticClass()));
	
	curr = 0;
}

// Called every frame
void ARhythmTurtleShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	a += DeltaTime * 8;
	SetActorRotation(FRotator(0, 90 + a, 0));

	gaugeWidget->UpdateGauge(curr, max);

	if (gaugeWidget->gaugeBar->GetPercent() >= 1)
	{
		sail->SetVisibility(true);
		bComplete = true;
		a = 0;
		gaugeWidget->gaugeBar->SetFillColorAndOpacity(FLinearColor::Blue);
	}
	else if (gaugeWidget->gaugeBar->GetPercent() > 0.8f)
	{
		head->SetVisibility(true);
	}
	else if (gaugeWidget->gaugeBar->GetPercent() > 0.5f)
	{
		top->SetVisibility(true);
	}
	else if (gaugeWidget->gaugeBar->GetPercent() > 0.25f)
	{
		bottom->SetVisibility(true);
	}

	if (manager->bEnd)
	{
		if (bComplete)
		{
			if (GetActorLocation().X > 2500)
			{
				FVector p0 = GetActorLocation();
				FVector vt = FVector::BackwardVector * 500 * DeltaTime;
				SetActorLocation(p0 + vt);
			}


// 			FTimerHandle WaitHandle;
// 			float WaitTime = 5; //시간을 설정하고
// 			GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
// 				{
// 					//GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black,false,true);
// 					//UE_LOG(LogTemp, Warning, TEXT("Fade!!!"));
// 
// 
// 					OpenMainLevel();
// 				}), WaitTime, false);
			

			FTimerHandle fadelTimer;
			GetWorld()->GetTimerManager().SetTimer(fadelTimer, this, &ARhythmTurtleShip::CameraFade, 5.0f, false);

			FTimerHandle levelTimer;
			GetWorld()->GetTimerManager().SetTimer(levelTimer, this, &ARhythmTurtleShip::OpenMainLevel, 6.0f, false);

		}

	}
}

void ARhythmTurtleShip::CameraFade()
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black);
}

void ARhythmTurtleShip::OpenMainLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"));
}

