// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordActor.h"

ASwordActor::ASwordActor()
{
	planeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	planeComp->SetupAttachment(meshComp);

}

void ASwordActor::BeginPlay()
{
	Super::BeginPlay();

	planeComp->SetVisibility(false);
	gripOffset = FVector(-50, 0, -15);
}
