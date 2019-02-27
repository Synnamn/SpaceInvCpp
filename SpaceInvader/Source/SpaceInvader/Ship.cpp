// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraActor.h"
#include "Components/InputComponent.h"


// Sets default values
AShip::AShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a visible object
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	// Respond when our "Grow" key is pressed or released.
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AShip::Shoot);
	InputComponent->BindAxis("MoveX", this, &AShip::MoveX);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	//Mouse setup
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
	PlayerController->bEnableMouseOverEvents = true;
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle movement based on our "MoveX" and "MoveY" axes
	Movement(DeltaTime);
}

void AShip::Movement(float DeltaTime)
{
	if (!CurrentVelocity.IsZero())
	{
		TimeAccellerating += DeltaTime;
		if (TimeAccellerating >= TimeBeforeAccelerate)
		{
			SpeedScale += 0.05;
			SpeedScale > 5.0f ? SpeedScale = 4.0f : SpeedScale;   //SpeedScale aldri over 5.0
		}
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * SpeedScale * DeltaTime);
		SetActorLocation(NewLocation);
	}
	else
	{
		SpeedScale = 2.5f;
		TimeAccellerating = 0.f;
	}
	FRotator TempRotation = GetActorRotation();
	SetActorRotation(TempRotation);

}
void AShip::MoveX(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(-1.0f, AxisValue, 1.0f) * 200.0f;
}

void AShip::Shoot()
{
	GetWorld()->SpawnActor<ABullet>(Bullet_BP, GetActorLocation() + FVector(10.f, 0.f, 0.f), GetActorRotation());
}
