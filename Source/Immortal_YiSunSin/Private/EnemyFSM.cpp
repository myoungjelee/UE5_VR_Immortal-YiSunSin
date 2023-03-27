// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include <AIModule/Classes/AIController.h>
#include "EnemyShip.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <NavigationSystem.h>
#include <Components/CapsuleComponent.h>
#include "MG4_Player.h"
#include <Components/BoxComponent.h>
#include "EnemyShipManager.h"
#include "ScoreUI.h"
#include <UMG/Public/Components/WidgetComponent.h>

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	PrimaryComponentTick.bCanEverTick = true;

	bAutoActivate = true;
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	currHp = maxHp;

	target = Cast<AMG4_Player>(UGameplayStatics::GetActorOfClass(GetWorld(), AMG4_Player::StaticClass()));
	me = Cast<AEnemyShip>(GetOwner());

	ai = Cast<AAIController>(me->GetController());
}

void UEnemyFSM::NotifyActorBeginOverlap(AActor* OtherActor)
{

}

// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (score == nullptr)
	{
		score = Cast<UScoreUI>(target->scoreUI->GetUserWidgetObject());
	}

	switch (currState)
	{
	case EEnemyState::Idle:
		UpdateIdle();
		break;
	case EEnemyState::Move:
		UpdateMove();
		break;
	case EEnemyState::Damaged:
		UpdateDamaged();
		break;
	case EEnemyState::Die:
		UpdateDie();
		break;
	}
}


void UEnemyFSM::UpdateIdle()
{
	if (IsTargetTrace())
	{
		ChangeState(EEnemyState::Move);
	}
	else
	{
		if (IsWaitComplete(idleDelayTime))
		{
			ChangeState(EEnemyState::Move);
		}
	}
}

void UEnemyFSM::UpdateMove()
{
	bool bTrace = IsTargetTrace();

	FVector dir = target->GetActorLocation() - me->GetActorLocation();
	float dist = FVector::Distance(originPos, me->GetActorLocation());

	if (bTrace) //만약 시야에 들어왔다면
	{
		ai->MoveToLocation(target->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("move!!!!"));
	}
	else
	{
		MoveToPos(randPos);
	}
}

void UEnemyFSM::UpdateDamaged()
{
	if (IsWaitComplete(damageDelayTime))
	{
		ChangeState(EEnemyState::Idle);
	}
}

void UEnemyFSM::UpdateDie()
{
	if (bDieMove == false) return;

	//UE_LOG(LogTemp, Warning, TEXT(""));
	FVector p0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector p = p0 + vt;
	
	if (p.Z < -200)
	{
		me->Destroy();
		me->SetActive(false);
		AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyShipManager::StaticClass());
		AEnemyShipManager* enemyManager = Cast<AEnemyShipManager>(actor);
		enemyManager->enemyArray.Add(me);
		currHp = maxHp;
		ChangeState(EEnemyState::Idle);
		bDieMove = false;
	}
	else
	{
		me->SetActorLocation(p);
	}

}



void UEnemyFSM::ChangeState(EEnemyState state)
{

	UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyState"), true);
	if (enumPtr != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s -----> %s"),
			*enumPtr->GetNameStringByIndex((int32)currState),
			*enumPtr->GetNameStringByIndex((int32)state));
	}

	//현재 상태를 갱신
	currState = state;

	//현재 시간 초기화
	currTime = 0;

	//ai 의 움직임 멈추자
	ai->StopMovement();

	//상태에 따른 초기설정
	switch (currState)
	{
	case EEnemyState::Move:
	{
		//네비게이션 시스템 가져오자
		UNavigationSystemV1* ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		//랜덤한 위치를 얻오자
		FNavLocation loc;
		ns->GetRandomReachablePointInRadius(originPos, 1000, loc);
		randPos = loc.Location;
	}
	break;
	case EEnemyState::Die:
		bDieMove = true;
		//충돌안되게 설정
		me->GetCapsuleComponent()->SetCollisionEnabled (ECollisionEnabled::NoCollision);
		me->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		me->boxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		score->UpdateScore(5);
	break;
	}
}

void UEnemyFSM::ReceiveDamage()
{
	currHp--;
	if (currHp > 0)
	{
		ChangeState(EEnemyState::Damaged);
	}
	else
	{
		ChangeState(EEnemyState::Die);
	}
}

bool UEnemyFSM::IsWaitComplete(float delayTime)
{
	currTime += GetWorld()->DeltaTimeSeconds;

	if (currTime > delayTime)
	{
		currTime = 0;
		return true;
	}
	return false;
}

bool UEnemyFSM::IsTargetTrace()
{
	FVector dir = target->GetActorLocation() - me->GetActorLocation();

	float dotValue = FVector::DotProduct(me->GetActorForwardVector(), dir.GetSafeNormal());
	float angle = UKismetMathLibrary::DegAcos(dotValue);

	//30도(시야각60) 보다 작고 traceRange 보다 거리가 좁을 때
	if (angle<30 && dir.Length() < traceRange)
	{
		FHitResult hitInfo;
		FCollisionQueryParams param;
		param.AddIgnoredActor(me);

		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, me->GetActorLocation(), target->GetActorLocation(), ECollisionChannel::ECC_Visibility, param);

		if (bHit)
		{
			if (hitInfo.GetActor()->GetName().Contains(TEXT("Player")))
			{
				//DrawDebugLine(GetWorld(), me->GetActorLocation(), target->GetActorLocation(),  FColor::Cyan, true, -1, 0, 0.5);
				
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *hitInfo.GetActor()->GetName());

				return true;
			}
		}
	}
	return false;
}

void UEnemyFSM::MoveToPos(FVector pos)
{
	//해당 위치(pos) 로 간다
	EPathFollowingRequestResult::Type result = ai->MoveToLocation(pos);

	//만약에 목적지에 도착했다면
	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		//Idle 상태로 전환
		ChangeState(EEnemyState::Idle);
	}
}