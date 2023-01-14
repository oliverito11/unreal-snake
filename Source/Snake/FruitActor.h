// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FruitActor.generated.h"

UCLASS()
class SNAKE_API AFruitActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *FruitMesh;

	UPROPERTY(EditDefaultsOnly)
	USoundBase *PickUpSound;
public:	
	// Sets default values for this actor's properties
	AFruitActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
