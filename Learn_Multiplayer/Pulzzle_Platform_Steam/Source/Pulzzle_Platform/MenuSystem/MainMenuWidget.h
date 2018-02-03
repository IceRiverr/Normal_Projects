// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Optional.h"
#include "MenuSystem/BaseMenuWidget.h"
#include "MenuSystem/ServerData.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API UMainMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
public:
	UMainMenuWidget(const FObjectInitializer & ObjectInitializer);

	void SetServerList(const TArray<FServerData>& ServerNames);

	void SetSelectIndex(uint32 Index);

protected:
	virtual bool Initialize();

private:
	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void FreshServer();

	UFUNCTION()
	void ExitGame();

	void UpdateChilren();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancleJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* FreshServerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* ServerList;

	TSubclassOf<class UUserWidget> ServerRowClass;

	TOptional<uint32> SelectedIndex;
};
