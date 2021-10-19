// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitMenu.h"
#include "Components/Button.h"


bool UExitMenu::Initialize() 
{
    bool Success = Super::Initialize();

    if(!Success) return false;

    if(CancelButton == nullptr) return false;
    CancelButton->OnClicked.AddDynamic(this, &UExitMenu::Cancel);

    if(ExitButton == nullptr) return false;
    ExitButton->OnClicked.AddDynamic(this, &UExitMenu::BackToMenu);

    return true;

}



void UExitMenu::Cancel() 
{
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

void UExitMenu::BackToMenu() 
{
    if(MenuInterface != nullptr) 
    {
        MenuInterface->BackToMenu();
    }
}
