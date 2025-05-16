// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GasWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class GASTOP_API UGasWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;	

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<class UAttributeSet> AttributeSet;

};
