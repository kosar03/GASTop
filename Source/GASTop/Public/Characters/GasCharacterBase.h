// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GasCharacterBase.generated.h"

UCLASS(Abstract)
class GASTOP_API AGasCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGasCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
