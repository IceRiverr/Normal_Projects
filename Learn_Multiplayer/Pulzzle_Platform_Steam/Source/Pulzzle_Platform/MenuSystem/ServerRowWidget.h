// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API UServerRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUp(class UMainMenuWidget* MainMenu, uint32 SelectIndex);

protected:
	virtual bool Initialize();

private:
	UFUNCTION()
	void SelectRow();

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	class UMainMenuWidget* Parent;

	uint32 Index;

};
