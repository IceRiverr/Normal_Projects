// Fill out your copyright notice in the Description page of Project Settings.

#include "MovePlatformActor.h"

AMovePlatformActor::AMovePlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	Speed = 20.0f;

	ActiveTriggers = 1;
}

void AMovePlatformActor::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetActorTransform().TransformPosition(TargetLocation);
}

void AMovePlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
	
	if (HasAuthority())
	{
		if (ActiveTriggers > 0)
		{
			FVector CurrentLocation = GetActorLocation();

			float TravalLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float TravaledLength = (CurrentLocation - GlobalStartLocation).Size();

			if (TravaledLength > TravalLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			CurrentLocation += Direction * Speed * DeltaTime;
			SetActorLocation(CurrentLocation);
		}
	}
}

void AMovePlatformActor::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovePlatformActor::RemoveActiveTrigger()
{
	ActiveTriggers--;
}
