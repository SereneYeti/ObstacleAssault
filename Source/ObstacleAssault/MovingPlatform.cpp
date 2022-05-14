// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();	
}

void AMovingPlatform::RotatePlatform(float DeltaTime, bool rotPlatform)
{
	UE_LOG(LogTemp, Display, TEXT("%s Platform is rotating: "), *GetName());
}

void AMovingPlatform::MovePlatform(float DeltaTime, bool movePlatform)
{	
	FVector CurrentLocation = GetActorLocation();	
	CurrentLocation += PlatformVelocity * DeltaTime;
	SetActorLocation(CurrentLocation);
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);

	if (DistanceMoved > MovedDistance)
	{
		FString ObjectName = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Platform overshot by: %f"), *ObjectName, DistanceMoved - MovedDistance);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime, bMovePlatform);
	RotatePlatform(DeltaTime, bRotPlatform);
}

