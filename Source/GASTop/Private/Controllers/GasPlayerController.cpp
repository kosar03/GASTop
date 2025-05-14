// Belong to kosar 


#include "Controllers/GasPlayerController.h"
#include "EnhancedInputSubsystems.h"


AGasPlayerController::AGasPlayerController()
{
    bReplicates = true;

}

void AGasPlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(GasContext);

    class UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);
    Subsystem->AddMappingContext(GasContext, 0);

    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
    
}