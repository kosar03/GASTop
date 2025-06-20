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

	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> GasContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);

	void CursorTrace();

	class IEnemyInterface* LastActor, *NowActor;
};
