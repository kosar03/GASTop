// Belong to kosar 


#include "Characters/GasEnemy.h"
#include "GasTop/GasTop.h"
#include "AbilitySystem/GasAbilitySystemComponent.h"
#include "AbilitySystem/GasAttributeSet.h"

AGasEnemy::AGasEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // 自动导致蓝图碰撞预设变为Custom

    AbilitySystemComponent = CreateDefaultSubobject<UGasAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UGasAttributeSet>(TEXT("AttributeSet"));
}

void AGasEnemy::HighlightActor()
{
    GetMesh()->SetRenderCustomDepth(true);
    GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

    Weapon->SetRenderCustomDepth(true);
    Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

void AGasEnemy::UnHighlightActor()
{
    GetMesh()->SetRenderCustomDepth(false);
    
    Weapon->SetRenderCustomDepth(false);
}

void AGasEnemy::BeginPlay()
{
    Super::BeginPlay();

    InitAbilityActorInfo();
}

void AGasEnemy::InitAbilityActorInfo()
{
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        Cast<UGasAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); 
    }

}