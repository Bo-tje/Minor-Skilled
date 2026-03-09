// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"

#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"


AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);
	
	for (int32 AIActorNumber = 0; AIActorNumber < ShooterAIActors.Num(); AIActorNumber++)
	{
		AActor* ShooterAIActor = ShooterAIActors[AIActorNumber];
		AShooterAI* ShooterAI =Cast<AShooterAI>(ShooterAIActor);
		
		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
		}
	}
}
