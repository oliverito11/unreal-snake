// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerManagerComponent.h"

#include "MarkerStruct.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UMarkerManagerComponent::UMarkerManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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
	const FMarkerStruct MarkerInst = {GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation()};
	if(MarkerList.Num() >= 100)
	{
		MarkerList.RemoveAt(0);
	}
	MarkerList.Add(MarkerInst);
}

void UMarkerManagerComponent::ClearMarkerList()
{
	MarkerList.Empty();
	UpdateMarkerList();
}
