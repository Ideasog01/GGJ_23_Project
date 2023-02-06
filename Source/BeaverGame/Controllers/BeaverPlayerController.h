// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BeaverPlayerController.generated.h"

class ABuildObject;

UCLASS()
class BEAVERGAME_API ABeaverPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int buildcounter;
	
	void PlayerInteract();

	void AddResource(int resourceIndex, int amount);

	bool HasResources(int roots, int logs, int stone);

	void RemoveResources(int roots, int logs, int stone);

	void DisplayResources(bool active);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int rootsCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int logsCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int stoneCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int berriesCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABuildObject* CurrentBuildObject = nullptr;

	UFUNCTION(BlueprintCallable)
	void WinScreen();

protected:

	void BeginPlay();

	//UPROPERTY(EditAnywhere, Category = "UI")
	//TSubclassOf<class UUserWidget> ResourceDisplayTemplate;
	

	
};
