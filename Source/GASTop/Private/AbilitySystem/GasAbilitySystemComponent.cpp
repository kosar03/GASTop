// Belong to kosar 


#include "AbilitySystem/GasAbilitySystemComponent.h"


void UGasAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);
}

void UGasAbilitySystemComponent::EffectApplied(UAbilitySystemComponent *AbilitySystemComponent, const FGameplayEffectSpec &EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
    FGameplayTagContainer TagContainer;
    EffectSpec.GetAllAssetTags(TagContainer);

    EffectAssetTags.Broadcast(TagContainer); 

}