// Belong to kosar 


#include "Player/GasPlayerState.h"
#include "AbilitySystem/GasAbilitySystemComponent.h"
#include "AbilitySystem/GasAttributeSet.h"

AGasPlayerState::AGasPlayerState()
{
    NetUpdateFrequency = 100.f;

    AbilitySystemComponent = CreateDefaultSubobject<UGasAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UGasAttributeSet>(TEXT("AttributeSet"));

}