 // Fill out your copyright notice in the Description page of Project Settings.


#include "DrumStick.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ADrumStick::ADrumStick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compSphere = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SetRootComponent(compSphere);
	compSphere->SetRelativeScale3D(FVector(0.15f));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	compMesh->SetupAttachment(compSphere);
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	compMesh->SetRelativeLocation(FVector(0,0,-70));
	compMesh->SetRelativeScale3D(FVector(0.4f));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Drum/DrumStick.DrumStick'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
}

// Called when the game starts or when spawned
void ADrumStick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrumStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

