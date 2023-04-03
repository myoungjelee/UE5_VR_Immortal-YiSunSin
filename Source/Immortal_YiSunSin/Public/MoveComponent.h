
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMMORTAL_YISUNSIN_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* rightThumbstick;

	UPROPERTY(EditAnywhere, Category = Inputs)
	class UInputAction* leftThumbstick;

private:
	class AWarriorPlayer* player;

	float moveSpeed = 60.0f;

	void Move(const struct FInputActionValue& value);
	void RotateAxis(const struct FInputActionValue& value);
};
