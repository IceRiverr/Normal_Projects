// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

#include "MenuSystem/MenuInterface.h"

void UMainMenuWidget::SetMenuInterface(class IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenuWidget::SetUp()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(this->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);

			PlayerController->bShowMouseCursor = true;
		}
	}
}

void UMainMenuWidget::TearDown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();

		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			//InputModeData.SetConsumeCaptureMouseDown(false);
			PlayerController->SetInputMode(InputModeData);

			PlayerController->bShowMouseCursor = false;
		}
	}
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

	return true;
}

void UMainMenuWidget::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm Host Server"));

	if (MenuInterface)
	{
		MenuInterface->Host();
	}
}

void UMainMenuWidget::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm Join Server"));

	if (MenuInterface && IPAddressField)
	{
		MenuInterface->Join(IPAddressField->GetText().ToString());
	}
}

void UMainMenuWidget::OpenJoinMenu()
{
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
