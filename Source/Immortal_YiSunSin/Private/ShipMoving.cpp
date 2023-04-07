// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipMoving.h"
#include <Components/BoxComponent.h>

// Sets default values
AShipMoving::AShipMoving()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(box);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	mesh->SetupAttachment(box);
}

// Called when the game starts or when spawned
void AShipMoving::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipMoving::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator currRot = GetActorRotation();

	float roll = FMath::Sin(GetGameTimeSinceCreation()) * 5;
	FRotator rot = FRotator(currRot.Pitch, currRot.Yaw, roll);
	SetActorRotation(rot);

	// 현재 위치 저장
	FVector currLoc = GetActorLocation();

	// Z 값 변경 (범위 내에서 스무스하게)
	float posZ = FMath::Lerp(currLoc.Z, currLoc.Z+5, FMath::Sin(GetGameTimeSinceCreation()));
	FVector TargetLocation = FVector(currLoc.X, currLoc.Y, posZ);

	// 위치 보간
	FVector loc = FMath::Lerp(currLoc, TargetLocation, DeltaTime * 5.0f);

	// 액터 위치 갱신
	SetActorLocation(loc);
}

