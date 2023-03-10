// Fill out your copyright notice in the Description page of Project Settings.


#include "BowActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

ABowActor::ABowActor()
{
	bowMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bow Mesh"));
	bowMesh->SetupAttachment(RootComponent);

	handleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle Mesh"));
	handleMesh->SetupAttachment(bowMesh);
	handleMesh->SetRelativeLocation(FVector(14.5, 0 ,0));
	handleMesh->SetRelativeScale3D(FVector(0.05));

	boxComp->SetBoxExtent(FVector(15, 90, 4));
}

void ABowActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABowActor::ShootArrow()
{

}
