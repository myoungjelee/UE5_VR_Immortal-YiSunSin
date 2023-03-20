// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include "EnemyShip.h"
#include "EnemyFSM.h"

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
	
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExplo(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	if (tempExplo.Succeeded())
	{
		exploEffect = tempExplo.Object;
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
	//End (위치 + 방향 * 거리)
	FVector endPos = startPos + mesh->GetUpVector() * grabDistance;
	//충돌 옵션 설정
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());

	DrawDebugLine(GetWorld(), startPos, endPos, debugColor, true, -1, 0, 2);
	DrawDebugSphere(GetWorld(), endPos, 8, 30, debugColor);
}

	//mesh->GetSocketLocation("socket");
	//FVector SocketLocation = mesh->GetSocketLocation("socket");

void ACannon::InputFire()
{
	//start
	FVector startPos = mesh->GetSocketLocation("socket");
	//End
	FVector endPos = startPos + mesh->GetUpVector() * grabDistance;
	//충돌이 되었을 때 정보를 담을 변수
	FHitResult hitInfo;
	//충돌 옵션 설정
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, param);

	if (bHit == true)
	{
		// 맞은 위치에 레이저를 보여준다.
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			exploEffect,
			hitInfo.ImpactPoint);

		// 만약에 맞은놈이 ship 라면
		AActor* actor = hitInfo.GetActor();
		AEnemyShip* ship = Cast<AEnemyShip>(actor);
		if (ship != nullptr)
		{
			ship->fsm->ReceiveDamage();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), exploEffect, hitInfo.ImpactPoint);
		}

	}

}