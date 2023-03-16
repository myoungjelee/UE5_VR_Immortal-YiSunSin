// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowTargetActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AArrowTargetActor::AArrowTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
}

void AArrowTargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArrowTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

