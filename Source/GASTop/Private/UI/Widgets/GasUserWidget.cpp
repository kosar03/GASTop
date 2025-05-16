// Belong to kosar 


#include "UI/Widgets/GasUserWidget.h"


void UGasUserWidget::SetWidgetController(UObject *InWidgetController)
{
    WidgetController = InWidgetController;
    WidgetControllerSet();
}