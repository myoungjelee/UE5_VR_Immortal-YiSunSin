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
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequence.h>
#include <MovieScene/Public/MovieSceneSequencePlayer.h>
#include "RhythmPlayer.h"
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include "MoviePlayerActor.h"

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
	levelSequence = Cast<ALevelSequenceActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelSequenceActor::StaticClass()));
	player = Cast<ARhythmPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ARhythmPlayer::StaticClass()));
	moviePlayer = Cast<AMoviePlayerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMoviePlayerActor::StaticClass()));

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
			if (GetActorLocation().X > 6500)
			{
				FVector p0 = GetActorLocation();
				FVector vt = FVector::BackwardVector * 2500 * DeltaTime;
				SetActorLocation(p0 + vt);
			}

			FTimerHandle movieTimer;
			GetWorld()->GetTimerManager().SetTimer(movieTimer, this, &ARhythmTurtleShip::PlayMovie, 4.0f, false);
			
			FTimerHandle fadeTimer;
			GetWorld()->GetTimerManager().SetTimer(fadeTimer, this, &ARhythmTurtleShip::FadeOut, 26.0f, false);

			FTimerHandle levelTimer;
			GetWorld()->GetTimerManager().SetTimer(levelTimer, this, &ARhythmTurtleShip::OpenMainLevel, 26.5f, false);
		}
		else
		{
			FTimerHandle gameOverTimer;
			GetWorld()->GetTimerManager().SetTimer(gameOverTimer, this, &ARhythmTurtleShip::GameOver, 3.0f, false);
		}
	}
}

void ARhythmTurtleShip::FadeOut()
{
	//GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 2.0f, FLinearColor::Black);
	ULevelSequence* endSequence = LoadObject<ULevelSequence>(nullptr, TEXT("/Script/LevelSequence.LevelSequence'/Game/Sequence/EndLevelSequence.EndLevelSequence'"));
 	levelSequence->SetSequence(endSequence);
 	levelSequence->GetSequencePlayer()->Play();
}

void ARhythmTurtleShip::OpenMainLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"));
}

void ARhythmTurtleShip::GameOver()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
	player->widgetPointer_Left->bShowDebug = true;
	player->widgetPointer_Right->bShowDebug = true;
	player->gameOverWidget->SetVisibility(true);
	player->gameOverWidget->SetCollisionProfileName(TEXT("interactionUI"));
}

void ARhythmTurtleShip::PlayMovie()
{
	moviePlayer->plane->SetVisibility(true);
	moviePlayer->PlayMovie();
}

