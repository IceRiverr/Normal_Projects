// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenuWidget.h"

#include "Components/Button.h"

bool UInGameMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (CancleButton)
	{
		CancleButton->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnCancleButtonPressed);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UInGameMenuWidget::OnQuitButtonPressed);
	}

	return true;
}

void UInGameMenuWidget::OnCancleButtonPressed()
{
	TearDown();
}

void UInGameMenuWidget::OnQuitButtonPressed()
{
	TearDown();
	if (MenuInterface)
	{
		MenuInterface->LoadMainMenu();
	}
}
