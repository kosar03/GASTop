// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/GasWidgetController.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GASTOP_API UOverlayWidgetController : public UGasWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;


	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:

	void HealthChanged(const struct FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const struct FOnAttributeChangeData& Data) const;

	void ManaChanged(const struct FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const struct FOnAttributeChangeData& Data) const;
};
