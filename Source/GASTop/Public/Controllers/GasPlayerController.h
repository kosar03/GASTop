// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GasPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GASTOP_API AGasPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGasPlayerController();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> GasContext;
};
