// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaverGame/Controllers/BeaverPlayerController.h"
#include "BeaverGame/Interaction/BuildObject.h"


void ABeaverPlayerController::PlayerInteract()
{
	if (CurrentBuildObject != nullptr)
	{
		CurrentBuildObject->Build();
		buildcounter++;
		CurrentBuildObject = nullptr;
	}
}



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

	UE_LOG(LogTemp, Warning, TEXT("Roots Count: %d"), rootsCount);
}

bool ABeaverPlayerController::HasResources(int roots, int logs, int stone)
{
	bool hasResources = true;

	hasResources &= roots <= rootsCount;
	hasResources &= logs <= logsCount;
	hasResources &= stone <= stoneCount;

	return hasResources;
}

void ABeaverPlayerController::RemoveResources(int roots, int logs, int stone)
{
	rootsCount -= roots;
	logsCount -= logs;
	stoneCount -= stone;
}

void ABeaverPlayerController::DisplayResources(bool active)
{
	/*if (ResourceDisplay)
	{
		if (active)
		{
			ResourceDisplay->AddToViewport();
		}
		else
		{
			ResourceDisplay->RemoveFromViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: ResourceDisplay in BeaverPlayerController is equal to null. \nPlease assign BeaverPlayerController in the blueprint."));
	}*/
}

void ABeaverPlayerController::WinScreen()
{
	if(buildcounter > 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("You Win!"));
	}
}

void ABeaverPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//ResourceDisplayInstance = CreateWidget<UUserWidget>(this, ResourceDisplayTemplate);

	//if(ResourceDisplayInstance) 
	//{
	//	//let add it to the view port
	//	ResourceDisplayInstance->AddToViewport();
	//}
}
