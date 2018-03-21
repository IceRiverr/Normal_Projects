// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ServerData.generated.h"

USTRUCT()
struct PULZZLE_PLATFORM_API FServerData
{
	GENERATED_BODY()
	
	FString ServerName;
	FString HostUsername;
	uint32 CurrentPlayers;
	uint32 MaxPlayers;
};
