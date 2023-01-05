// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePlayerPawn.generated.h"

class AMarkerActor;
class USpringArmComponent;
class AHeadPartActor;
class UCameraComponent;
class ABodyPartActor;
UCLASS()
class SNAKE_API ASnakePlayerPawn : public APawn
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
	USpringArmComponent *SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent *Camera;

	UPROPERTY(EditDefaultsOnly, Category="Body")
	TSubclassOf<ABodyPartActor> BodyPartClass;

	UPROPERTY(VisibleAnywhere, Category="Body")
	TArray<ABodyPartActor*> BodyPartsActors;

	UPROPERTY(EditAnywhere, Category="Spawn")
	float SpawnOffset {1};
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurnSpeed {10};

	UPROPERTY(VisibleAnywhere, Category="Spawn")
	float SpawnTime {0};

	UPROPERTY(VisibleAnywhere, Category="Spawn")
	bool CanSpawn {false};
	
public:
	// Sets default values for this pawn's properties
	ASnakePlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void MoveSnake(float DeltaTime);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRightSnakeActor(float Axis);

	void AddNewBodyPart(ABodyPartActor* BodyPart);
	void IncreaseTail();
	void ManageSnakeBody();
	void SetCanSpawn(bool Spawn) { this->CanSpawn = Spawn; }
};
