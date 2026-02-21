// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScreenMessage.h"
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
	
	UScreenMessage* ScreenMessageWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;
	
	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;
	
	UPROPERTY(EditAnywhere)
	int32 CountDownDelay = 3;
	
	int32 CountDownSeconds;
	
	FTimerHandle CountDownTimerHandle;
	
	UPROPERTY(VisibleAnywhere)
	ATank* Tank;
	int32 TowerCount;
	bool IsVictory = false;
	bool IsGameOver = false;
	
	void ActorDied(AActor* DeadActor);
	
	void OnGameOverTimerTimeout();
	void OnCountDownTimerTimeout();
};
