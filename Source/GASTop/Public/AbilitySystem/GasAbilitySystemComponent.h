// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GasAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*自己所有的尚未Granted的AssetTags*/);


/**
 * 
 */
UCLASS()
class GASTOP_API UGasAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// 会在Character的InitAbilityActorInfo()后调用
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
protected:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
