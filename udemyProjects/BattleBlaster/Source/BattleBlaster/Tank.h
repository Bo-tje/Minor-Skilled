// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:	
	ATank();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	APlayerController* PlayerController;
	
	bool IsAlive = true;
	
	void HandleDestruction();
	void SetPlayerEnabled(bool Enabled);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveInput(const FInputActionValue& Value);
	void RotateInput(const FInputActionValue& Value);
	

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MoveMappingContext;
	

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;
	

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 400.f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 100.f;

	



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
};
