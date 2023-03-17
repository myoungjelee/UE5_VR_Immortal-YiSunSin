// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumActor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ADrumActor::ADrumActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compDrum = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SetRootComponent(compDrum);
	compDrum->SetSphereRadius(40);
	compDrum->SetRelativeScale3D(FVector(0.75f));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	compMesh->SetupAttachment(compDrum);
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	compMesh->SetRelativeRotation(FRotator(90, 0, 90));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Drum/SM_Drum.SM_Drum'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}

}

// Called when the game starts or when spawned
void ADrumActor::BeginPlay()
{
	Super::BeginPlay();
	
	compDrum->OnComponentBeginOverlap.AddDynamic(this, &ADrumActor::OnDrum);
}

// Called every frame
void ADrumActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector p0 = GetActorLocation();
	FVector vt = FVector::BackwardVector * 500 * DeltaTime;
	SetActorLocation(p0 + vt);
}

void ADrumActor::OnDrum(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp->GetName().Contains(TEXT("Stick")))
	{
		//이펙트를 생성한다.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), drumEffect, GetActorLocation(), GetActorRotation(), FVector3d(0.25));
		//드럼 액터를 파괴한다
		Destroy();
		//UI 점수 1점씩 올린다
		
	}
}


