// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Controllers/BeaverPlayerController.h"

void ABeaverPlayerController::AddResource(int resourceIndex, int amount)
{
	if(resourceIndex > resourceArray.Num() - 1)
	{
		//IncrementThirst
	}
	else
	{
		resourceArray[resourceIndex] += amount;
	}
}