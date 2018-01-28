// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuInterface.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(class IMenuInterface* MenuInterface);

protected:
	virtual bool Initialize();

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	class IMenuInterface* MenuInterface;
	
};
