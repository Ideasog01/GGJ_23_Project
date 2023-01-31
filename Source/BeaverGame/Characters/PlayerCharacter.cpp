// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Characters/PlayerCharacter.h"

void APlayerCharacter::IncreaseFood(float amount)
{
	Food += amount;

	if(Food > MaxFood)
		Food = MaxFood;
}

void APlayerCharacter::IncreaseThirst(float amount)
{
	Thirst += amount;

	if (Thirst > MaxThirst)
		Thirst = MaxThirst;
}
