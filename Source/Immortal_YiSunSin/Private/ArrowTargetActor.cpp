// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowTargetActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ArrowActor.h"
#include <Components/BoxComponent.h>
#include <Components/TextRenderComponent.h>
#include "ArcherPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include "ScoreUI.h"

AArrowTargetActor::AArrowTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	bracket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bracket"));
	bracket->SetupAttachment(RootComponent);

	ring1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring1"));
	ring1->SetupAttachment(RootComponent);
	ring1->SetRelativeLocation(FVector(0, 20, 150));
	ring1->SetRelativeRotation(FRotator(0, 0, -10));

	ring2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring2"));
	ring2->SetupAttachment(RootComponent);
	ring2->SetRelativeLocation(FVector(0, 20, 150));
	ring2->SetRelativeRotation(FRotator(0, 0, -10));

	ring3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring3"));
	ring3->SetupAttachment(RootComponent);
	ring3->SetRelativeLocation(FVector(0, 20, 150));
	ring3->SetRelativeRotation(FRotator(0, 0, -10));

	ring4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring4"));
	ring4->SetupAttachment(RootComponent);
	ring4->SetRelativeLocation(FVector(0, 20, 150));
	ring4->SetRelativeRotation(FRotator(0, 0, -10));

	ring5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring5"));
	ring5->SetupAttachment(RootComponent);
	ring5->SetRelativeLocation(FVector(0, 20, 150));
	ring5->SetRelativeRotation(FRotator(0, 0, -10));

	ring6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring6"));
	ring6->SetupAttachment(RootComponent);
	ring6->SetRelativeLocation(FVector(0, 20, 150));
	ring6->SetRelativeRotation(FRotator(0, 0, -10));

	ring7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring7"));
	ring7->SetupAttachment(RootComponent);
	ring7->SetRelativeLocation(FVector(0, 20, 150));
	ring7->SetRelativeRotation(FRotator(0, 0, -10));

	ring8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring8"));
	ring8->SetupAttachment(RootComponent);
	ring8->SetRelativeLocation(FVector(0, 20, 150));
	ring8->SetRelativeRotation(FRotator(0, 0, -10));

	ring9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring9"));
	ring9->SetupAttachment(RootComponent);
	ring9->SetRelativeLocation(FVector(0, 20, 150));
	ring9->SetRelativeRotation(FRotator(0, 0, -10));

	ring10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring10"));
	ring10->SetupAttachment(RootComponent);
	ring10->SetRelativeLocation(FVector(0, 20, 150));
	ring10->SetRelativeRotation(FRotator(0, 0, -10));

	hit = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Hit Infomation"));
	hit->SetupAttachment(RootComponent);
	hit->SetTextRenderColor(FColor::Red);
}

void AArrowTargetActor::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AArcherPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AArcherPlayer::StaticClass()));

	TArray<UActorComponent*> Components = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* Component : Components)
	{
		UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component);
		if (Mesh != nullptr)
		{
			rings.Add(Mesh);
		}
	}

	for (UStaticMeshComponent* Mesh : rings)
	{
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit);
	}
}

void AArrowTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (scoreUI == nullptr)
	{
		scoreUI = Cast<UScoreUI>(player->scoreUI->GetUserWidgetObject());
	}

	if (bSpawn)
	{
		setTime += DeltaTime;
		if (setTime > 4)
		{
			SetActive(false);
		}
	}
}

// È­»ì°ú ºÎµúÇûÀ» ¶§
void AArrowTargetActor::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		FString playerScore = FString::Printf(TEXT("Hit!!"), point);
		hit->SetText(FText::FromString(playerScore));
		player->shootCnt++;
		scoreUI->UpdateScore(1);
		SetActive(false);
	}
}

// ºÎµúÈù°Ô È­»ìÀÎÁö ¾Æ´ÑÁö
bool AArrowTargetActor::IsShoot(AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (OtherComp->GetName().Contains(TEXT("Box")))
	{
		arrow = Cast<AArrowActor>(OtherActor);
		arrow->boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		return true;
	}
	
	return false;
}

void AArrowTargetActor::SetActive(bool bActive)
{
	TArray<UActorComponent*> Components = GetComponentsByClass(UStaticMeshComponent::StaticClass());
	for (UActorComponent* Component : Components)
	{
		UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Component);
		if (Mesh != nullptr)
		{
			rings.Add(Mesh);
		}
	}

	if (bActive)
	{
		for (UStaticMeshComponent* Mesh : rings)
		{
			Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
	else
	{
		for (UStaticMeshComponent* Mesh : rings)
		{
			Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		targetHit.ExecuteIfBound(this);
	}

	bSpawn = bActive;

	for (UStaticMeshComponent* Mesh : rings)
	{
		Mesh->SetActive(bActive);
		Mesh->SetVisibility(bActive);
	}

	hit->SetActive(bActive);
	hit->SetVisibility(bActive);
}
