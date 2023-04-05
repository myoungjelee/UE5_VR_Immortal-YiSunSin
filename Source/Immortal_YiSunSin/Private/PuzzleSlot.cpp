// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSlot.h"

// Sets default values
APuzzleSlot::APuzzleSlot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleSlot::BeginPlay()
{
	Super::BeginPlay();

	GetRootComponent()->SetRelativeScale3D(FVector(2));

	FVector startPos = FVector(1300, -125, 2900);

	/*FString label = GetActorLabel();
	label = label.Replace(TEXT("Slot"), TEXT(""));
	int32 idx = FCString::Atoi(*label) - 1;*/
	//UE_LOG(LogTemp, Warning, TEXT("%d"), idx);

	FVector pos = startPos;
	pos.Y += (idx % 4) * 200;
	pos.Z -= (idx / 4) * 200;
	SetActorLocation(pos);

	start = GetActorLocation() + FVector(-101, 0, 0);
	end = GetActorLocation() + FVector(-105, 0, 0);
}

// Called every frame	
void APuzzleSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugLine(GetWorld(), start, end, FColor::Red, true, -1, 0, 10);

}

