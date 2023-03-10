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
	// SphereTrace ¹æ½Ä
	FVector center = selectHand->GetComponentLocation();
	//FVector endLoc = center + selectHand->GetRightVector() * grabDistance;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());

	if (GetWorld()->SweepSingleByChannel(hitInfo, center, center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(grabDistance), params) && grabedObject == nullptr)
	{
		grabedObject = Cast<APickupActor>(hitInfo.GetActor());
		if (IsValid(grabedObject))
		{
			UBoxComponent* boxComp = Cast<UBoxComponent>(grabedObject->GetRootComponent());
			if (boxComp != nullptr)
			{
				physicsState = boxComp->IsSimulatingPhysics();
				boxComp->SetSimulatePhysics(false);
			}

			hitInfo.GetActor()->AttachToComponent(selectHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GrabPoint"));
			grabedObject->SetActorRelativeLocation(grabedObject->gripOffset);
		}
	}

	bIsGrab = true;
}

