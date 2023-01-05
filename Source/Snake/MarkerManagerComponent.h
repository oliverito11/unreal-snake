// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarkerManagerComponent.generated.h"


struct FMarkerStruct;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNAKE_API UMarkerManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TArray<FMarkerStruct> MarkerList;

	UPROPERTY(VisibleAnywhere)
	float MaxSpawnMarkerTime {.1};

	UPROPERTY(VisibleAnywhere)
	float SpawnMarkerTime {MaxSpawnMarkerTime};
public:	
	// Sets default values for this component's properties
	UMarkerManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	void UpdateMarkerList();
	void ClearMarkerList();
};
