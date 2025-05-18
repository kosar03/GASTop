// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASCharacterBase.h"
#include "GasCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASTOP_API AGasCharacter : public AGasCharacterBase
{
	GENERATED_BODY()

public:
	AGasCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComponent;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
};
