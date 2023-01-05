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
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *HeadMesh;
	
	UPROPERTY(VisibleDefaultsOnly)
	USpringArmComponent *SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category="Spawn")
	float StartTimer {3};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> CameraShakeClass;
	
	bool HasStarted {false};
	
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
	bool GameOver {false};

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Widget")
	UUserWidget *GameOverWidget;

	UPROPERTY(EditDefaultsOnly)
	float ShowMenuTimer {2};

	UPROPERTY(VisibleAnywhere)
	int64 Score {0};
public:
	// Sets default values for this pawn's properties
	ASnakePlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void CheckIfHit(FHitResult* Hit);
	void MoveSnake(float DeltaTime);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRightSnakeActor(float Axis);

	void AddNewBodyPart(ABodyPartActor* BodyPart);
	void IncreaseTail();
	void ShowDeadScreen();
	void EndGame();
	void ManageSnakeBody();
	void SetCanSpawn(bool Spawn) { this->CanSpawn = Spawn; }

	UFUNCTION(BlueprintCallable)
	int GetStartTime() const { return FMath::TruncToInt(StartTimer); }

	UFUNCTION(BlueprintCallable)
	int64 GetScore() const { return this->Score; }
};
