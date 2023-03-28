// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowTargetActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ArrowActor.h"
#include <Components/BoxComponent.h>
#include <Components/TextRenderComponent.h>

AArrowTargetActor::AArrowTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);

	hit = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Hit Infomation"));
	hit->SetupAttachment(RootComponent);
	hit->SetTextRenderColor(FColor::Red);
}

void AArrowTargetActor::BeginPlay()
{
	Super::BeginPlay();
	
	meshComp->OnComponentBeginOverlap.AddDynamic(this, &AArrowTargetActor::OnHit);
}

void AArrowTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// È­»ì°ú ºÎµúÇûÀ» ¶§
void AArrowTargetActor::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsShoot(OtherActor, OtherComp))
	{
		hit->SetText(FText::FromString(TEXT("HIT!")));
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