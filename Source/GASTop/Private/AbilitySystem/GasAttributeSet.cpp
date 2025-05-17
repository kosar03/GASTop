// Belong to kosar 


#include "AbilitySystem/GasAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"


UGasAttributeSet::UGasAttributeSet( )
{
    InitHealth(50.f);
    InitMaxHealth(100.f);
    InitMana(50.f);
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


