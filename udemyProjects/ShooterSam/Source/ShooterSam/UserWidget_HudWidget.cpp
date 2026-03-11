// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget_HudWidget.h"

void UUserWidget_HudWidget::SetHealthBarPercentage(float NewPercentage)
{
	if (NewPercentage >= 0.0f && NewPercentage <= 1.0f)
	{
		HealthBar->SetPercent(NewPercentage);
	}
}
