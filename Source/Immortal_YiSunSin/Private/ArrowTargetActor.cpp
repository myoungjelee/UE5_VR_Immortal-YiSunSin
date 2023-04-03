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
	
	ring1->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit1);
	ring2->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit2);
	ring3->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit3);
	ring4->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit4);
	ring5->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit5);
	ring6->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit6);
	ring7->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit7);
	ring8->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit8);
	ring9->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit9);
	ring10->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit10);
}

void AArrowTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (scoreUI == nullptr)
	{
		scoreUI = Cast<UScoreUI>(player->scoreUI->GetUserWidgetObject());
	}

}

// È­»ì°ú ºÎµúÇûÀ» ¶§
void AArrowTargetActor::OnHit1(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 1;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 2;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit3(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 3;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit4(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 4;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit5(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 5;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit6(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 6;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit7(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 7;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit8(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 8;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit9(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 9;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
	}
}

void AArrowTargetActor::OnHit10(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), hitTarget);
		point = 10;
		FString playerScore = FString::Printf(TEXT("%d"), point);
		hit->SetText(FText::FromString(playerScore));
		scoreUI->UpdateScore(point);
		player->shootCnt++;
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