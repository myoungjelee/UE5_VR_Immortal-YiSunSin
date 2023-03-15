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

	UPROPERTY(EditAnywhere)
		class UCameraComponent* cam;

	UPROPERTY(EditAnywhere)
		class UMotionControllerComponent* l_Controller;

	UPROPERTY(EditAnywhere)
		class UMotionControllerComponent* r_Controller;

	UPROPERTY(EditAnywhere)
		class USphereComponent* l_Stick;

	UPROPERTY(EditAnywhere)
		class USphereComponent* r_Stick;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* l_Mesh;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* r_Mesh;

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* hitHaptic;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

	UPROPERTY(EditAnywhere)
		class UInputMappingContext* inputMapping;

	UPROPERTY(EditAnywhere)
		class UInputAction* grip_Left;

// 	UPROPERTY(EditAnywhere)
// 		class UParticleSystem* hit_Left;
// 
// 	UPROPERTY(EditAnywhere)
// 		class UParticleSystem* hit_Right;

public:
	
	UFUNCTION()
		void OnDrum_Left(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnDrum_Right(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		void Recenter();

};
