// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordActor.h"

ASwordActor::ASwordActor()
{
	planeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Mesh"));
	planeComp->SetupAttachment(meshComp);
	planeComp->SetRelativeLocation(FVector(0, -268, 52));
	planeComp->SetRelativeScale3D(FVector(1, 12, 1));

}

void ASwordActor::BeginPlay()
{
	Super::BeginPlay();

	planeComp->SetVisibility(false);
}
