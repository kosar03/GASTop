// Belong to kosar 


#include "UI/HUD/GasHUD.h"
#include "UI/Widgets/GasUserWidget.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"

UOverlayWidgetController *AGasHUD::GetOverlayWidgetController(const FWidgetControllerParams &WCParams)
{
    if (!OverlayWidgetController)
    {
        if (!OverlayWidgetControllerClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetControllerClass is not set in AGasHUD"));
            return nullptr;
        }
        OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
        OverlayWidgetController->SetWidgetControllerParams(WCParams);
        OverlayWidgetController->BindCallbacksToDependencies();
        
    }
    return OverlayWidgetController;
}

void AGasHUD::InitOverlay(APlayerController *PC, APlayerState *PS, UAbilitySystemComponent *ASC, UAttributeSet *AS)
{
    checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is null, please set it in BP_AGasHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class is null, please set it in BP_AGasHUD"))

    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
    OverlayWidget = Cast<UGasUserWidget>(Widget);

    const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams); 
    
    OverlayWidget->SetWidgetController(WidgetController);
    WidgetController->BroadcastInitialValues();
    
    Widget->AddToViewport();
}
