// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Tower.h"

void ABattleBlasterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();

	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tank is NULL"));
		}
	}

	for (int TowerIndex = 0; TowerIndex < TowerCount; ++TowerIndex)
	{
		if (AActor* TowerActor = Towers[TowerIndex])
		{
			ATower* Tower = Cast<ATower>(TowerActor);
			if (Tower && Tank)
			{
				Tower->Tank = Tank;
			}
		}
	}
}
