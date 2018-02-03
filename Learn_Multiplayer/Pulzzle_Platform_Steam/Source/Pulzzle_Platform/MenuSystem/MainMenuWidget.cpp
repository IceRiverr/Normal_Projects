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

void UMainMenuWidget::SetServerList(const TArray<FString> ServerNames)
{
	UWorld* World = this->GetWorld();
	if (ServerList && World)
	{
		ServerList->ClearChildren();
		
		uint32 Select = 0;
		for (const FString& ServerName : ServerNames)
		{
			UServerRowWidget* Row = CreateWidget<UServerRowWidget>(World, ServerRowClass);
			if (Row)
			{
				Row->SetUp(this, Select);
				Select++;
				Row->ServerName->SetText(FText::FromString(ServerName));
				ServerList->AddChild(Row);
			}
		}
	}
}

void UMainMenuWidget::SetSelectIndex(uint32 Index)
{
	SelectIndex = Index;
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
		HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HostServer);
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

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
	}

	return true;
}

void UMainMenuWidget::HostServer()
{
	//UE_LOG(LogTemp, Warning, TEXT("I'm Host Server"));

	if (MenuInterface)
	{
		MenuInterface->Host();
	}
}

void UMainMenuWidget::JoinServer()
{
	if (!MenuInterface) return;

	if (SelectIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Server %d selected"), SelectIndex.GetValue());
		MenuInterface->Join(SelectIndex.GetValue());
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
