// Belong to kosar 


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/GasAttributeSet.h"
#include "Interfaces/CombatInterface.h"


UMMC_MaxMana::UMMC_MaxMana()
{
    // Initialize the attribute capture definition for Intelligence
    IntelligenceDef.AttributeToCapture = UGasAttributeSet::GetIntelligenceAttribute();
    IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    IntelligenceDef.bSnapshot = false;

    // Add the attribute capture definition to the relevant attributes
    RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Get tags from source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameter;
    EvaluationParameter.SourceTags = SourceTags;
    EvaluationParameter.TargetTags = TargetTags;

    float Intelligence = 0.0f;
    GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameter, Intelligence);
    Intelligence = FMath::Max<float>(Intelligence, 0.0f); // Ensure Intelligence is not negative

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

    return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}