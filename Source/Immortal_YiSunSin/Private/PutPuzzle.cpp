// Fill out your copyright notice in the Description page of Project Settings.


#include "PutPuzzle.h"
#include <Components/BoxComponent.h>
#include <Particles/ParticleSystem.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
APutPuzzle::APutPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(compBox);
	compBox->SetRelativeScale3D(FVector(1.25f));

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempPuzzle(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_shotShockwave.P_ky_shotShockwave'"));
	if (tempPuzzle.Succeeded())
	{
		completePuzzle = tempPuzzle.Object;
	}
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

	startLoc = GetActorLocation()+(GetActorForwardVector() * 49);
	endLoc = GetActorLocation()+(GetActorForwardVector() * -500);
	hit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility);

	if (hit)
	{
		if (hitInfo.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			setPuzzle = hitInfo.GetActor();
			//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, false, 1, 0, 3);
		}
 		else
 		{
 			setPuzzle = nullptr;
 		}	
	}
	else
	{
		setPuzzle = nullptr;
	}

	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Yellow, true);
}

void APutPuzzle::OnPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void APutPuzzle::SettingPuzzle()
{
	if (setPuzzle != nullptr)
	{
		setPuzzle->SetActorLocation(compBox->GetComponentLocation() + FVector(0, 0, -60));
		setPuzzle->SetActorRotation(compBox->GetComponentRotation());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), completePuzzle, GetActorLocation(), GetActorRotation(), FVector3d(1));
	}
}

