// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "GasEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GASTOP_API AGasEnemy : public AGasCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AGasEnemy();

	/**
	 * Enemy Interface
	 */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	/**
	 * Combat Interface
	 */
	virtual int32 GetPlayerLevel() override { return Level; }

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
private:


};
