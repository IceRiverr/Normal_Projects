// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/BaseMenuWidget.h"

#include "InGameMenuWidget.generated.h"


/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API UInGameMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

private:
	UFUNCTION()
	void OnCancleButtonPressed();

	UFUNCTION()
	void OnQuitButtonPressed();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* CancleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

};
