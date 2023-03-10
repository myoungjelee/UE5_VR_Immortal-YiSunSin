// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AArrowActor::AArrowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(2);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
	meshComp->SetupAttachment(sphereComp);
	meshComp->SetRelativeLocation(FVector(-31, 0, 0));
	meshComp->SetRelativeRotation(FRotator(0, 180, 0));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	projectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	projectileComp->SetUpdatedComponent(sphereComp);
	projectileComp->InitialSpeed = 2000.0f;
	projectileComp->MaxSpeed = 2000.0f;
	projectileComp->bShouldBounce = false;
}

void AArrowActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArrowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		FVector p0 = GetActorLocation();
	FVector vt = GetActorForwardVector() * 2000 * DeltaTime;

}

void AArrowActor::Die()
{
	Destroy();
}

