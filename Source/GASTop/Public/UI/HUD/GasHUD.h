// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GasHUD.generated.h"

/**
 * 
 */
UCLASS()
class GASTOP_API AGasHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<class UGasUserWidget> OverlayWidget;

	class UOverlayWidgetController* GetOverlayWidgetController(const struct FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS);

protected:


private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<class UGasUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<class UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UOverlayWidgetController> OverlayWidgetControllerClass;
};
