// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UCLASS()
class IMMORTAL_YISUNSIN_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//cpp랑 blueprint sync 하기 -> button 정의하고 함수 만들기 ??
	/*virtual void OnClicked(Button) override;
	virtual void OnReleased(Button) override;*/
 
};
