// Fill out your copyright notice in the Description page of Project Settings.


#include "PutPuzzle.h"
#include <Components/BoxComponent.h>
#include <Particles/ParticleSystem.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundBase.h>


// Sets default values
APutPuzzle::APutPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compBox = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(compBox);
	compBox->SetBoxExtent(FVector(50));
	compBox->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempPuzzle(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_shotShockwave.P_ky_shotShockwave'"));
	if (tempPuzzle.Succeeded())
	{
		completePuzzle = tempPuzzle.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Engine/VREditor/Sounds/UI/Object_Snaps_To_Grid.Object_Snaps_To_Grid'"));
	if (tempSound.Succeeded())
	{
		puzzleSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void APutPuzzle::BeginPlay()
{
	Super::BeginPlay();

// 	compBox->OnComponentBeginOverlap.AddDynamic(this, &APutPuzzle::OnPuzzle);
// 	compBox->OnComponentEndOverlap.AddDynamic(this, &APutPuzzle::OffPuzzle);

	GetRootComponent()->SetRelativeScale3D(FVector(2));

	FVector startPos = FVector(1095, 120, 2900);

	FString label = GetActorLabel();
	label = label.Replace(TEXT("BP_PutPuzzle"), TEXT(""));
	int32 idx = FCString::Atoi(*label) - 1;
	//UE_LOG(LogTemp, Warning, TEXT("%d"), idx);

	FVector pos = startPos;
	pos.Y += (idx % 4) * 200;
	pos.Z -= (idx / 4) * 200;
	SetActorLocation(pos);
}

// Called every frame
void APutPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	startLoc_s = GetActorLocation() + FVector(104, 0 , 0);
	endLoc_s = GetActorLocation() + FVector(99, 0, 0);
// 	FCollisionObjectQueryParams objectPoint;
// 	objectPoint.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
// 	hit_s = GetWorld()->LineTraceSingleByObjectType(hitInfo_s,startLoc_s,endLoc_s,objectPoint);
	hit_s = GetWorld()->LineTraceSingleByChannel(hitInfo_s, startLoc_s, endLoc_s, ECollisionChannel::ECC_WorldDynamic);
	DrawDebugLine(GetWorld(), startLoc_s, endLoc_s, FColor::Red, true,-1,0,1);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *hitInfo_s.GetActor()->GetName());
	if (hit_s)
	{
		bOverlap = true;
	}
	else
	{
		bOverlap = false;
	}

	
	startLoc = GetActorLocation() + GetActorForwardVector();
	endLoc = GetActorLocation() + (GetActorForwardVector() * -900);
	hit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility);
	//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, true, -1, 0, 3);
	if (bOverlap == false)
	{
		if (hit)
		{
			if (hitInfo.GetActor()->GetName().Contains(TEXT("Puzzle")))
			{
				setPuzzle = hitInfo.GetActor();
				DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Emerald, false, -1, 0, 10);
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
	}


	//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Yellow, true);
}

void APutPuzzle::OnPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//bOverlap = true;
}

void APutPuzzle::OffPuzzle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//bOverlap = false;
}

void APutPuzzle::SettingPuzzle()
{
	if (setPuzzle != nullptr)
	{
		setPuzzle->SetActorLocation(compBox->GetComponentLocation());
		setPuzzle->SetActorRotation(compBox->GetComponentRotation());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), completePuzzle, GetActorLocation(), GetActorRotation(), FVector3d(1));
		UGameplayStatics::PlaySound2D(GetWorld(),puzzleSound);

		setPuzzle = nullptr;
	}
}

