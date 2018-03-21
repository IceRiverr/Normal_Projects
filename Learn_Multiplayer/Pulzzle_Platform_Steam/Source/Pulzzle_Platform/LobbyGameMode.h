// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pulzzle_PlatformGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API ALobbyGameMode : public APulzzle_PlatformGameMode
{
	GENERATED_BODY()
	
public:
	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

private:
	void StartGame();

	FTimerHandle StartGameTimer;

	int NumberOfPlayers;
};
