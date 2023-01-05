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
		float X = FMath::FRandRange(0, Width);
		float Y = FMath::FRandRange(0, Height);
		FVector SpawnLocation = FVector{X, Y, 0};
		GetWorld()->SpawnActor<AFruitActor>(FruitActorClass, SpawnLocation, FRotator::ZeroRotator);
		SpawnFruitTime = MaxSpawnFruitTime;
	}
}
