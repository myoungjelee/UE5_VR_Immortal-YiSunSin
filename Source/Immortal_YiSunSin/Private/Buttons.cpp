// Fill out your copyright notice in the Description page of Project Settings.


#include "Buttons.h"
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include "mainPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include "ShipMoving.h"
#include <Sound/SoundBase.h>

// Sets default values
AButtons::AButtons()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	SetRootComponent(body);
	body->SetRelativeScale3D(FVector(0.5f, 1.0f, 1.7f));

	bottom1 = CreateDefaultSubobject<UStaticMeshComponent>("Bottom1");
	bottom1->SetupAttachment(body);
	bottom1->SetRelativeLocation(FVector(40, -30, 50));
	bottom1->SetRelativeScale3D(FVector(0.4f, 0.2f, 0.2f));

	btn1 = CreateDefaultSubobject<UStaticMeshComponent>("Btn1");
	btn1->SetupAttachment(bottom1);

	box1 = CreateDefaultSubobject<UBoxComponent>("Box1");
	box1->SetupAttachment(btn1);
	box1->SetRelativeLocation(FVector(-100, 0, 22));
	box1->SetRelativeScale3D(FVector(1, 1, 0.1f));
	box1->SetBoxExtent(FVector(25));

	bottom2 = CreateDefaultSubobject<UStaticMeshComponent>("Bottom2");
	bottom2->SetupAttachment(body);
	bottom2->SetRelativeLocation(FVector(40, 0, 50));
	bottom2->SetRelativeScale3D(FVector(0.4f, 0.2f, 0.2f));

	btn2 = CreateDefaultSubobject<UStaticMeshComponent>("Btn2");
	btn2->SetupAttachment(bottom2);

	box2 = CreateDefaultSubobject<UBoxComponent>("Box2");
	box2->SetupAttachment(btn2);
	box2->SetRelativeLocation(FVector(-100, 0, 22));
	box2->SetRelativeScale3D(FVector(1, 1, 0.1f));
	box2->SetBoxExtent(FVector(25));

	bottom3 = CreateDefaultSubobject<UStaticMeshComponent>("Bottom3");
	bottom3->SetupAttachment(body);
	bottom3->SetRelativeLocation(FVector(40, 30, 50));
	bottom3->SetRelativeScale3D(FVector(0.4f, 0.2f, 0.2f));

	btn3 = CreateDefaultSubobject<UStaticMeshComponent>("Btn3");
	btn3->SetupAttachment(bottom3);

	box3 = CreateDefaultSubobject<UBoxComponent>("Box3");
	box3->SetupAttachment(btn3);
	box3->SetRelativeLocation(FVector(-100, 0, 22));
	box3->SetRelativeScale3D(FVector(1, 1, 0.1f));
	box3->SetBoxExtent(FVector(25));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBody(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempBody.Succeeded())
	{
		body->SetStaticMesh(tempBody.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/StarterContent/Materials/M_Rock_Marble_Polished.M_Rock_Marble_Polished'"));
	if (tempMat.Succeeded())
	{
		body->SetMaterial(0, tempMat.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBottom1(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Button/SM_Button_Bottom.SM_Button_Bottom'"));
	if (tempBottom1.Succeeded())
	{
		bottom1->SetStaticMesh(tempBottom1.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBtn1(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Button/SM_Button1.SM_Button1'"));
	if (tempBtn1.Succeeded())
	{
		btn1->SetStaticMesh(tempBtn1.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBottom2(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Button/SM_Button_Bottom.SM_Button_Bottom'"));
	if (tempBottom2.Succeeded())
	{
		bottom2->SetStaticMesh(tempBottom2.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBtn2(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Button/SM_Button2.SM_Button2'"));
	if (tempBtn2.Succeeded())
	{
		btn2->SetStaticMesh(tempBtn2.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBottom3(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Button/SM_Button_Bottom.SM_Button_Bottom'"));
	if (tempBottom3.Succeeded())
	{
		bottom3->SetStaticMesh(tempBottom3.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempBtn3(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Button/SM_Button3.SM_Button3'"));
	if (tempBtn3.Succeeded())
	{
		btn3->SetStaticMesh(tempBtn3.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Audios/MJ/buttons.buttons'"));
	if (tempSound.Succeeded())
	{
		btnSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void AButtons::BeginPlay()
{
	Super::BeginPlay();

	box1->OnComponentBeginOverlap.AddDynamic(this, &AButtons::BeginOverlapBtn1);
	box2->OnComponentBeginOverlap.AddDynamic(this, &AButtons::BeginOverlapBtn2);
	box3->OnComponentBeginOverlap.AddDynamic(this, &AButtons::BeginOverlapBtn3);

	player = Cast<AmainPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AmainPlayer::StaticClass()));
	ship = Cast<AShipMoving>(UGameplayStatics::GetActorOfClass(GetWorld(), AShipMoving::StaticClass()));

	pos = btn1->GetRelativeLocation();
	rot = FRotator::ZeroRotator;
}

// Called every frame
void AButtons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtons::BeginOverlapBtn1(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Contains(TEXT("Coll")))
	{

		UGameplayStatics::PlaySound2D(GetWorld(), btnSound);

		FVector loc = pos - FVector(0, 0, 10);
		FLatentActionInfo info;
		info.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(btn1, loc, rot, false, false, 0.3f, false, EMoveComponentAction::Move, info);

		if (ship->paddleMove)
		{
			ship->paddleMove = false;
		}
		else
		{
			ship->paddleMove = true;
		}

		FTimerHandle returnBtn;
		GetWorld()->GetTimerManager().SetTimer(returnBtn, this, &AButtons::ReturnBtn1, 0.4f, false);
// 		FLatentActionInfo info2;
// 		info.CallbackTarget = this;
// 		info.ExecutionFunction = TEXT("ReturnBtn");
// 		info.Linkage = 0;
// 		info.UUID = 0;
// 
// 		UKismetSystemLibrary::Delay(GetWorld(), 0.1f, info2);
	}
}

void AButtons::BeginOverlapBtn2(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UGameplayStatics::PlaySound2D(GetWorld(), btnSound);

	if (OtherComp->GetName().Contains(TEXT("Coll")))
	{
		FVector loc = pos - FVector(0, 0, 10);
		FLatentActionInfo info;
		info.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(btn2, loc, rot, false, false, 0.3f, false, EMoveComponentAction::Move, info);

		if (ship->bodyMove)
		{
			ship->bodyMove = false;
		}
		else
		{
			ship->bodyMove = true;
		}

		FTimerHandle returnBtn;
		GetWorld()->GetTimerManager().SetTimer(returnBtn, this, &AButtons::ReturnBtn2, 0.4f, false);
	}

}

void AButtons::BeginOverlapBtn3(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UGameplayStatics::PlaySound2D(GetWorld(), btnSound);

	if (OtherComp->GetName().Contains(TEXT("Coll")))
	{
		FVector loc = pos - FVector(0, 0, 10);
		FLatentActionInfo info;
		info.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(btn3, loc, rot, false, false, 0.3f, false, EMoveComponentAction::Move, info);

		if (ship->fire)
		{
			ship->fire = false;
		}
		else
		{
			ship->fire = true;
		}

		FTimerHandle returnBtn;
		GetWorld()->GetTimerManager().SetTimer(returnBtn, this, &AButtons::ReturnBtn3, 0.4f, false);
	}
}

void AButtons::ReturnBtn1()
{
	FLatentActionInfo info;
	info.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(btn1, pos, rot, false, false, 0.3f, false, EMoveComponentAction::Move, info);
}

void AButtons::ReturnBtn2()
{
	FLatentActionInfo info;
	info.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(btn2, pos, rot, false, false, 0.3f, false, EMoveComponentAction::Move, info);
}

void AButtons::ReturnBtn3()
{
	FLatentActionInfo info;
	info.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(btn3, pos, rot, false, false, 0.3f, false, EMoveComponentAction::Move, info);
}






