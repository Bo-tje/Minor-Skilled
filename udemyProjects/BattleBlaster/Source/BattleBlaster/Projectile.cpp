// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Pooler.h"
#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(ProjectileMesh);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(ProjectileMesh);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation(), GetActorRotation());
}

void AProjectile::OnSpawnFromPool(const FVector& Direction)
{
	// Reset velocity and reactivate movement
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
	
	// Ensure the component is active and ticking
	ProjectileMovementComponent->SetComponentTickEnabled(true);
	ProjectileMovementComponent->Activate(true);

	// Reset lifespan timer
	GetWorldTimerManager().SetTimer(LifeSpanTimerHandle, this, &AProjectile::ReturnToPool, 3.0f, false);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		if (OtherActor && OtherActor != MyOwner && OtherActor != this)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, UDamageType::StaticClass() );

			if (HitParticles)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (HitSound)
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation(), GetActorRotation());
			
			if (HitCameraShakeClass)
			{
				if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
					PlayerController->ClientStartCameraShake(HitCameraShakeClass);
			}
		}
	}
	
	ReturnToPool();
}

void AProjectile::ReturnToPool()
{
	GetWorldTimerManager().ClearTimer(LifeSpanTimerHandle);
	
	if (UUnrealObjectPooler* Pooler = UUnrealObjectPooler::Get(this))
	{
		Pooler->ReturnObjectToPool(this);
	}
}
