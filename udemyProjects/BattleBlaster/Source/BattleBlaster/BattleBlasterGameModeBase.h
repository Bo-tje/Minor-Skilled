// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleBlasterGameModeBase.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere)
	ATank* Tank;
	int32 TowerCount;
};
