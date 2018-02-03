// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"

#include "Engine/Engine.h"
#include "ConstructorHelpers.h"
#include "UserWidget.h"
#include "MenuSystem/MainMenuWidget.h"
#include "MenuSystem/InGameMenuWidget.h"


const static FName SESSION_NAME = TEXT("Session Puzzle Platform");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuBPClass.Class != NULL)
	{
		MainMenuClass = MainMenuBPClass.Class;
	}

	// In Game Menu
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (InGameMenuBPClass.Class != NULL)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}
}

void UPuzzlePlatformGameInstance::Init()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString());

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found No Subsystem"));
	}
}

void UPuzzlePlatformGameInstance::LoadMenuWidget()
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

void UPuzzlePlatformGameInstance::LoadInGameMenu()
{
	if (!InGameMenuClass)
		return;

	InGameMenu = CreateWidget<UInGameMenuWidget>(this, InGameMenuClass);
	if (InGameMenu)
	{
		InGameMenu->SetUp();
		InGameMenu->SetMenuInterface(this);
	}
}

void UPuzzlePlatformGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzlePlatformGameInstance::Join(uint32 Index)
{
	if (MainMenu)
	{
		MainMenu->TearDown();
	}

	if (SessionInterface.IsValid() && SessionSearch.IsValid())
	{
		SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
	}
}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformGameInstance::FreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch);
	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Begin find Sessions"));
		SessionSearch->bIsLanQuery = true;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformGameInstance::ExitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		//PlayerController->close
	}
}

void UPuzzlePlatformGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Session %s"), *SessionName.ToString());

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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found No Session"));
	}
}

void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		CreateSession();
	}
}

void UPuzzlePlatformGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Finish find Sessions"));

	if (bWasSuccessful && SessionSearch.IsValid() && MainMenu)
	{
		TArray<FString> ServerList;
		if (SessionSearch.IsValid())
		{
			for (auto result : SessionSearch->SearchResults)
			{
				UE_LOG(LogTemp, Warning, TEXT("Sessions %s"), *result.GetSessionIdStr());
				ServerList.AddUnique(result.GetSessionIdStr());
			}
		}
		MainMenu->SetServerList(ServerList);
	}
}

void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString ConnectInfo;
	if (SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Green, FString::Printf(TEXT("Join %s..."), *ConnectInfo));
		}

		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Find Connect Address"));
	}
}