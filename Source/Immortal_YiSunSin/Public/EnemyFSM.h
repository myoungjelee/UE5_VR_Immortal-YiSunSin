// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

//상태 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Damaged,
	Die
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_YISUNSIN_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void NotifyActorBeginOverlap(AActor* OtherActor);

	//현재상태
	UPROPERTY(EditAnywhere)
		EEnemyState currState = EEnemyState::Idle;

	UPROPERTY(EditAnywhere)
		class AMG4_Player* target;

	UPROPERTY(EditAnywhere)
		class AEnemyShip* me;

	UPROPERTY(EditAnywhere)
	class UScoreUI* score;

	//ai controller 
	UPROPERTY(EditAnywhere)
		class AAIController* ai;

	/*UPROPERTY(EditAnywhere)
		class AActor* actor;*/
	
	UPROPERTY(EditAnywhere)
	float currHp;

	UPROPERTY(EditAnywhere)
	float maxHp = 1;

	float traceRange = 1000;
	float currTime = 0;
	float idleDelayTime = 2;
	float damageDelayTime = 2;
	float dieSpeed = 100;
	bool bDieMove = false;

	//처음 위치
	FVector originPos;
	//랜덤 위치
	FVector randPos;

public:
	void UpdateIdle();
	void UpdateMove();
	void UpdateDamaged();
	void UpdateDie();

	void ChangeState(EEnemyState state);
	void ReceiveDamage();

	bool IsWaitComplete(float delayTime);
	bool IsTargetTrace();
	void MoveToPos(FVector pos);
};
