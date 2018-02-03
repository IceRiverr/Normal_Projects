// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMenuWidget.h"

void UBaseMenuWidget::SetMenuInterface(class IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UBaseMenuWidget::SetUp()
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

void UBaseMenuWidget::TearDown()
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

