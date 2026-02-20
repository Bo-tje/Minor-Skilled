// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "Tank.h"


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
	UE_LOG(LogTemp, Warning, TEXT("Total Towers: %i"), TowerCount);
}

void ABattleBlasterGameModeBase::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;
	bool IsVictory = false;
	
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		IsGameOver = true;
	}
	else
	{
		if (ATower* DeadTower = Cast<ATower>(DeadActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Tower died"));
			DeadTower->HandleDestruction();

			TowerCount--;
			if (TowerCount == 0)
			{
				IsGameOver = true;
				IsVictory = true;
			}
		}
		if (IsGameOver)
		{
			FString GameOverString = IsVictory ? "Victory!" : "Defeat!";
			UE_LOG(LogTemp, Display, TEXT("Game Over: %s"), *GameOverString);
			
			FTimerHandle GameOverTimerHandle;
			GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameModeBase::OnGameOverTimerTimeout, GameOverDelay, false);
		}
	}
}

void ABattleBlasterGameModeBase::OnGameOverTimerTimeout()
{
	FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevel);
}
