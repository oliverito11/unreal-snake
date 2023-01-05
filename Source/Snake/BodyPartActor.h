// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BodyPartActor.generated.h"

class AMarkerActor;
UCLASS()
class SNAKE_API ABodyPartActor : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *BodyPartMesh;
public:	
	// Sets default values for this actor's properties
	ABodyPartActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
