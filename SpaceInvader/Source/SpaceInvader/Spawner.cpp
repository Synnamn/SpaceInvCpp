// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Enemy.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < 9; y++)
		{
			GetWorld()->SpawnActor<AEnemy>(Enemy_BP, GetActorLocation() + FVector((spawnDistance * y), (spawnDistance * i), 0.f), GetActorRotation());
		}
	}

	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

