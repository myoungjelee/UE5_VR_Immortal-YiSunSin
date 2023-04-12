// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherGraspComponent.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "Engine/StaticMesh.h"
#include <Components/TextRenderComponent.h>
#include "PickupActor.h"
#include <Components/BoxComponent.h>
#include "BowActor.h"
#include "SwordActor.h"
#include <Kismet/GameplayStatics.h>
#include "WarriorPlayer.h"

UArcherGraspComponent::UArcherGraspComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UArcherGraspComponent::BeginPlay()
{
	Super::BeginPlay();


}


void UArcherGraspComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UArcherGraspComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(grip_right, ETriggerEvent::Started, this, &UArcherGraspComponent::GripRightAction);
	//PlayerInputComponent->BindAction(grip_right, ETriggerEvent::Completed, this, &UArcherGraspComponent::GripRightReleased);
}

void UArcherGraspComponent::GripRightAction(const struct FInputActionValue& value)
{
	GrabObject(player->rightHand);
	FVector center = player->rightHand->GetComponentLocation();
	DrawDebugSphere(GetWorld(), center, grabDistance, 30, FColor::Red, false, -1, 0, 1);
}

void UArcherGraspComponent::GripRightReleased(const struct FInputActionValue& value)
{
	ReleaseObject(player->rightHand);
	bIsGrab = false;
}

void UArcherGraspComponent::GrabObject(USkeletalMeshComponent* selectHand)
{
	// SphereTrace 방식
	FVector center = selectHand->GetComponentLocation();
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

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

			grabedObject->gripRot = FRotator(-70, 0, -90);
			grabedObject->AttachToComponent(selectHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GrabPoint"));

			grabedObject->SetActorRelativeLocation(grabedObject->gripOffset);
			grabedObject->SetActorRelativeRotation(grabedObject->gripRot);
		}
	}

	bIsGrab = true;
}

void UArcherGraspComponent::ReleaseObject(USkeletalMeshComponent* selectHand)
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

		grabedObject = nullptr;
	}
}