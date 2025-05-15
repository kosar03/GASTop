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

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;

};
