// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPaddle.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
AShipPaddle::AShipPaddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = mesh;


}

// Called when the game starts or when spawned
void AShipPaddle::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
	TimeElapsed = 0.0f;
}

// Called every frame
void AShipPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 2초 주기로 이동
	const float MovementPeriod = 2.0f;
	TimeElapsed += DeltaTime;
	float MovementOffset_X = FMath::Sin(TimeElapsed / MovementPeriod * 2 * PI) * 100.0f;

	// 위치 변경
	FVector NewLocation = InitialLocation + FVector(0.0f, MovementOffset_X, 0.0f);
	SetActorLocation(NewLocation);
}

