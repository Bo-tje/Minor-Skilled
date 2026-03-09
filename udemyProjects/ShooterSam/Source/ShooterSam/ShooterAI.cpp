// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ShooterAI.h"

// Called when the game starts or when spawned
void AShooterAI::BeginPlay()
{
	Super::BeginPlay();

}

void AShooterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	if (PlayerPawn)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, 200.f, false, true, false, 0, true);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	}
	*/

}

void AShooterAI::StartBehaviorTree(AShooterSamCharacter* Player)
{
	if (EnemyAIBehaviorTree)
	{
		MyCharacter = Cast<AShooterSamCharacter>(GetPawn());
		if (Player)
		{
			PlayerCharacter = Player;
		}
		
		RunBehaviorTree(EnemyAIBehaviorTree);
	}
}
