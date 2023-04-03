// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "PlayerBase.h"
#include "EnhancedInputComponent.h"
#include "WarriorPlayer.h"

UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AWarriorPlayer>(GetOwner());
}

void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMoveComponent::SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(rightThumbstick, ETriggerEvent::Triggered, this, &UMoveComponent::Move);
	PlayerInputComponent->BindAction(leftThumbstick, ETriggerEvent::Triggered, this, &UMoveComponent::RotateAxis);
}

// 플레이어 이동
void UMoveComponent::Move(const FInputActionValue& value)
{
	FVector2D val = value.Get<FVector2D>();
	FVector forwardDirection = FVector(1, 0, 0) * val.Y;
	player->AddActorLocalOffset(forwardDirection * moveSpeed);
}

// 플레이어 회전
void UMoveComponent::RotateAxis(const FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	player->AddControllerPitchInput(axis.Y * -1.0f);
	player->AddControllerYawInput(axis.X);
}