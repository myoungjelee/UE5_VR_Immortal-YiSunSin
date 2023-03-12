// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "PuzzlePlayer.h"
#include <MotionControllerComponent.h>
#include <Misc/OutputDeviceNull.h>


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

	params_L.AddIgnoredActor(player);
	params_R.AddIgnoredActor(player);
}


// Called every frame
void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	startLoc_L = player->controller_Left->GetComponentLocation();
	endLoc_L = player->controller_Left->GetComponentLocation() + (player->controller_Left->GetForwardVector() + (player->controller_Left->GetUpVector() * -1)) * 2000;
	hit_L = GetWorld()->LineTraceSingleByChannel(hitInfo_L, startLoc_L, endLoc_L, ECC_Visibility, params_L);

	if (hit_L)
	{
		if (hitPuzzle_L == nullptr)
		{
			if (hitInfo_L.GetActor()->GetName().Contains(TEXT("Puzzle")))
			{
				FString funcName_L = TEXT("LightOn");
				FOutputDeviceNull ar_L;
				hitInfo_L.GetActor()->CallFunctionByNameWithArguments(*funcName_L, ar_L, NULL, true);
				hitPuzzle_L = hitInfo_L.GetActor();
			}
		}
		else if (hitPuzzle_L != nullptr)
		{
			FString funcName_hitPuzzle_L = TEXT("LightOff");
			FOutputDeviceNull ar_hitPuzzle_L;
			hitPuzzle_L->CallFunctionByNameWithArguments(*funcName_hitPuzzle_L, ar_hitPuzzle_L, NULL, true);
			hitPuzzle_L = nullptr;

			if (hitInfo_L.GetActor()->GetName().Contains(TEXT("Puzzle")))
			{
				FString funcName_L = TEXT("LightOn");
				FOutputDeviceNull ar_L;
				hitInfo_L.GetActor()->CallFunctionByNameWithArguments(*funcName_L, ar_L, NULL, true);
				hitPuzzle_L = hitInfo_L.GetActor();
			}
		}
	}

	startLoc_R = player->controller_Right->GetComponentLocation();
	endLoc_R = player->controller_Right->GetComponentLocation() + (player->controller_Right->GetForwardVector() + (player->controller_Right->GetUpVector() * -1)) * 2000;
	hit_R = GetWorld()->LineTraceSingleByChannel(hitInfo_R, startLoc_R, endLoc_R, ECC_Visibility, params_R);

	if (hit_R)
	{
		if (hitInfo_R.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			FString funcName = TEXT("LightOn");
			FOutputDeviceNull ar;
			hitInfo_R.GetActor()->CallFunctionByNameWithArguments(*funcName, ar, NULL, true);
		}

	}
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

			FString funcName = TEXT("LightOn");
			FOutputDeviceNull ar;
			grabedPuzzle_L->CallFunctionByNameWithArguments(*funcName, ar, NULL, true);
		}
	}

	DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Blue, false, 3, 0, 3);
}

void UWidgetPointerComponent::ReleasedPuzzle_L()
{
	if (grabedPuzzle_L != nullptr)
	{
		grabedPuzzle_L->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		FString funcName = TEXT("LightOff");
		FOutputDeviceNull ar;
		grabedPuzzle_L->CallFunctionByNameWithArguments(*funcName, ar, NULL, true);

		grabedPuzzle_L = nullptr;
	}
}

void UWidgetPointerComponent::GribedPuzzle_R()
{
	FVector startLoc = player->controller_Right->GetComponentLocation();
	FVector endLoc = player->controller_Right->GetComponentLocation() + (player->controller_Right->GetForwardVector() + (player->controller_Right->GetUpVector() * -1)) * 2000;
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
	if (grabedPuzzle_R != nullptr)
	{
		grabedPuzzle_R->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		grabedPuzzle_R = nullptr;
	}
}

