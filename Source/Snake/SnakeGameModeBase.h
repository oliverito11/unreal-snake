// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameModeBase.generated.h"

class AFruitActor;
/**
 * 
 */
UCLASS()
class SNAKE_API ASnakeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	float MaxSpawnFruitTime {1};
	
	UPROPERTY(VisibleAnywhere)
	float SpawnFruitTime {MaxSpawnFruitTime};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFruitActor> FruitActorClass;

	UPROPERTY(EditAnywhere)
	float Width {500};

	UPROPERTY(EditAnywhere)
	float Height {500};
public:
	ASnakeGameModeBase();
	
protected:
	virtual void Tick(float DeltaSeconds) override;
};
