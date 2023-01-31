// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Controllers/BeaverPlayerController.h"

void ABeaverPlayerController::AddResource(AResource& resource, int amount)
{
	int resourceIndex = resource.GetResourceType();

	if(resourceIndex > resourceArray.Num() - 1)
	{
		//IncrementThirst
	}
	else
	{
		resourceArray[resource.GetResourceType()] += amount;
	}
}