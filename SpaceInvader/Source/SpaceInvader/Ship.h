// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

class UInputComponent;
class ABullet;

UCLASS()
class SPACEINVADER_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(UInputComponent* mInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<ABullet> Bullet_BP;

	UShapeComponent* CollisionBox{ nullptr };

	//Input functions
	void MoveX(float AxisValue);
	void Shoot();

	//Input variables
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
		float SpeedScale{ 1.f };
	float TimeBeforeAccelerate{ 1.f };
	float TimeAccellerating{ 0.f };


private:
	void Movement(float DeltaTime);

};
