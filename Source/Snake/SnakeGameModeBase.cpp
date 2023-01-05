// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameModeBase.h"

#include "FruitActor.h"

ASnakeGameModeBase::ASnakeGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASnakeGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SpawnFruitTime -= DeltaSeconds;

	if(SpawnFruitTime <= 0)
	{
		//Spawn new fruit in random position
		FVector SpawnLocation {FMath::RandRange(Width, Height),FMath::RandRange(Width, Height), 0};
		GetWorld()->SpawnActor<AFruitActor>(FruitActorClass, SpawnLocation, FRotator::ZeroRotator);
		SpawnFruitTime = MaxSpawnFruitTime;
	}
}
