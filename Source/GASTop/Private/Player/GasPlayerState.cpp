// Belong to kosar 


#include "Player/GasPlayerState.h"
#include "AbilitySystem/GasAbilitySystemComponent.h"
#include "AbilitySystem/GasAttributeSet.h"
#include "Net/UnrealNetwork.h"

AGasPlayerState::AGasPlayerState()
{
    NetUpdateFrequency = 100.f;

    AbilitySystemComponent = CreateDefaultSubobject<UGasAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UGasAttributeSet>(TEXT("AttributeSet"));

}

void AGasPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGasPlayerState, Level);
}

void AGasPlayerState::OnRep_Level(int32 OldLevel)
{
}