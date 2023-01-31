// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Controllers/BeaverPlayerController.h"

void ABeaverPlayerController::AddResource(int resourceIndex, int amount)
{
	switch (resourceIndex)
	{
	case 0:
		rootsCount += amount;
		break;
	case 1:
		logsCount += amount;
		break;
	case 2:
		stoneCount += amount;
		break;
	case 3:
		berriesCount += amount;
		break;
	}
}