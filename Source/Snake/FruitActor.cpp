// Fill out your copyright notice in the Description page of Project Settings.


#include "FruitActor.h"

#include "BodyPartActor.h"
#include "SnakePlayerPawn.h"
#include "GameFramework/PlayerState.h"

// Sets default values
AFruitActor::AFruitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FruitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fruit mesh"));
	SetRootComponent(FruitMesh);
}

// Called when the game starts or when spawned
void AFruitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFruitActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if(!Other) return;
	ABodyPartActor *BodyPart = Cast<ABodyPartActor>(Other);
	if(!BodyPart) return;
	
	//Add one more object to tail
	ASnakePlayerPawn *PlayerPawn = Cast<ASnakePlayerPawn>(GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>()->GetPawn());
	if(!PlayerPawn) return;
	PlayerPawn->SetCanSpawn(true);

	Destroy();
}
