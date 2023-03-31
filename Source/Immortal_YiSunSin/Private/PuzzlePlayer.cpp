// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlayer.h"
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "GraspComponent.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include <GameFramework/PlayerController.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>
#include "WidgetPointerComponent.h"
#include <Misc/OutputDeviceNull.h>
#include <UMG/Public/Components/WidgetComponent.h>
#include <Sound/SoundBase.h>
#include <Components/AudioComponent.h>
// Sets default values
APuzzlePlayer::APuzzlePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>("Cam");
	cam->SetupAttachment(RootComponent);

	controller_Left = CreateDefaultSubobject<UMotionControllerComponent>("Left Controller");
	controller_Left->SetupAttachment(RootComponent);
	controller_Left->MotionSource = "Left";

	mesh_Left = CreateDefaultSubobject<USkeletalMeshComponent>("Left Hand");
	mesh_Left->SetupAttachment(controller_Left);
	mesh_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh_Left->SetRelativeRotation(FRotator(-25.0f, 180.0f, 90.0f));

	widgetPointer_Left = CreateDefaultSubobject<UWidgetInteractionComponent>("Left Pointer");
	widgetPointer_Left->SetupAttachment(controller_Left);
	widgetPointer_Left->InteractionDistance = 2000;
	widgetPointer_Left->bShowDebug = true;
	widgetPointer_Left->DebugColor = FColor::Red;
	widgetPointer_Left->SetRelativeRotation(FRotator(-45,0,0));

	controller_Right = CreateDefaultSubobject<UMotionControllerComponent>("Right Controller");
	controller_Right->SetupAttachment(RootComponent);
	controller_Right->MotionSource = "Right";

	mesh_Right = CreateDefaultSubobject<USkeletalMeshComponent>("Right Hand");
	mesh_Right->SetupAttachment(controller_Right);
	mesh_Right->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mesh_Right->SetRelativeRotation(FRotator(25.0f, 0.0f, 90.0f));

	widgetPointer_Right = CreateDefaultSubobject<UWidgetInteractionComponent>("Right Pointer");
	widgetPointer_Right->SetupAttachment(controller_Right);
	widgetPointer_Right->InteractionDistance = 2000;
	widgetPointer_Right->bShowDebug = true;
	widgetPointer_Right->DebugColor = FColor::Red;
	widgetPointer_Right->SetRelativeRotation(FRotator(-45, 0, 0));

	pauseWidget = CreateDefaultSubobject<UWidgetComponent>("PauseWidget");
	pauseWidget->SetupAttachment(RootComponent);
	pauseWidget->SetVisibility(false);
	pauseWidget->SetCollisionProfileName(TEXT("NoCollision"));
	pauseWidget->SetRelativeLocation(FVector(700,0,300));
	pauseWidget->SetRelativeRotation(FRotator(0,180,0));
	pauseWidget->SetDrawSize(FVector2D(1920, 1080));

	gameOverWidget = CreateDefaultSubobject<UWidgetComponent>("GameOverWidget");
	gameOverWidget->SetupAttachment(RootComponent);
	gameOverWidget->SetVisibility(false);
	gameOverWidget->SetCollisionProfileName(TEXT("NoCollision"));
	gameOverWidget->SetRelativeLocation(FVector(700, 0, 300));
	gameOverWidget->SetRelativeRotation(FRotator(0, 180, 0));
	gameOverWidget->SetDrawSize(FVector2D(1920, 1080));

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	widgetPointerComp = CreateDefaultSubobject<UWidgetPointerComponent>("Pointer Component");

	ConstructorHelpers::FClassFinder<UUserWidget> tempPause(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MJ_Blueprint/Jigsaw/BP_Puzzle_PauseUI.BP_Puzzle_PauseUI_C'"));
	if (tempPause.Succeeded())
	{
		pauseWidget->SetWidgetClass(tempPause.Class);
	}

	ConstructorHelpers::FClassFinder<UUserWidget> tempGameOver(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MJ_Blueprint/Jigsaw/BP_Puzzle_GameOverUI.BP_Puzzle_GameOverUI_C'"));
	if (tempGameOver.Succeeded())
	{
		gameOverWidget->SetWidgetClass(tempGameOver.Class);
	}

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh_L(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));
	if (tempMesh_L.Succeeded())
	{
		mesh_Left->SetSkeletalMesh(tempMesh_L.Object);
	}

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh_R(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	if (tempMesh_R.Succeeded())
	{
		mesh_Right->SetSkeletalMesh(tempMesh_R.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Audios/MJ/PuzzleSound/PuzzleBGM.PuzzleBGM'"));
	if (tempSound.Succeeded())
	{
		gameSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void APuzzlePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

	subsys->AddMappingContext(inputMapping, 0);

	bgm = UGameplayStatics::SpawnSound2D(GetWorld(),gameSound);

}

// Called every frame
void APuzzlePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzlePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		widgetPointerComp->SetupPlayerInputComponent(enhancedInputComponent);
	}
}



