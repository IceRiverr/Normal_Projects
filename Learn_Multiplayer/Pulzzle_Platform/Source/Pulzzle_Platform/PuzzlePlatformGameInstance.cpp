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

	MainMenu = nullptr;
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

	MainMenu = CreateWidget<UMainMenuWidget>(this, MainMenuClass);
	if (MainMenu)
	{
		MainMenu->SetUp();
		MainMenu->SetMenuInterface(this);
	}
}

void UPuzzlePlatformGameInstance::Host()
{
	if (MainMenu)
	{
		MainMenu->TearDown();
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting..."));
	}

	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	if (MainMenu)
	{
		MainMenu->TearDown();
	}

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
