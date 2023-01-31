// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BeaverPlayerController.generated.h"

class AResource;

/**
 * 
 */
UCLASS()
class BEAVERGAME_API ABeaverPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void AddResource(int resourceIndex, int amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int rootsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int logsCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int stoneCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int berriesCount;
	
};
