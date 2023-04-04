// Fill out your copyright notice in the Description page of Project Settings.


#include "MoviePlayerActor.h"
#include <Components/StaticMeshComponent.h>
#include <MediaAssets/Public/MediaSoundComponent.h>
#include <MediaAssets/Public/MediaPlayer.h>

// Sets default values
AMoviePlayerActor::AMoviePlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		plane = CreateDefaultSubobject<UStaticMeshComponent>("VideoPlayer");
		SetRootComponent(plane);
		plane->SetCollisionProfileName(TEXT("NoCollision"));
		plane->SetVisibility(false);

		mediaSound = CreateDefaultSubobject<UMediaSoundComponent>("MediaSound");
		mediaSound->SetupAttachment(plane);

		ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		if (tempMesh.Succeeded())
		{
			plane->SetStaticMesh(tempMesh.Object);
		}

}

// Called when the game starts or when spawned
void AMoviePlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
	mediaSound->SetMediaPlayer(mediaPlayer);
}

// Called every frame
void AMoviePlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoviePlayerActor::PlayMovie()
{
	plane->SetVisibility(true);

	if (mediaPlayer->IsPlaying())
	{
		mediaPlayer->Play();
	}
	else
	{
		mediaPlayer->OpenSource(mediaSource);
	}
}

void AMoviePlayerActor::PausedMovie()
{
	if (mediaPlayer->IsPlaying())
	{
		mediaPlayer->Pause();
	}
}

