// Belong to kosar 


#include "Characters/GasCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GasPlayerState.h"
#include "AbilitySystem/GasAbilitySystemComponent.h"
#include "Player/GasPlayerController.h"
#include "UI/HUD/GasHUD.h"


AGasCharacter::AGasCharacter()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(CameraBoom);  

    GetCharacterMovement()->bOrientRotationToMovement = true; 
    GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); 
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true; 

    bUseControllerRotationYaw = false; 
    bUseControllerRotationPitch = false; 
    bUseControllerRotationRoll = false;
}

void AGasCharacter::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);
    
    // Init the ability actor info for the server
    InitAbilityActorInfo();

}

void AGasCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    
    // Init the ability actor info for the client
    InitAbilityActorInfo();
}

void AGasCharacter::InitAbilityActorInfo()
{
    AGasPlayerState* GasPlayerState = GetPlayerState<AGasPlayerState>();
    check(GasPlayerState);

    AbilitySystemComponent = GasPlayerState->GetAbilitySystemComponent();
    AbilitySystemComponent->InitAbilityActorInfo(GasPlayerState, this);
    AttributeSet = GasPlayerState->GetAttributeSet();

    AGasPlayerController* GasPlayerController = Cast<AGasPlayerController>(GetController());
    if (GasPlayerController)
    {
        AGasHUD* GasHUD = Cast<AGasHUD>(GasPlayerController->GetHUD());
        if (GasHUD)
        {
            GasHUD->InitOverlay(GasPlayerController, GasPlayerState, AbilitySystemComponent, AttributeSet);
        }
    }
}
