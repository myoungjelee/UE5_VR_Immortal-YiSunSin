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

// Sets default values
AMG4_Player::AMG4_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

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

}

// Called to bind functionality to input
void AMG4_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Grip Input Binding
	enhancedInputComponent->BindAction(gripLeft, ETriggerEvent::Started, this, &AMG4_Player::GripLeftAction);
	enhancedInputComponent->BindAction(gripLeft, ETriggerEvent::Completed, this, &AMG4_Player::GripLeftReleased);
	enhancedInputComponent->BindAction(gripRight, ETriggerEvent::Started, this, &AMG4_Player::GripRightAction);
	enhancedInputComponent->BindAction(gripRight, ETriggerEvent::Completed, this, &AMG4_Player::GripRightReleased);
	//Move Input Binding
	enhancedInputComponent->BindAction(thumbstickLeft, ETriggerEvent::Triggered, this, &AMG4_Player::Move);
	enhancedInputComponent->BindAction(thumbstickRight, ETriggerEvent::Triggered, this, &AMG4_Player::RotateAxis);

}

void AMG4_Player::Recenter()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMG4_Player::GripRightAction(const struct FInputActionValue& value)
{
	GrabObject(leftHand);
}

void AMG4_Player::GripRightReleased(const struct FInputActionValue& value)
{
	bIsGrab = false;
}

void AMG4_Player::GripLeftAction(const struct FInputActionValue& value)
{
	GrabObject(rightHand);
}

void AMG4_Player::GripLeftReleased(const struct FInputActionValue& value)
{
	bIsGrab = false;
}

void AMG4_Player::GrabObject(USkeletalMeshComponent* selectHand)
{
	// SphereTrace 방식
	FVector rightTrace = rightHand->GetComponentLocation();
	FVector leftTrace = leftHand->GetComponentLocation();
	FVector rightEnd = rightTrace + rightHand->GetRightVector() * grabDistance;
	FVector leftEnd = leftTrace + leftHand->GetRightVector() * grabDistance;

	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	

	if (GetWorld()->SweepSingleByChannel(hitInfo, rightTrace, rightEnd, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(grabDistance), params))
	{
		if (hitInfo.GetComponent()->GetName().Contains(TEXT("RightHandle")))
		{
			DrawDebugSphere(GetWorld(), rightTrace, 30, 20, FColor::Red, false, 3, 0, 3);
			
			hitInfo.GetActor()->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform, FName("GrabPoint"));
//			SnapToTargetNotIncludingScale
			UE_LOG(LogTemp, Warning, TEXT("%s"),*hitInfo.GetActor()->GetName());
			UE_LOG(LogTemp, Error, TEXT("%s"),*hitInfo.GetComponent()->GetName());
		}
		/*grabedObject = Cast<AActor>(hitInfo.GetActor());
		if (IsValid(grabedObject))
		{

			UBoxComponent* boxComp = Cast<UBoxComponent>(grabedObject->GetRootComponent());
			if (boxComp != nullptr)
			{
				physicsState = boxComp->IsSimulatingPhysics();
				boxComp->SetSimulatePhysics(false);
			}

			hitInfo.GetActor()->AttachToComponent(rightHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GrabPoint"));
		}*/
	}

	bIsGrab = true;
}

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