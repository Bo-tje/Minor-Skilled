// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAI.h"
#include "BTTaskNode_ShootAtPlayer.h"

UBTTaskNode_ShootAtPlayer::UBTTaskNode_ShootAtPlayer()
{
	NodeName = TEXT("Shoot At Player");
}

EBTNodeResult::Type UBTTaskNode_ShootAtPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	EBTNodeResult::Type Result = EBTNodeResult::Failed;
	
	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		AShooterSamCharacter* OwnerCharacter = OwnerController->MyCharacter;
		AShooterSamCharacter* PlayerCharacter = OwnerController->PlayerCharacter;
		
		if (OwnerCharacter && PlayerCharacter && PlayerCharacter->IsAlive)
		{
			OwnerCharacter->Shoot();
			Result = EBTNodeResult::Succeeded;
		}
	}
	return Result;
}
