// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "PuzzlePlayer.h"
#include <MotionControllerComponent.h>

// Sets default values for this component's properties
UWidgetPointerComponent::UWidgetPointerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APuzzlePlayer>(GetOwner());

	
}


// Called every frame
void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(left_Grib, ETriggerEvent::Started, this, &UWidgetPointerComponent::GribedPuzzle_L);
	PlayerInputComponent->BindAction(left_Grib, ETriggerEvent::Completed, this, &UWidgetPointerComponent::ReleasedPuzzle_L);
	PlayerInputComponent->BindAction(right_Grib, ETriggerEvent::Started, this, &UWidgetPointerComponent::GribedPuzzle_R);
	PlayerInputComponent->BindAction(right_Grib, ETriggerEvent::Completed, this, &UWidgetPointerComponent::ReleasedPuzzle_R);
}

void UWidgetPointerComponent::GribedPuzzle_L()
{
	FVector startLoc = player->controller_Left->GetComponentLocation();
	FVector endLoc = player->controller_Left->GetComponentLocation() + (player->controller_Left->GetForwardVector() + (player->controller_Left->GetUpVector() * -1)) * 2000;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	if (GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, params))
	{
		if (hitInfo.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			hitInfo.GetActor()->AttachToComponent(player->mesh_Left, FAttachmentTransformRules::KeepWorldTransform, FName("PuzzlePoint_L"));
			grabedPuzzle_L = hitInfo.GetActor();
		}
	}

	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Blue, false, 3,0,3);
}

void UWidgetPointerComponent::ReleasedPuzzle_L()
{
	grabedPuzzle_L->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void UWidgetPointerComponent::GribedPuzzle_R()
{
	FVector startLoc = player->controller_Right->GetComponentLocation();
	FVector endLoc = player->controller_Right->GetComponentLocation() + (player->controller_Right->GetForwardVector() + (player->controller_Right->GetUpVector()*-1)) * 2000;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	if (GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, params))
	{
		if (hitInfo.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			hitInfo.GetActor()->AttachToComponent(player->mesh_Right, FAttachmentTransformRules::KeepWorldTransform, FName("PuzzlePoint_L"));
			grabedPuzzle_R = hitInfo.GetActor();
		}
	}

	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Green, false, 3, 0, 3);
}

void UWidgetPointerComponent::ReleasedPuzzle_R()
{
	grabedPuzzle_R->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

