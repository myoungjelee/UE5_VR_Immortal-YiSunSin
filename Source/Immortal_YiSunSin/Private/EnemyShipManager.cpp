// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShipManager.h"
#include "EnemyShip.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyShipManager::AEnemyShipManager()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ConstructorHelpers::FClassFinder<AEnemyShip> tempEnemy(TEXT("/Script/Engine.Blueprint'/Game/GN_Blueprint/MG4/BP_enemyShip.BP_enemyShip_C'"));
	if (tempEnemy.Succeeded())
	{
		enemyFactory = tempEnemy.Class;
	}
}

void AEnemyShipManager::BeginPlay()
{
	Super::BeginPlay();
	
	spawnTime = FMath::RandRange(minTime, maxTime);

	//spawn pos 세팅
	FindSpawnPos();

	for (int32 i = 0; i < 10; i++)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//enemy 생성
		AEnemyShip* e = GetWorld()->SpawnActor<AEnemyShip>(enemyFactory, GetActorLocation(), GetActorRotation(), param);
		//적이 죽었을 때 호출되는 함수 등록
		e->dieDelegate.BindUObject(this, &AEnemyShipManager::AddEnemy);
		//적을 비활성화 하자
		e->SetActive(false);
	}
}

// Called every frame
void AEnemyShipManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//만약에 적 탄창 갯수가 0이면
	if (enemyArray.Num() == 0)
	{
		return;
	}
	currTime += DeltaTime;
	if (currTime > spawnTime)
	{
		AActor* spawn = spawnPosArray[spawnIdx];

		//1. 랜덤한 yaw 값 구하자( 0 ~ 360 )4
		float yaw = FMath::RandRange(0.0f, 360.0f);
		//2. 구한 값을 spawnPosArray 의 yaw 값에 셋팅
		spawn->SetActorRotation(FRotator(0, yaw, 0));
		//3. 랜덤한 길이 구하자( 0 ~ 500 )
		float length = FMath::RandRange(300.0f, 1000.0f);
		//4. spawnPosArray 앞방향 * 랜덤 길이
		FVector pos = spawn->GetActorForwardVector() * length;
		//5. 4번에서 구한 벡터 + spawnPosArray 의 위치		

		//적 위치, 회전 셋팅
		enemyArray[0]->SetActorLocation(spawn->GetActorLocation() + pos);
		enemyArray[0]->SetActorRotation(spawn->GetActorRotation());
		//적 탄창에서 0번째 놈 활성화 
		enemyArray[0]->SetActive(true);
		//enemyArray 에서 빼자
		enemyArray.RemoveAt(0);

		//0 ~ 갯수 순서대로
		//다음 자리로 설정
		spawnIdx++;
		spawnIdx = spawnIdx % spawnPosArray.Num();

		//현재시간 초기화
		currTime = 0;
		//생성시간 새롭게 셋팅
		spawnTime = FMath::RandRange(minTime, maxTime);
	}
}

void AEnemyShipManager::FindSpawnPos()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), actors);

	for (int32 i = 0; i < actors.Num(); i++)
	{
		//만약에 이름에 SpawnPos 가 포함되어 있다면
		if (actors[i]->GetName().Contains(TEXT("SpawnPos")))
		{
			//spawnPosArray 에 추가한다
			spawnPosArray.Add(actors[i]);
		}
	}
}

void AEnemyShipManager::AddEnemy(class AEnemyShip* e)
{
	enemyArray.Add(e);
}

