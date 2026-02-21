// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameModeBase.h"

#include "BattleBlasterGameInstance.h"
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
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("Get Ready!");
		}
	}
	
	CountDownSeconds = CountDownDelay;
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &ABattleBlasterGameModeBase::OnCountDownTimerTimeout, 1.0f, true);
}

void ABattleBlasterGameModeBase::OnCountDownTimerTimeout()
{
	CountDownSeconds--;

	if (CountDownSeconds > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("CountdownSeconds: %i"), CountDownSeconds);
		ScreenMessageWidget->SetMessageText(FString::FromInt(CountDownSeconds));
	}
	else if (CountDownSeconds == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("GO!"));
		ScreenMessageWidget->SetMessageText("GO!");
		Tank->SetPlayerEnabled(true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABattleBlasterGameModeBase::ActorDied(AActor* DeadActor)
{
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
	}
	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Victory!" : "Defeat!";
		ScreenMessageWidget->SetMessageText(GameOverString);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);
		
		UE_LOG(LogTemp, Display, TEXT("Game Over: %s"), *GameOverString);
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameModeBase::OnGameOverTimerTimeout, GameOverDelay, false);
	}
}

void ABattleBlasterGameModeBase::OnGameOverTimerTimeout()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UBattleBlasterGameInstance* BattleBlasterGameInstance = Cast<UBattleBlasterGameInstance>(GameInstance))
		{
			if (IsVictory)
			{
				BattleBlasterGameInstance->LoadNextLevel();
			}
			else
			{
				BattleBlasterGameInstance->RestartCurrentLevel();
			}
		}
	}
	
}


