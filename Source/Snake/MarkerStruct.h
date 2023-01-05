// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MarkerStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMarkerStruct
{
	GENERATED_BODY()

public:
	FVector Position;
	FRotator Rotation;

public:
	FMarkerStruct() = default;
	FMarkerStruct(const FVector &PositionValue, const FRotator &RotationValue) : Position(PositionValue), Rotation(RotationValue) {}
};