// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Button.h"
#include "MenuSystem/MenuInterface.h"



void UMainMenuWidget::SetMenuInterface(class IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

bool UMainMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success || !HostButton || !JoinButton)
	{
		return false;
	}

	// Todo Setup
	HostButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HostServer);
	
	JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinServer);
	
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
}
