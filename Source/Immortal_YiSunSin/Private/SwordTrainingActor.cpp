// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordTrainingActor.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"

ASwordTrainingActor::ASwordTrainingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);

	proComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	proComp->SetupAttachment(meshComp);

	
}

void ASwordTrainingActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASwordTrainingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
