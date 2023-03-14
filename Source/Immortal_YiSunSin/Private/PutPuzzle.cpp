// Fill out your copyright notice in the Description page of Project Settings.


#include "PutPuzzle.h"
#include <Components/BoxComponent.h>


// Sets default values
APutPuzzle::APutPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(compBox);
	compBox->SetRelativeScale3D(FVector(5, 0.1f, 0.1f));
}

// Called when the game starts or when spawned
void APutPuzzle::BeginPlay()
{
	Super::BeginPlay();

	compBox->OnComponentBeginOverlap.AddDynamic(this, &APutPuzzle::OnPuzzle);
}

// Called every frame
void APutPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	startLoc = GetActorLocation()+(GetActorForwardVector() * 99);
	endLoc = GetActorLocation()+(GetActorForwardVector() * -500);
	hit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility);

	if (hit)
	{
		if (hitInfo.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			overlapPuzzle = hitInfo.GetActor();
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *hitInfo.GetActor()->GetName());
	}
	else
	{
		overlapPuzzle = nullptr;
	}

	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, true);
}

void APutPuzzle::OnPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Puzzle")))
	{
		//overlapPuzzle = OtherActor;
	}
}

void APutPuzzle::SettingPuzzle()
{
	if (overlapPuzzle != nullptr)
	{
		overlapPuzzle->SetActorLocation(compBox->GetComponentLocation() + FVector(40, 0, -60));
		overlapPuzzle->SetActorRotation(compBox->GetComponentRotation());
		//overlapPuzzle = nullptr;
	}
}

