// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	SetRootComponent(SceneRoot);
	SkeletalMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (OwnerController)
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		FHitResult HitResult;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(GetOwner());

		FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
		bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, LineTraceEnd, ECC_GameTraceChannel2, params);
		
		if (IsHit)
		{
			LineTraceEnd = HitResult.Location;
			if (AActor* HitActor = HitResult.GetActor())
			{
				UGameplayStatics::ApplyDamage(HitActor, Damage, OwnerController, this, UDamageType::StaticClass());
			}
		}
	}
}

