// Fill out your copyright notice in the Description page of Project Settings.


#include "DrumActor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
ADrumActor::ADrumActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compDrum = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SetRootComponent(compDrum);
	compDrum->SetSphereRadius(40);

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	compMesh->SetupAttachment(compDrum);
	compMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

}

void ADrumActor::OnDrum(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetName().Contains(TEXT("Node")) && OtherComp->GetName().Contains(TEXT("Stick")))
	{
		//손에 진동을 주기위해 bHit 값을 true 로 바꿔준다
// 		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitHaptic, EControllerHand::Right, 1, false);
// 		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitHaptic, EControllerHand::Left, 1, false);
		bHit = true;
		//이펙트를 생성한다

		//노드 액터를 파괴한다

		//UI 점수 1점씩 올린다

	}

}

