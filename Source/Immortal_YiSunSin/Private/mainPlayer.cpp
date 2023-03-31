// Fill out your copyright notice in the Description page of Project Settings.


#include "mainPlayer.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <HeadMountedDisplayFunctionLibrary.h>
#include <Components/SkeletalMeshComponent.h>
#include <MotionControllerComponent.h>
#include <Camera/CameraComponent.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AmainPlayer::AmainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head Mesh"));
	headMesh->SetupAttachment(cam);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	controllerLeft = CreateDefaultSubobject<UMotionControllerComponent>("Left Controller");
	controllerLeft->SetupAttachment(RootComponent);
	controllerLeft->MotionSource = "Left";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(controllerLeft);
	leftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftHand->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f));

	controllerRight = CreateDefaultSubobject<UMotionControllerComponent>("Right Controller");
	controllerRight->SetupAttachment(RootComponent);
	controllerRight->MotionSource = "Right";

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(controllerRight);
	rightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	rightHand->SetRelativeRotation(FRotator(85.0f, 0.0f, 90.0f));

	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void AmainPlayer::BeginPlay()
{
	Super::BeginPlay();
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
	

	subsys->AddMappingContext(inputMapping, 0);
}

// Called every frame
void AmainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsShowLine)
	{
		DrawMoveLine();
	}
}

// Called to bind functionality to input
void AmainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Move Input Binding
	enhancedInputComponent->BindAction(thumbstickR, ETriggerEvent::Triggered, this, &AmainPlayer::Move);
	enhancedInputComponent->BindAction(thumbstickL, ETriggerEvent::Triggered, this, &AmainPlayer::RotateAxis);
	enhancedInputComponent->BindAction(btnB, ETriggerEvent::Started, this, &AmainPlayer::ShowLine);
	enhancedInputComponent->BindAction(btnB, ETriggerEvent::Completed, this, &AmainPlayer::HideLine);
}

void AmainPlayer::Recenter()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AmainPlayer::Move(const struct FInputActionValue& value)
{
	FVector2D val = value.Get<FVector2D>();
	FVector direction = FVector(val.Y, val.X, 0);

	AddMovementInput(direction.GetSafeNormal(), 1, false);
}

void AmainPlayer::RotateAxis(const struct FInputActionValue& value)
{
	FVector2D axis = value.Get<FVector2D>();

	//axis 값을 이용해서 캐릭터(콘트롤러)를 회전한다.
	AddControllerYawInput(axis.X);
}

void AmainPlayer::Teleport()
{
	// 가리킨 지점으로 순간 이동(즉시 좌표 변경)한다.
	FVector targetLoc = lineLoc[lineLoc.Num() - 1];
	targetLoc.Z += GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	SetActorLocation(targetLoc, false, nullptr, ETeleportType::None);

	/*if (spawned_fx != nullptr)
	{
		spawned_fx->niagara_fx->SetVisibility(false);
	}*/
}

void AmainPlayer::DrawMoveLine()
{
	// 이동할 곡선을 화면에 그린다.
	// 1. 이동할 위치 구간을 구한다.(TArray<FVector>)
	// 1-1. p = p0 + vt - 0.5 * g * t^2

	float timeInterval = 0.02f;
	int32 timeSegment = 50;

	//FVector dir = (FVector::ForwardVector + FVector::UpVector);
	//dir = player->leftHand->GetComponentTransform().TransformVector(dir);

	//왼손 모델링의 로컬 좌표에 맞춰서 forward 방향과 up 방향을 다시 계산한다.
	FVector handForward = FRotationMatrix(rightHand->GetComponentRotation()).GetUnitAxis(EAxis::Y);
	FVector handUp = FRotationMatrix(rightHand->GetComponentRotation()).GetUnitAxis(EAxis::X) * -1;
	// 다시 계산한 손 방향으로 dir을 구한다.
	FVector dir = handForward + handUp;
	
	lineLoc.Empty();
	for (int32 i = 0; i < timeSegment; i++)
	{
		// 소요시간
		float timeTaken = timeInterval * i;
		// p = p0 + vt
		FVector prediction = rightHand->GetComponentLocation() + dir.GetSafeNormal() * power * timeTaken;

		// p.Z -= 0.5 * g * t^2
		prediction.Z += 0.5f * GetWorld()->GetDefaultGravityZ() * timeTaken * timeTaken;

		// 1-2. 0.1초씩 0~50번째 구간을 계산해서 배열에 넣는다.
		lineLoc.Add(prediction);

		// 라인트레이스를 구간마다 체크한다.
		FHitResult hitInfo;

		if (i > 0)
		{
			if (GetWorld()->LineTraceSingleByChannel(hitInfo, lineLoc[i - 1], lineLoc[i], ECC_Visibility))
			{
				// 부딪힌 지점을 마지막 좌표로 넣고 반복문을 강제 종료한다. 
				lineLoc.Add(hitInfo.ImpactPoint);
				break;
			}
		}
	}

	// 2. 앞에서 구한 위치 마다 선으로 연결한 그림을 그린다(DrawLine).
	for (int32 i = 0; i < lineLoc.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), lineLoc[i], lineLoc[i + 1], debugColor, false, -1, 0, 2);
	}

	//// 텔레포트 링 이펙트를 마지막 라인 위치에 배치한다.
	//if (spawned_fx == nullptr)
	//{
	//	// 이펙트를 생성한다.
	//	spawned_fx = currentWorld->SpawnActor<ATeleportRingActor>(teleport_fx, lineLoc[lineLoc.Num() - 1], FRotator::ZeroRotator);
	//}
	//else
	//{
	//	// 안보이게 처리된 이펙트를 다시 보이게 한다.
	//	spawned_fx->niagara_fx->SetVisibility(true);
	//	spawned_fx->SetActorLocation(lineLoc[lineLoc.Num() - 1]);
	//}
}

void AmainPlayer::ShowLine()
{
	bIsShowLine = true;
}

void AmainPlayer::HideLine()
{
	bIsShowLine = false;
	Teleport();
	TeleportFade();
}

void AmainPlayer::TeleportFade()
{
	// 카메라를 Fade in 한다.
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(0, 1.0f, 1.0f, FLinearColor::Black);

	FTimerHandle fadeTimer;
	GetWorld()->GetTimerManager().SetTimer(fadeTimer, this, &AmainPlayer::Teleport, 1.0f, false);
} 
