// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YiSunSinInstance.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API UYiSunSinInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

public:
	UPROPERTY(BlueprintReadWrite)
	int32 score;
};
