// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_PlayerLocationIfSeen.h" 

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	AShooterSamCharacter* PlayerCharacter = OwnerController->PlayerCharacter;
	UBlackboardComponent* BlackboardComponent = OwnerController->GetBlackboardComponent();
	
	if (OwnerController && PlayerCharacter && BlackboardComponent)
	{
		if (OwnerController->LineOfSightTo(PlayerCharacter))
		{
			BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), PlayerCharacter->GetActorLocation());
			OwnerController->SetFocus(PlayerCharacter);
		}
		else
		{
			BlackboardComponent->ClearValue(GetSelectedBlackboardKey());
			OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
