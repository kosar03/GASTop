// Belong to kosar 


#include "AbilitySystem/GasAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"


UGasAttributeSet::UGasAttributeSet( )
{
    InitHealth(50.f);
    InitMana(50.f);

}

void UGasAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    /**
     * Primary Attributes
     */
    // Replicate the Strength attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    // Replicate the Intelligence attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
    // Replicate the Vigor attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
    // Replicate the Resilience attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Resilience, COND_None, REPNOTIFY_Always);

    /**
     * Secondary Attributes
     */
    // Replicate the Armor attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Armor, COND_None, REPNOTIFY_Always);
    // Replicate the ArmorPenetration attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
    // Replicate the BlockChance attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
    // Replicate the CriticalHitChance attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
    // Replicate the CriticalHitDamage attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
    // Replicate the CriticalHitResistance attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
    // Replicate the HealthRegeneration attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
    // Replicate the ManaRegeneration attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
    // Replicate the Health attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Health, COND_None, REPNOTIFY_Always);
    // Replicate the MaxHealth attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

    /**
     * Vital Attributes
     */
    // Replicate the Mana attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, Mana, COND_None, REPNOTIFY_Always);
    // Replicate the MaxMana attribute
    DOREPLIFETIME_CONDITION_NOTIFY(UGasAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

}

void UGasAttributeSet::PreAttributeChange(const FGameplayAttribute &Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
    if (Attribute == GetMaxHealthAttribute())
    {
        NewValue = FMath::Max(0.f, NewValue);
    }
    if (Attribute == GetManaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
    }
    if (Attribute == GetMaxManaAttribute())
    {
        NewValue = FMath::Max(0.f, NewValue);
    }


}

void UGasAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData &Data, FEffectProperties &Props) const
{
    Props.EffectContextHandle = Data.EffectSpec.GetContext();
    Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

    if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();

        Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
        if (!Props.SourceController && Props.SourceAvatarActor)
        {
            APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor);
            if (Pawn)
            {
                Props.SourceController = Pawn->GetController(); 
            }
        }
        if (Props.SourceController)
        {
            Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
        }
    }

    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
        Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);

    }
}

void UGasAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data)
{
    Super::PostGameplayEffectExecute(Data);
    
    FEffectProperties Props;
    SetEffectProperties(Data, Props);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxHealth()));
    }

}

void UGasAttributeSet::OnRep_Strength(const FGameplayAttributeData &OldStrength) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Strength, OldStrength);
}

void UGasAttributeSet::OnRep_Intelligence(const FGameplayAttributeData &OldIntelligence) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Intelligence, OldIntelligence);
}

void UGasAttributeSet::OnRep_Vigor(const FGameplayAttributeData &OldVigor) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Vigor, OldVigor);
}

void UGasAttributeSet::OnRep_Resilience(const FGameplayAttributeData &OldResilience) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Resilience, OldResilience);
}

void UGasAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData &OldManaRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UGasAttributeSet::OnRep_Armor(const FGameplayAttributeData &OldArmor) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Armor, OldArmor);
}

void UGasAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData &OldArmorPenetration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UGasAttributeSet::OnRep_BlockChance(const FGameplayAttributeData & OldBlockChance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, BlockChance, OldBlockChance);
}

void UGasAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData &OldCriticalHitChance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UGasAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData &OldCriticalHitResistance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UGasAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData &OldHealthRegeneration) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UGasAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData &OldCriticalHitDamage) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UGasAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, MaxHealth, OldMaxHealth);
}

void UGasAttributeSet::OnRep_MaxMana(const FGameplayAttributeData &OldMaxMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, MaxMana, OldMaxMana);
}

void UGasAttributeSet::OnRep_Health(const FGameplayAttributeData &OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Health, OldHealth);
}

void UGasAttributeSet::OnRep_Mana(const FGameplayAttributeData &OldMana) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGasAttributeSet, Mana, OldMana);
}

