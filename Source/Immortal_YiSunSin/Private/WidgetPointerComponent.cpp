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
		if (hitInfo_L.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			
		}
	}

	startLoc_R = player->controller_Right->GetComponentLocation();
	endLoc_R = player->controller_Right->GetComponentLocation() + (player->controller_Right->GetForwardVector() + (player->controller_Right->GetUpVector() * -1)) * 2000;
	hit_R = GetWorld()->LineTraceSingleByChannel(hitInfo_R, startLoc_R, endLoc_R, ECC_Visibility, params_R);

	if (hit_R)
	{
		if (hitInfo_R.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{

		}
	}
}

void UWidgetPointerComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(left_Trigger, ETriggerEvent::Started, this, &UWidgetPointerComponent::TriggedPuzzle_L);
	PlayerInputComponent->BindAction(left_Trigger, ETriggerEvent::Completed, this, &UWidgetPointerComponent::ReleasedPuzzle_L);
	PlayerInputComponent->BindAction(right_Trigger, ETriggerEvent::Started, this, &UWidgetPointerComponent::TriggedPuzzle_R);
	PlayerInputComponent->BindAction(right_Trigger, ETriggerEvent::Completed, this, &UWidgetPointerComponent::ReleasedPuzzle_R);
}

void UWidgetPointerComponent::TriggedPuzzle_L()
{
	if (hit_L)
	{
		if (hitInfo_L.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			hitInfo_L.GetActor()->AttachToComponent(player->mesh_Left, FAttachmentTransformRules::KeepWorldTransform, FName("PuzzlePoint_L"));
		}
	}

	DrawDebugLine(GetWorld(), startLoc_L, endLoc_L, FColor::Blue, false, 3,0,3);
}

void UWidgetPointerComponent::ReleasedPuzzle_L()
{

}

void UWidgetPointerComponent::TriggedPuzzle_R()
{
	if (hit_R)
	{
		if (hitInfo_R.GetActor()->GetName().Contains(TEXT("Puzzle")))
		{
			hitInfo_R.GetActor()->AttachToComponent(player->mesh_Right, FAttachmentTransformRules::KeepWorldTransform, FName("PuzzlePoint_R"));
		}
	}

	DrawDebugLine(GetWorld(), startLoc_R, endLoc_L, FColor::Green, false, 3, 0, 3);
}

void UWidgetPointerComponent::ReleasedPuzzle_R()
{

}

