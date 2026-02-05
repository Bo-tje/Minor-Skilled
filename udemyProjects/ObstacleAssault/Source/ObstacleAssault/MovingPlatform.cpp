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

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveOrRotate ? RotatePlatform(DeltaTime) : MovePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	AddActorLocalOffset(PlatformVelocity * DeltaTime);
	
    float DistanceMoved = FVector::Dist(StartLocation, GetActorLocation());
	
    if (DistanceMoved >= MoveDistance)
    {
    	FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    	FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;
    	SetActorLocation(NewStartLocation);
    	StartLocation = GetActorLocation();
    	PlatformVelocity = -PlatformVelocity;
    }
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

