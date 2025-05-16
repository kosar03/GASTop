// Belong to kosar 


#include "Player/GasPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/EnemyInterface.h"


AGasPlayerController::AGasPlayerController()
{
    bReplicates = true;

}

void AGasPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    // Add any custom player tick logic here
    CursorTrace();
    
}

void AGasPlayerController::BeginPlay()
{
    Super::BeginPlay();

    check(GasContext);

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(GasContext, 0);
    }

    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
    
}


void AGasPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
     
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGasPlayerController::Move);
}

void AGasPlayerController::Move(const struct FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    APawn* ControlledPawn = GetPawn();
    if (ControlledPawn)
    {
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
        ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
    }
}

void AGasPlayerController::CursorTrace()
{
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit); 
    if (!CursorHit.bBlockingHit) return;

    LastActor = NowActor;
    NowActor = Cast<IEnemyInterface>(CursorHit.GetActor());

    if (!LastActor)
    {
        if (NowActor)
        {
            NowActor->HighlightActor();
        }
    }
    else 
    {
        if (!NowActor)
        {
            LastActor->UnHighlightActor();        
        }
        else 
        {
            if (LastActor != NowActor)
            {
                LastActor->UnHighlightActor();
                NowActor->HighlightActor();
            }
        }
    }


}