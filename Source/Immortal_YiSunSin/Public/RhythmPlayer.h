// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RhythmPlayer.generated.h"


UCLASS()
class IMMORTAL_YISUNSIN_API ARhythmPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARhythmPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* cam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* l_Controller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMotionControllerComponent* r_Controller;

	UPROPERTY(EditAnywhere)
		class USphereComponent* l_Stick;

	UPROPERTY(EditAnywhere)
		class USphereComponent* r_Stick;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* l_Mesh;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* r_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* widgetPointer_Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* widgetPointer_Right;

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* hitHaptic;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

	UPROPERTY(EditAnywhere)
		class UInputMappingContext* inputMapping;

	UPROPERTY(EditAnywhere)
		class UInputAction* x_Btn;

	UPROPERTY(EditAnywhere)
		class UInputAction* left_Trigger;

	UPROPERTY(EditAnywhere)
		class UInputAction* right_Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* pauseWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* gameOverWidget;

	UPROPERTY(EditAnywhere)
		class USoundBase* arirang;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AMoviePlayerActor* moviePlayer;


public:

	UFUNCTION()
		void OnDrum_Left(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnDrum_Right(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void GamePause();
	void ClickWidget_L();
	void ReleaseWidget_L();
	void ClickWidget_R();
	void ReleaseWidget_R();

};
