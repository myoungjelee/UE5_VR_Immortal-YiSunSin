// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include <Components/StaticMeshComponent.h>

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/GN/Cannon/Cannon.Cannon'"));
	if (tempMesh.Succeeded())
	{
		
		mesh->SetStaticMesh(tempMesh.Object);
		mesh->SetRelativeRotation(FRotator(0, 0, 90));
	
	}
	
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LaserPoint();
}

void ACannon::LaserPoint()
{
	//Line trace start
	FVector startPos = mesh->GetSocketLocation("socket");
	//End (카메라위치 + 카메라 앞방향 * 거리)
	FVector endPos = startPos + mesh->GetUpVector() * grabDistance;
	//충돌 옵션 설정
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());

	DrawDebugLine(GetWorld(), startPos, endPos, debugColor, true, -1, 0, 2);
	DrawDebugSphere(GetWorld(), endPos, 8, 30, debugColor);
}

void ACannon::InputFire()
{
	mesh->GetSocketLocation("socket");
	FVector SocketLocation = mesh->GetSocketLocation("socket");
}