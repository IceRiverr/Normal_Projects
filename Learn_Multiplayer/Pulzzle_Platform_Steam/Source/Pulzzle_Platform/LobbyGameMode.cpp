// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "PuzzlePlatformGameInstance.h"

ALobbyGameMode::ALobbyGameMode()
{
	NumberOfPlayers = 0;
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumberOfPlayers++;

	if (NumberOfPlayers >= 2)
	{
		GetWorldTimerManager().SetTimer(StartGameTimer, this, &ALobbyGameMode::StartGame, 5.0f, false);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	NumberOfPlayers--;
}

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->StartSession(); // 其他玩家就无法再加入游戏，并且无法搜索到
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/Platform/Maps/Game?listen");
		}
	}
}
