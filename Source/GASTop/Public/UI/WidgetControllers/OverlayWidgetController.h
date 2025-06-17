// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/GasWidgetController.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGasUserWidget> MessageWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


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
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRow;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<class UDataTable> MessageWidgetDataTable;

	void HealthChanged(const struct FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const struct FOnAttributeChangeData& Data) const;

	void ManaChanged(const struct FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const struct FOnAttributeChangeData& Data) const;

	template<typename T>
	T* GetDataTableRowByTag(class UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
inline T *UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag &Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	
}
