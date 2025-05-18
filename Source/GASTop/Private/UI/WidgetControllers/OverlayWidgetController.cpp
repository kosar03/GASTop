// Belong to kosar 


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "AbilitySystem/GasAttributeSet.h"
#include "AbilitySystem/GasAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
    const UGasAttributeSet* GasAttributeSet = CastChecked<UGasAttributeSet>(AttributeSet);

    OnHealthChanged.Broadcast(GasAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(GasAttributeSet->GetMaxHealth());

    OnManaChanged.Broadcast(GasAttributeSet->GetMana());
    OnMaxManaChanged.Broadcast(GasAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    const UGasAttributeSet* GasAttributeSet = CastChecked<UGasAttributeSet>(AttributeSet);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GasAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GasAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GasAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GasAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

    Cast<UGasAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
        [this](const FGameplayTagContainer& AssetTags) -> void
        {
            for (const FGameplayTag& Tag : AssetTags)
            {
                // "A.1".MatchesTag("A") == true, "A".MatchesTag("A") == false.
                FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
                bool bIsMessageTag = Tag.MatchesTag(MessageTag); 
                if (bIsMessageTag)
                {
                    const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
                    MessageWidgetRow.Broadcast(*Row);

                }
            }   
        }
    );
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData &Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData &Data) const
{
    OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData &Data) const
{
    OnManaChanged.Broadcast(Data.NewValue);    
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData &Data) const
{
    OnMaxManaChanged.Broadcast(Data.NewValue);
}
