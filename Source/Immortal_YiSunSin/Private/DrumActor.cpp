// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumActor.h"
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ADrumActor::ADrumActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compCapsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	SetRootComponent(compCapsule);

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	compMesh->SetupAttachment(compCapsule);
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADrumActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrumActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrumActor::OnDrum(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

