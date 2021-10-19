// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup() 
{
    this->AddToViewport();

    UWorld* World = GetWorld();
    if(World == nullptr) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();

    if(PlayerController == nullptr) return;

    FInputModeUIOnly InputModeData;

    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);

    PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) 
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    this->RemoveFromViewport();
    UWorld* World = GetWorld();
    if (!ensure(World != nullptr))
        return;
    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController != nullptr))
        return;
    FInputModeGameOnly InputMode;
    PlayerController->SetInputMode(InputMode);
    PlayerController->bShowMouseCursor = false;
}

void UMenuWidget::SetMenuInterface(IMenuInterface* _MenuInterface) 
{
    this->MenuInterface = _MenuInterface;
}