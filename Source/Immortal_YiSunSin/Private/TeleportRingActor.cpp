// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportRingActor.h"
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include <../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>

// Sets default values
ATeleportRingActor::ATeleportRingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	niagara_fx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport Ring"));
	niagara_fx->SetupAttachment(RootComponent);
	niagara_fx->SetRelativeScale3D(FVector(3));

	ConstructorHelpers::FObjectFinder<UNiagaraSystem> tempRing(TEXT("/Script/Niagara.NiagaraSystem'/Game/VRTemplate/VFX/NS_TeleportRing.NS_TeleportRing'"));
	if (tempRing.Succeeded())
	{
		niagara_fx->SetAsset(tempRing.Object);
	}
}

// Called when the game starts or when spawned
void ATeleportRingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportRingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

