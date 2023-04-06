// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class IMMORTAL_YISUNSIN_API UEasingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static float QuadEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
	static float QuadEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
	static float QuadEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
	static float CubicEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
	static float CubicEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
	static float CubicEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
	static float QuartEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
	static float QuartEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
	static float QuartEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float QuintEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float QuintEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float QuintEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float SineEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float SineEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float SineEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float CircEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float CircEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float CircEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float ExpoEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float ExpoEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float ExpoEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float ElasticEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float ElasticEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float ElasticEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float BackEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float BackEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float BackEaseInOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float BounceEaseIn(float Param);

	UFUNCTION(BlueprintCallable)
		static float BounceEaseOut(float Param);

	UFUNCTION(BlueprintCallable)
		static float BounceEaseInOut(float Param);

};
