// Fill out your copyright notice in the Description page of Project Settings.


#include "Buttons.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
AButtons::AButtons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	SetRootComponent(body);

	bottom1 = CreateDefaultSubobject<UStaticMeshComponent>("Bottom1");
	bottom1->SetupAttachment(body);

	bottom2 = CreateDefaultSubobject<UStaticMeshComponent>("Bottom2");
	bottom2->SetupAttachment(body);

	bottom3 = CreateDefaultSubobject<UStaticMeshComponent>("Bottom3");
	bottom3->SetupAttachment(body);

	btn1 = CreateDefaultSubobject<UStaticMeshComponent>("Btn1");
	btn1->SetupAttachment(body);

	box1 = CreateDefaultSubobject<UBoxComponent>("Box1");
	box1->SetupAttachment(btn1);

	btn2 = CreateDefaultSubobject<UStaticMeshComponent>("Btn2");
	btn2->SetupAttachment(body);

	box2 = CreateDefaultSubobject<UBoxComponent>("Box2");
	box2->SetupAttachment(btn2);

	btn3 = CreateDefaultSubobject<UStaticMeshComponent>("Btn3");
	btn3->SetupAttachment(body);

	box3 = CreateDefaultSubobject<UBoxComponent>("Box3");
	box3->SetupAttachment(btn3);
}

// Called when the game starts or when spawned
void AButtons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

