// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarkerActor.generated.h"

UCLASS()
class SNAKE_API AMarkerActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *DebugMarkerMesh;
public:	
	// Sets default values for this actor's properties
	AMarkerActor();
};
