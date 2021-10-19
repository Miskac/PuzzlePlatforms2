// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "ServerRow.h"
#include "Components/TextBlock.h"


UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UUserWidget>ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
    if(ServerRowBPClass.Class == nullptr) return;

    ServerRowClass = ServerRowBPClass.Class;
}

void UMainMenu::SetServerList(TArray<FServerData> ServerNames) 
{
    UWorld* World = this->GetWorld();
    if(World == nullptr) return;

    ServerList->ClearChildren();
    
    uint32 i =0;
    for(const FServerData& ServerData : ServerNames)
    {
        if(ServerRowClass == nullptr) return;

        UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
        if(Row == nullptr) return;

        Row->ServerName->SetText(FText::FromString(ServerData.Name));
        Row->HostUser->SetText(FText::FromString(ServerData.HostUsername));
        FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
        Row->ConncetionFraction->SetText(FText::FromString(FractionText));
        Row->Setup(this, i);
        ++i;

        ServerList->AddChild(Row);
    }
    
}

void UMainMenu::SelectIndex(uint32 Index) 
{
    SelectedIndex = Index;

    UpdateChildren();
}

bool UMainMenu::Initialize() 
{
    bool Success = Super::Initialize();

    if(!Success) return false;

    if(Host == nullptr) return false;
    Host->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);

    if(Join == nullptr) return false;
    Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

    if(Cancel == nullptr) return false;
    Cancel->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenu);

    if(JoinServerButton == nullptr) return false;
    JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    if(QuitButton == nullptr) return false;
    QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);

    if(ConfirmHostMenuButton == nullptr) return false;
    ConfirmHostMenuButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

    if(CancelHostMenuButton == nullptr) return false;
    CancelHostMenuButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenu);

    return true;
}

void UMainMenu::HostServer() 
{
    if(MenuInterface != nullptr) 
    {
        FString ServerName = ServerHostName->Text.ToString();
        MenuInterface->Host(ServerName);
    }


}

void UMainMenu::OpenHostMenu() 
{
    if(MenuSwitcher == nullptr) return;
    if(HostMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::JoinServer() 
{
    if(SelectedIndex.IsSet() && MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Selected Index %d"), SelectedIndex.GetValue());
        MenuInterface->Join(SelectedIndex.GetValue());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Selected Index not set"));
    }
        // if(IPAddressField == nullptr) return;
        // const FString Addres = IPAddressField->GetText().ToString();
}

void UMainMenu::OpenJoinMenu() 
{
    if(MenuSwitcher == nullptr) return;
    if(JoinMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
    if(MenuInterface != nullptr)
    {
        MenuInterface->RefreshServerList();
    } 
}

void UMainMenu::BackToMainMenu() 
{
    if(MenuSwitcher == nullptr) return;
    if(MainMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(MainMenu);

}

void UMainMenu::QuitGame() 
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if(PlayerController == nullptr) return;
    PlayerController->ConsoleCommand(TEXT("quit"));
}

void UMainMenu::UpdateChildren() 
{
    for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
    {
        UServerRow* Row = Cast<UServerRow>(ServerList->GetChildAt(i));
        if(Row !=nullptr)
        {
            Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
        }
    }
}
