// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerManagerComponent.h"

#include "MarkerActor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UMarkerManagerComponent::UMarkerManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AMarkerActor> MarkerActorClassFinder(TEXT("/Game/Blueprints/BP_MarkerActor"));
	MarkerActorClass = MarkerActorClassFinder.Class;
}


// Called when the game starts
void UMarkerManagerComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UMarkerManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateMarkerList();
}

void UMarkerManagerComponent::UpdateMarkerList()
{
	AMarkerActor *MarkerActor = GetWorld()->SpawnActor<AMarkerActor>(MarkerActorClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	if(!MarkerActor) return;
	if(MarkerActorsList.Num() >= 100)
	{
		MarkerActorsList[0]->Destroy();
		MarkerActorsList.RemoveAt(0);
	}
	MarkerActorsList.Add(MarkerActor);
}

void UMarkerManagerComponent::ClearMarkerList()
{
	for(int32 i = 0; i < MarkerActorsList.Num(); i++)
	{
		MarkerActorsList[i]->Destroy();
	}
	MarkerActorsList.Empty();
	UpdateMarkerList();
}
