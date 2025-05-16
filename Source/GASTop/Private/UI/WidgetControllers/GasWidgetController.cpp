// Belong to kosar 


#include "UI/WidgetControllers/GasWidgetController.h"


void UGasWidgetController::SetWidgetControllerParams(const FWidgetControllerParams &WCParams)
{
    PlayerController = WCParams.PlayerController;
    PlayerState = WCParams.PlayerState;
    AbilitySystemComponent = WCParams.AbilitySystemComponent;
    AttributeSet = WCParams.AttributeSet;
}

void UGasWidgetController::BroadcastInitialValues()
{

}

void UGasWidgetController::BindCallbacksToDependencies()
{
    
}