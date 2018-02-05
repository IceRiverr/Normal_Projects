// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/ServerRowWidget.h"


UMainMenuWidget::UMainMenuWidget(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (ServerRowBPClass.Class != NULL)
	{
		ServerRowClass = ServerRowBPClass.Class;
	}
}

void UMainMenuWidget::SetServerList(const TArray<FServerData>& ServerNames)
{
	UWorld* World = this->GetWorld();
	if (ServerList && World)
	{
		ServerList->ClearChildren();
		
		uint32 Select = 0;
		for (const FServerData& ServerData : ServerNames)
		{
			UServerRowWidget* Row = CreateWidget<UServerRowWidget>(World, ServerRowClass);
			if (Row)
			{
				Row->SetUp(this, Select);
				Select++;

				Row->ServerName->SetText(FText::FromString(ServerData.ServerName));
				Row->HostUserName->SetText(FText::FromString(ServerData.HostUsername));
				FString Connection = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
				Row->ConnectionInfo->SetText(FText::FromString(Connection));
				
				ServerList->AddChild(Row);
			}
		}
	}
}

void UMainMenuWidget::SetSelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChilren();
}

bool UMainMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenHostMenu);
	}
	
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenJoinMenu);
	}
	
	if (CancleJoinMenuButton)
	{
		CancleJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenMainMenu);
	}
	
	if (ConfirmJoinMenuButton)
	{
		ConfirmJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinServer);
	}

	if (FreshServerButton)
	{
		FreshServerButton->OnClicked.AddDynamic(this, &UMainMenuWidget::FreshServer);
	}

	if (HostCancleButton)
	{
		HostCancleButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenMainMenu);
	}

	if (HostConfirmButton)
	{
		HostConfirmButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HostServer);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
	}

	return true;
}

void UMainMenuWidget::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm Host Server"));
	if (MenuInterface)
	{
		if (HostServerName)
		{
			FString HostName = HostServerName->Text.ToString();
			MenuInterface->Host(HostName);
		}
		else
		{
			MenuInterface->Host("Puzzle Platform #123");
		}
	}
}

void UMainMenuWidget::JoinServer()
{
	if (!MenuInterface) return;

	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Server %d selected"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Server no selected"));
	}
}

void UMainMenuWidget::OpenJoinMenu()
{
	FreshServer();

	if (MenuSwitcher && JoinMenu)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
}

void UMainMenuWidget::OpenMainMenu()
{
	if (MenuSwitcher && MainMenu)
	{
		MenuSwitcher->SetActiveWidget(MainMenu);
	}

	if (ServerList)
	{
		ServerList->ClearChildren();
	}
}

void UMainMenuWidget::OpenHostMenu()
{
	if (MenuSwitcher && HostMenu)
	{
		MenuSwitcher->SetActiveWidget(HostMenu);
	}
}

void UMainMenuWidget::FreshServer()
{
	if (MenuInterface)
	{
		MenuInterface->FreshServerList();
	}
}

void UMainMenuWidget::ExitGame()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->ConsoleCommand("quit");
		}
	}
}

void UMainMenuWidget::UpdateChilren()
{
	if (ServerList)
	{
		for (int i = 0; i < ServerList->GetChildrenCount(); ++i)
		{
			UServerRowWidget* Row = Cast<UServerRowWidget>(ServerList->GetChildAt(i));
			if (Row)
			{
				Row->bSelected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
			}
		}
	}
}
