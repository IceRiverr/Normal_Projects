// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"

#include "BaseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(class IMenuInterface* MenuInterface);

	void SetUp();

	void TearDown();

protected:
	class IMenuInterface* MenuInterface;
};
