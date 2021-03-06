// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRowWidget.h"

#include "Button.h"
#include "TextBlock.h"

#include "MainMenuWidget.h"


UServerRowWidget::UServerRowWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	bIsHeader = false;
}

void UServerRowWidget::SetUp(class UMainMenuWidget* MainMenu, uint32 SelectIndex)
{
	Parent = MainMenu;
	Index = SelectIndex;
}

bool UServerRowWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	if (SelectButton)
	{
		if (bIsHeader == false)
		{
			SelectButton->OnClicked.AddDynamic(this, &UServerRowWidget::SelectRow);
		}
	}

	return true;
}

void UServerRowWidget::SelectRow()
{
	Parent->SetSelectIndex(Index);
	//UE_LOG(LogTemp, Warning, TEXT("Select %s"), *ServerName->GetText().ToString());
}
