// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmPlayer.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <HeadMountedDisplayFunctionLibrary.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystem.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include <Components/AudioComponent.h>
#include <Haptics/HapticFeedbackEffect_Base.h>
#include "MoviePlayerActor.h"

// Sets default values
ARhythmPlayer::ARhythmPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	l_Controller = CreateDefaultSubobject<UMotionControllerComponent>("LeftController");
	l_Controller->SetupAttachment(RootComponent);
	l_Controller->MotionSource = "Left";

	l_Stick = CreateDefaultSubobject<USphereComponent>("LeftStick");
	l_Stick->SetupAttachment(l_Controller);
	l_Stick->SetSphereRadius(10);
	l_Stick->SetRelativeLocation(FVector(17, 0, -10));
	l_Stick->SetRelativeRotation(FRotator(-110, 0, 0));

	l_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftMesh");
	l_Mesh->SetupAttachment(l_Stick);
	l_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	l_Mesh->SetRelativeScale3D(FVector(0.1f));
	l_Mesh->SetRelativeLocation(FVector(0, 0, -17.5f));
	
	widgetPointer_Left = CreateDefaultSubobject<UWidgetInteractionComponent>("Left Pointer");
	widgetPointer_Left->SetupAttachment(l_Controller);
	widgetPointer_Left->InteractionDistance = 2000;
	widgetPointer_Left->bShowDebug = false;
	widgetPointer_Left->DebugColor = FColor::Red;
	widgetPointer_Left->SetRelativeRotation(FRotator(-45, 0, 0));

	r_Controller = CreateDefaultSubobject<UMotionControllerComponent>("RightController");
	r_Controller->SetupAttachment(RootComponent);
	r_Controller->MotionSource = "Right";

	r_Stick = CreateDefaultSubobject<USphereComponent>("RightStick");
	r_Stick->SetupAttachment(r_Controller);
	r_Stick->SetSphereRadius(10);
	r_Stick->SetRelativeLocation(FVector(17, 0, -10));
	r_Stick->SetRelativeRotation(FRotator(-110, 0, 0));

	r_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RightMesh");
	r_Mesh->SetupAttachment(r_Stick);
	r_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	r_Mesh->SetRelativeScale3D(FVector(0.1f));
	r_Mesh->SetRelativeLocation(FVector(0, 0, -17.5f));

	widgetPointer_Right = CreateDefaultSubobject<UWidgetInteractionComponent>("Right Pointer");
	widgetPointer_Right->SetupAttachment(r_Controller);
	widgetPointer_Right->InteractionDistance = 2000;
	widgetPointer_Right->bShowDebug = false;
	widgetPointer_Right->DebugColor = FColor::Red;
	widgetPointer_Right->SetRelativeRotation(FRotator(-45, 0, 0));

	pauseWidget = CreateDefaultSubobject<UWidgetComponent>("PauseWidget");
	pauseWidget->SetupAttachment(RootComponent);
	pauseWidget->SetVisibility(false);
	pauseWidget->SetCollisionProfileName(TEXT("NoCollision"));
	pauseWidget->SetRelativeLocation(FVector(700, 0, 300));
	pauseWidget->SetRelativeRotation(FRotator(0, 180, 0));
	pauseWidget->SetDrawSize(FVector2D(1920,1080));

	gameOverWidget = CreateDefaultSubobject<UWidgetComponent>("GameOverWidget");
	gameOverWidget->SetupAttachment(RootComponent);
	gameOverWidget->SetVisibility(false);
	gameOverWidget->SetCollisionProfileName(TEXT("NoCollision"));
	gameOverWidget->SetRelativeLocation(FVector(700, 0, 300));
	gameOverWidget->SetRelativeRotation(FRotator(0, 180, 0));
	gameOverWidget->SetDrawSize(FVector2D(1920, 1080));

	ConstructorHelpers::FObjectFinder<UStaticMesh> leftMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Drum/SM_DrumStick.SM_DrumStick'"));
	if (leftMesh.Succeeded())
	{
		l_Mesh->SetStaticMesh(leftMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> rightMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/MJ/Drum/SM_DrumStick.SM_DrumStick'"));
	if (rightMesh.Succeeded())
	{
		r_Mesh->SetStaticMesh(rightMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UHapticFeedbackEffect_Base> tempHit(TEXT("/Script/Engine.HapticFeedbackEffect_Curve'/Game/MJ_Blueprint/Rhythm/RhythmHaptic.RhythmHaptic'"));
	if (tempHit.Succeeded())
	{
		hitHaptic = tempHit.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> tempBtn_X(TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerInput/GN/IA_btnX.IA_btnX'"));
	if (tempBtn_X.Succeeded())
	{
		x_Btn = tempBtn_X.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> tempTrigger_L(TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerInput/GN/IA_TriggerL.IA_TriggerL'"));
	if (tempTrigger_L.Succeeded())
	{
		left_Trigger = tempTrigger_L.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> tempTrigger_R(TEXT("/Script/EnhancedInput.InputAction'/Game/PlayerInput/GN/IA_TriggerR.IA_TriggerR'"));
	if (tempTrigger_R.Succeeded())
	{
		right_Trigger = tempTrigger_R.Object;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> tempPause(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MJ_Blueprint/Rhythm/BP_Rhythm_PauseUI.BP_Rhythm_PauseUI_C'"));
	if (tempPause.Succeeded())
	{
		pauseWidget->SetWidgetClass(tempPause.Class);
	}

	ConstructorHelpers::FClassFinder<UUserWidget> tempGameOver(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MJ_Blueprint/Rhythm/BP_Rhythm_GameOverUI.BP_Rhythm_GameOverUI_C'"));
	if (tempGameOver.Succeeded())
	{
		gameOverWidget->SetWidgetClass(tempGameOver.Class);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Audios/MJ/RhythmSound/Arirang.Arirang'"));
	if (tempSound.Succeeded())
	{
		arirang = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void ARhythmPlayer::BeginPlay()
{
	Super::BeginPlay();

	l_Stick->OnComponentBeginOverlap.AddDynamic(this, &ARhythmPlayer::OnDrum_Left);
	r_Stick->OnComponentBeginOverlap.AddDynamic(this, &ARhythmPlayer::OnDrum_Right);

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	moviePlayer = Cast<AMoviePlayerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMoviePlayerActor::StaticClass()));

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(inputMapping, 0);

	playerCon->SetControlRotation(FRotator(0));

	sound = UGameplayStatics::SpawnSound2D(GetWorld(), arirang);
}

// Called every frame
void ARhythmPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARhythmPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(x_Btn, ETriggerEvent::Started, this, &ARhythmPlayer::GamePause);
		enhancedInputComponent->BindAction(left_Trigger, ETriggerEvent::Started, this, &ARhythmPlayer::ClickWidget_L);
		enhancedInputComponent->BindAction(left_Trigger, ETriggerEvent::Completed, this, &ARhythmPlayer::ReleaseWidget_L);
		enhancedInputComponent->BindAction(right_Trigger, ETriggerEvent::Started, this, &ARhythmPlayer::ClickWidget_R);
		enhancedInputComponent->BindAction(right_Trigger, ETriggerEvent::Completed, this, &ARhythmPlayer::ReleaseWidget_R);
	}
}

void ARhythmPlayer::OnDrum_Left(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Drum")))
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitHaptic, EControllerHand::Left, 1, false);
	}	
}

void ARhythmPlayer::OnDrum_Right(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("Drum")))
	{
		GetWorld()->GetFirstPlayerController()->PlayHapticEffect(hitHaptic, EControllerHand::Right, 1, false);
	}
}

void ARhythmPlayer::GamePause()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
	if (sound != nullptr)
	{
		sound->SetPaused(true);
	}
	
	widgetPointer_Left->bShowDebug = true;
	widgetPointer_Right->bShowDebug = true;
	pauseWidget->SetVisibility(true);
	pauseWidget->SetCollisionProfileName(TEXT("interactionUI"));

	moviePlayer->PausedMovie();
}

void ARhythmPlayer::ClickWidget_L()
{
	widgetPointer_Left->PressPointerKey(EKeys::LeftMouseButton);
}

void ARhythmPlayer::ReleaseWidget_L()
{
	widgetPointer_Left->ReleasePointerKey(EKeys::LeftMouseButton);
}

void ARhythmPlayer::ClickWidget_R()
{
	widgetPointer_Right->PressPointerKey(EKeys::LeftMouseButton);
}

void ARhythmPlayer::ReleaseWidget_R()
{
	widgetPointer_Right->ReleasePointerKey(EKeys::LeftMouseButton);
}

