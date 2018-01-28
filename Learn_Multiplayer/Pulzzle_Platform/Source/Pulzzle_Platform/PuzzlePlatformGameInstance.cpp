// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

#include "Engine/Engine.h"
#include "ConstructorHelpers.h"
#include "UserWidget.h"
#include "MenuSystem/MainMenuWidget.h"


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuBPClass.Class != NULL)
	{
		MainMenuClass = MainMenuBPClass.Class;
	}
}

void UPuzzlePlatformGameInstance::Init()
{
	if (MainMenuClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Find2 %s"), *MainMenuClass->GetName());
	}
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (!MainMenuClass)
		return;

	UMainMenuWidget* MainMenu = CreateWidget<UMainMenuWidget>(this, MainMenuClass);
	if (MainMenu)
	{
		MainMenu->AddToViewport();
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(MainMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModeData);

		PlayerController->bShowMouseCursor = true;

		MainMenu->SetMenuInterface(this);
	}
}

void UPuzzlePlatformGameInstance::Host()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting..."));
	}

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		FInputModeGameOnly InputModeData;
		InputModeData.SetConsumeCaptureMouseDown(false);
		PlayerController->SetInputMode(InputModeData);
	}
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Green, FString::Printf(TEXT("Join %s..."), *Address));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}
