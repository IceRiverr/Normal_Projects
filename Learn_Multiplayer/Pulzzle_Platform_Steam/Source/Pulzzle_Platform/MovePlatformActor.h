// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovePlatformActor.generated.h"

/**
 * 
 */
UCLASS()
class PULZZLE_PLATFORM_API AMovePlatformActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovePlatformActor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:


public:
	UPROPERTY(EditAnywhere)
	float Speed;
	
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers;
	
private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
};
