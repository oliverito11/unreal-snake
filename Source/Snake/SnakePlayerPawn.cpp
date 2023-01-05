// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePlayerPawn.h"

#include "BodyPartActor.h"
#include "MarkerManagerComponent.h"
#include "MarkerStruct.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnakePlayerPawn::ASnakePlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head mesh"));
	SetRootComponent(HeadMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}


// Called when the game starts or when spawned
void ASnakePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	IncreaseTail();
}

// Called every frame
void ASnakePlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveSnake(DeltaTime);
	ManageSnakeBody();

	if(CanSpawn)
	{
		IncreaseTail();
	}
}

// Called to bind functionality to input
void ASnakePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASnakePlayerPawn::MoveRightSnakeActor);
}

void ASnakePlayerPawn::MoveRightSnakeActor(float Axis)
{
	if(BodyPartsActors.Num() == 0) return;
	FRotator NewRotation {0, TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this) * Axis, 0};
	BodyPartsActors[0]->AddActorWorldRotation(NewRotation);
	HeadMesh->SetWorldRotation(BodyPartsActors[0]->GetActorRotation());
}

void ASnakePlayerPawn::MoveSnake(float DeltaTime)
{
	if(BodyPartsActors.Num() == 0) return;
	
	FVector DeltaLocation = BodyPartsActors[0]->GetActorForwardVector() * MoveSpeed * DeltaTime;
	FHitResult Hit;
	BodyPartsActors[0]->AddActorWorldOffset(DeltaLocation, true, &Hit);
	HeadMesh->SetWorldLocation(BodyPartsActors[0]->GetActorLocation());
	CheckIfHit(&Hit);
	if(BodyPartsActors.Num() > 1)
	{
		for(int32 i = 1; i < BodyPartsActors.Num(); i++)
		{
			UMarkerManagerComponent *TempMarkerManager = Cast<UMarkerManagerComponent>(BodyPartsActors[i - 1]->GetComponentByClass(UMarkerManagerComponent::StaticClass()));
			if(!TempMarkerManager || TempMarkerManager->MarkerList.Num() < 1) continue;
			
			BodyPartsActors[i]->SetActorLocation(TempMarkerManager->MarkerList[0].Position);
			BodyPartsActors[i]->SetActorRotation(TempMarkerManager->MarkerList[0].Rotation);
			TempMarkerManager->MarkerList.RemoveAt(0);
		}		
	}
}

void ASnakePlayerPawn::CheckIfHit(FHitResult* Hit)
{
	if(!Hit->GetActor()) return;
	
	if(!Cast<ABodyPartActor>(Hit->GetActor())) return;

	for(int32 i = 0; i < BodyPartsActors.Num(); i++)
	{
		UMarkerManagerComponent *TempMarkerManager = Cast<UMarkerManagerComponent>(BodyPartsActors[i]->GetComponentByClass(UMarkerManagerComponent::StaticClass()));
		if(!TempMarkerManager) continue;
		TempMarkerManager->ClearMarkerList();
		BodyPartsActors[i]->Destroy();
	}

	BodyPartsActors.Empty();
	UE_LOG(LogTemp, Warning, TEXT("End of the game"));
}

void ASnakePlayerPawn::IncreaseTail()
{
	if(BodyPartsActors.Num() == 0)
	{
		//Spawn the head
		ABodyPartActor *Head = GetWorld()->SpawnActor<ABodyPartActor>(BodyPartClass, GetActorLocation(), GetActorRotation());
		AddNewBodyPart(Head);
		return;
	}

	UMarkerManagerComponent *MarkerManager = Cast<UMarkerManagerComponent>(BodyPartsActors[BodyPartsActors.Num() - 1]->GetComponentByClass(UMarkerManagerComponent::StaticClass()));
	if(!MarkerManager) return;
	if(SpawnTime == 0)
	{
		MarkerManager->ClearMarkerList();
	}
	
	SpawnTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	if(SpawnTime >= SpawnOffset)
	{
		ABodyPartActor *BodyPart = GetWorld()->SpawnActor<ABodyPartActor>(BodyPartClass, MarkerManager->MarkerList[0].Position, MarkerManager->MarkerList[0].Rotation);
		AddNewBodyPart(BodyPart);
		
		UMarkerManagerComponent *TempMarkerManager = Cast<UMarkerManagerComponent>(BodyPart->GetComponentByClass(UMarkerManagerComponent::StaticClass()));
		TempMarkerManager->ClearMarkerList();
		
		UE_LOG(LogTemp, Warning, TEXT("Increased tail!"));

		//Reset the variables
		SpawnTime = 0;
		CanSpawn = false;
	}
}

void ASnakePlayerPawn::ManageSnakeBody()
{
	for(int32 i = 0; i < BodyPartsActors.Num(); i++)
	{
		if(BodyPartsActors[i] == nullptr)
		{
			BodyPartsActors.RemoveAt(i);
			i = i - 1;
		}
	}

	if(BodyPartsActors.Num() == 0)
		Destroy();
}

void ASnakePlayerPawn::AddNewBodyPart(ABodyPartActor* BodyPart)
{
	UMarkerManagerComponent *MarkerManagerComponent = Cast<UMarkerManagerComponent>(BodyPart->AddComponentByClass(UMarkerManagerComponent::StaticClass(), true, GetActorTransform(), true));
	BodyPart->FinishAddComponent(MarkerManagerComponent, true, GetActorTransform());
	BodyPart->AddInstanceComponent(MarkerManagerComponent);
	BodyPartsActors.Add(BodyPart);
}
