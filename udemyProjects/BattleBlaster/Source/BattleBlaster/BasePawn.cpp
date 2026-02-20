// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Pooler.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComponent);
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	
	FRotator LookAtRotation = FRotator(0.0f, VectorToTarget.Rotation().Yaw, 0.0f);
	
	FRotator InterpolatedRotation = FMath::RInterpTo
	(TurretMesh->GetComponentRotation(), 
		LookAtRotation, GetWorld()->GetDeltaSeconds(), 
		10.0f);
	
	TurretMesh->SetWorldRotation(InterpolatedRotation);
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	
	if (UUnrealObjectPooler* Pooler = UUnrealObjectPooler::Get(this))
	{
		AProjectile* Projectile = Pooler->SpawnObject<AProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation, EPoolType::Projectiles);
		if (Projectile)
		{
			Projectile->SetOwner(this);
			Projectile->OnSpawnFromPool(ProjectileSpawnRotation.Vector());
		}
	}
}

void ABasePawn::HandleDestruction()
{
	
}
