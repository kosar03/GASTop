// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GasUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GASTOP_API UGasUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
