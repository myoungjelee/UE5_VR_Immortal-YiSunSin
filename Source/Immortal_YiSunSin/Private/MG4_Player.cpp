// Fill out your copyright notice in the Description page of Project Settings.


#include "MG4_Player.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <HeadMountedDisplayFunctionLibrary.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <MotionControllerComponent.h>
#include <Camera/CameraComponent.h>
#include "PickupActor.h"
#include <Components/BoxComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Particles/ParticleSystem.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyShip.h"
#include "EnemyFSM.h"

// Sets default values
AMG4_Player::AMG4_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	cannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	cannon->SetupAttachment(GetMesh());

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	headMesh->SetupAttachment(cam);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	controllerLeft = CreateDefaultSubobject<UMotionControllerComponent>("Left Controller");
	controllerLeft->SetupAttachment(RootComponent);
	controllerLeft->MotionSource = "Left";
	
	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(controllerLeft);
	leftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	controllerRight = CreateDefaultSubobject<UMotionControllerComponent>("Right Controller");
	controllerRight->SetupAttachment(RootComponent);
	controllerRight->MotionSource = "Right";

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(controllerRight);
	rightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bUseControllerRotationPitch = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/GN/Cannon/Cannon.Cannon'"));
	if (tempMesh.Succeeded())
	{
		cannon->SetStaticMesh(tempMesh.Object);
		cannon->SetRelativeRotation(FRotator(0, -90, 90));
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExplo(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempExplo.Succeeded())
	{
		exploEffect = tempExplo.Object;
	}

}

// Called when the game starts or when spawned
void AMG4_Player::BeginPlay()
{
	Super::BeginPlay();
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(inputMapping, 0);
}

// Called every frame
void AMG4_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LaserPoint();
}

// Called to bind functionality to input
void AMG4_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Move Input Binding
	enhancedInputComponent->BindAction(thumbstickLeft, ETriggerEvent::Triggered, this, &AMG4_Player::Move);
	enhancedInputComponent->BindAction(thumbstickRight, ETriggerEvent::Triggered, this, &AMG4_Player::RotateAxis);
	enhancedInputComponent->BindAction(btnX, ETriggerEvent::Started, this, &AMG4_Player::OpenWidget);
	//trigger Input Binding
	enhancedInputComponent->BindAction(btnA, ETriggerEvent::Started, this, &AMG4_Player::APressed);
	enhancedInputComponent->BindAction(btnA, ETriggerEvent::Completed, this, &AMG4_Player::AReleased);

}

void AMG4_Player::Recenter()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

//void AMG4_Player::GripRightAction(const struct FInputActionValue& value)
//{
//	GrabObject(leftHand);
//}
//
//void AMG4_Player::GripRightReleased(const struct FInputActionValue& value)
//{
//	if (grabbedObject_R != nullptr)
//	{
//		grabbedObject_R->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//		grabbedObject_R = nullptr;
//		//이거 넣어줘야하나 ?? 굳이 안넣어도되나 윗줄 코드 있어서?
//		//bIsGrab = false;
//	}
//}
//
//void AMG4_Player::GripLeftAction(const struct FInputActionValue& value)
//{
//	GrabObject(rightHand);
//}
//
//void AMG4_Player::GripLeftReleased(const struct FInputActionValue& value)
//{
//	if (grabbedObject_L != nullptr)
//	{
//		grabbedObject_L->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//		grabbedObject_L = nullptr;
//		//이거 넣어줘야하나 ?? 굳이 안넣어도되나 윗줄 코드 있어서?
//		//bIsGrab = false;
//	}
//}
//
//void AMG4_Player::GrabObject(USkeletalMeshComponent* selectHand) //selectHand 넣어야하나? 아님 변수 따로 설정해주려면 GrabObject_R, L 이렇게 만들어야하나??
//{
//	// SphereTrace 방식
//	FVector rightTrace = rightHand->GetComponentLocation();
//	FVector rightEnd = rightTrace + rightHand->GetRightVector() * grabDistance;
//	FVector leftTrace = leftHand->GetComponentLocation();
//	FVector leftEnd = leftTrace + leftHand->GetRightVector() * grabDistance;
//
//	FHitResult hitInfo;
//	FCollisionQueryParams params;
//	params.AddIgnoredActor(GetOwner());
//	
//	//오른손 그립
//	if (GetWorld()->SweepSingleByChannel(hitInfo, rightTrace, rightEnd, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(grabDistance), params))
//	{
//		if (hitInfo.GetComponent()->GetName().Contains(TEXT("RightHandle")))
//		{
//			DrawDebugSphere(GetWorld(), rightTrace, 30, 20, FColor::Cyan, false, 3, 0, 3);
//			
//			grabbedObject_R = hitInfo.GetActor();
//			hitInfo.GetActor()->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform, FName("GrabPoint"));
//
//			/*UE_LOG(LogTemp, Warning, TEXT("%s"),*hitInfo.GetActor()->GetName());
//			UE_LOG(LogTemp, Error, TEXT("%s"),*hitInfo.GetComponent()->GetName());*/
//		}
//		/*grabedObject = Cast<AActor>(hitInfo.GetActor());
//		if (IsValid(grabedObject))
//		{
//
//			UBoxComponent* boxComp = Cast<UBoxComponent>(grabedObject->GetRootComponent());
//			if (boxComp != nullptr)
//			{
//				physicsState = boxComp->IsSimulatingPhysics();
//				boxComp->SetSimulatePhysics(false);
//			}
//
//			hitInfo.GetActor()->AttachToComponent(rightHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GrabPoint"));
//		}*/
//	}
//	//왼손 그립
//	if (GetWorld()->SweepSingleByChannel(hitInfo, leftTrace, leftEnd, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(grabDistance), params))
//	{
//		if (hitInfo.GetComponent()->GetName().Contains(TEXT("LeftHandle")))
//		{
//			DrawDebugSphere(GetWorld(), leftTrace, 30, 20, FColor::Red, false, 3, 0, 3);
//
//			grabbedObject_R = hitInfo.GetActor();
//			hitInfo.GetActor()->AttachToComponent(leftHand, FAttachmentTransformRules::KeepWorldTransform, FName("GrabPoint"));
//		}
//	}
//
//	bIsGrab = true;
//}

void AMG4_Player::Move(const struct FInputActionValue& value)
{
	FVector2D val = value.Get<FVector2D>();
	FVector direction = FVector(val.Y, val.X, 0);

	AddMovementInput(direction.GetSafeNormal(), 1, false);
}

void AMG4_Player::RotateAxis(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	//axis 값을 이용해서 캐릭터(콘트롤러)를 회전한다.
	AddControllerPitchInput(axis.Y * -1.0f);
	AddControllerYawInput(axis.X);
}

void AMG4_Player::LaserPoint()
{
	//Line trace start
	FVector startPos = cannon->GetSocketLocation("socket");
	//End (위치 + 방향 * 거리)
	FVector endPos = startPos + cannon->GetUpVector() * reachDistance;
	//충돌 옵션 설정
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());

	DrawDebugLine(GetWorld(), startPos, endPos, debugColor, false, -1, 0, 2);
	DrawDebugSphere(GetWorld(), endPos, 8, 30, debugColor);
}

void AMG4_Player::APressed()
{
	InputFire(true);
}

void AMG4_Player::AReleased()
{
	InputFire(false);
}

void AMG4_Player::InputFire(bool bFire) //const FInputActionValue& value
{
	//start
	FVector startPos = cannon->GetSocketLocation("socket");
	//End
	FVector endPos = startPos + cannon->GetUpVector() * reachDistance;
	//충돌이 되었을 때 정보를 담을 변수
	FHitResult hitInfo;
	//충돌 옵션 설정
	FCollisionQueryParams param;
	param.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, param);

	if (bHit == true)
	{
		// 맞은 위치에 effect 보여준다.
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			exploEffect,
			hitInfo.ImpactPoint);

		// 만약에 맞은놈이 ship 라면
		AActor* actor = hitInfo.GetActor();
		AEnemyShip* ship = Cast<AEnemyShip>(actor);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *hitInfo.GetActor()->GetName());
		if (ship != nullptr)
		{
			ship->fsm->ReceiveDamage();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), exploEffect, hitInfo.ImpactPoint);
		}
	bHit = false;
	}
}

void AMG4_Player::OpenWidget()
{
	
}
