// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrowActor::AArrowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(35.0f, 2.0f, 2.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetRelativeLocation(FVector(3, 0, 0));
	//meshComp->SetRelativeRotation(FRotator(0, 180, 0));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	projectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	projectileComp->SetUpdatedComponent(boxComp);
	projectileComp->InitialSpeed = 3000.0f;
	projectileComp->MaxSpeed = 3000.0f;
	projectileComp->bShouldBounce = false;
	projectileComp->bRotationFollowsVelocity = true;

}

void AArrowActor::BeginPlay()
{
	Super::BeginPlay();

	projectileComp->SetActive(false);
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AArrowActor::OnTarget);
	
}

void AArrowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 화살 발사 --> 플레이어에서 실행
void AArrowActor::Shoot()
{
	projectileComp->SetVelocityInLocalSpace(FVector(projectileComp->MaxSpeed, 0, 0));
	bIsShoot = true;
	projectileComp->bRotationFollowsVelocity = true;
	projectileComp->SetActive(true);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// 과녁에 박혔을 때
void AArrowActor::OnTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!(OtherActor->GetName().Contains(TEXT("Player"))) && bIsShoot)
	{
		projectileComp->StopMovementImmediately();
		projectileComp->SetActive(false);

		FTimerHandle WaitHandle;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
			{

				Destroy();

			}), 5.0f, false);
	}
}
