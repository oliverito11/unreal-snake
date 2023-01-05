// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerActor.h"

// Sets default values
AMarkerActor::AMarkerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DebugMarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Debug mesh"));
	SetRootComponent(DebugMarkerMesh);
}
