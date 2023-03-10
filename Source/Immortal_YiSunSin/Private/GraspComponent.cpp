// Fill out your copyright notice in the Description page of Project Settings.


#include "GraspComponent.h"
#include "PlayerBase.h"
#include "EnhancedInputComponent.h"
#include "PickupActor.h"
#include "Components/BoxComponent.h"
#include "BowActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextRenderComponent.h"

UGraspComponent::UGraspComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UGraspComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerBase>(GetOwner());
	//bow = Cast<ABowActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ABowActor::StaticClass()));

	//FVector slideLoc = bow->handleMesh->GetComponentLocation();
}

void UGraspComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGraspComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(grip_left, ETriggerEvent::Started, this, &UGraspComponent::GripLeftAction);
	PlayerInputComponent->BindAction(grip_left, ETriggerEvent::Completed, this, &UGraspComponent::GripLeftReleased);
	PlayerInputComponent->BindAction(grip_right, ETriggerEvent::Started, this, &UGraspComponent::GripRightAction);
	PlayerInputComponent->BindAction(grip_right, ETriggerEvent::Completed, this, &UGraspComponent::GripRightReleased);
}

void UGraspComponent::GripLeftAction(const struct FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("11111111111111"));
	GrabObject(player->leftHand);
	player->rightLog->SetText(FText::FromString(TEXT("Left")));
}

void UGraspComponent::GripLeftReleased(const struct FInputActionValue& value)
{
	bIsGrab = false;
}

void UGraspComponent::GripRightAction(const struct FInputActionValue& value)
{
	GrabObject(player->rightHand);
	player->rightLog->SetText(FText::FromString(TEXT("Right")));
}

void UGraspComponent::GripRightReleased(const struct FInputActionValue& value)
{
	bIsGrab = false;
}

// 액터 잡기
void UGraspComponent::GrabObject(USkeletalMeshComponent* selectHand)
{
	// SphereTrace 방식
	FVector center = selectHand->GetComponentLocation();
	//FVector endLoc = center + selectHand->GetRightVector() * grabDistance;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	if (GetWorld()->SweepSingleByChannel(hitInfo, center, center, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(grabDistance), params) && grabedObject == nullptr)
	{
		player->rightLog->SetText(FText::FromString(hitInfo.GetActor()->GetName()));
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

// 액터 놓기
void UGraspComponent::ReleaseObject(USkeletalMeshComponent* selectHand)
{
	if (grabedObject != nullptr)
	{
		// 잡고 있던 물체를 떼어낸다.
		grabedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// 물체의 본래 피직스 on/off 여부를 되돌려준다.
		UBoxComponent* boxComp = Cast<UBoxComponent>(grabedObject->GetRootComponent());
		if (boxComp != nullptr)
		{
			boxComp->SetSimulatePhysics(physicsState);
		}
	}
}
