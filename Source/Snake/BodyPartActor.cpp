// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPartActor.h"

#include "MarkerActor.h"

// Sets default values
ABodyPartActor::ABodyPartActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyPartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body mesh"));
	SetRootComponent(BodyPartMesh);
}

// Called when the game starts or when spawned
void ABodyPartActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABodyPartActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
