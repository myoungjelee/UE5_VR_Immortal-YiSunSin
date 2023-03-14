// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"
#include "EnemyFSM.h"
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AEnemyShip::AEnemyShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//LineTrace 에 감지가 되게 셋팅
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//FSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	//Auto possess ai 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called every frame
void AEnemyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyShip::SetActive(bool bActive)
{
	// 활성화
	if (bActive)
	{
		//충돌 활성
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	// 비활성화
	else
	{
		//충돌 비활성
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//탄창에 날 다시 넣어줘
		dieDelegate.ExecuteIfBound(this);
	}

	//메쉬를 활성 / 비활성
	GetMesh()->SetActive(bActive);
	//메쉬를 보이고 / 안보이고
	GetMesh()->SetVisibility(bActive);
	//캐릭터 무브먼트 활성 / 비활성
	GetCharacterMovement()->SetActive(bActive);
	//fsm 활성 / 비활성
	if (fsm != nullptr)
	{
		fsm->SetActive(bActive);
	}
}
