// Belong to kosar 


#include "AbilitySystem/GasAttributeSet.h"
#include "Net/UnrealNetwork.h"


UGasAttributeSet::UGasAttributeSet( )
{
    InitHealth(50.f);
    InitMaxHealth(100.f);
    InitMana(100.f);
    InitMaxMana(100.f);

}

void UGasAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Replicate the Health attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Health, COND_None, REPNOTIFY_Always);
    // Replicate the MaxHealth attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    // Replicate the Mana attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    // Replicate the MaxMana attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UGasAttributeSet::OnRep_Health(const FGameplayAttributeData &OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Health, OldHealth);
}

void UGasAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, MaxHealth, OldMaxHealth);
}

void UGasAttributeSet::OnRep_Mana(const FGameplayAttributeData &OldMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Mana, OldMana);
}

void UGasAttributeSet::OnRep_MaxMana(const FGameplayAttributeData &OldMaxMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, MaxMana, OldMaxMana);
}
