// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverGame/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
		float Food = 100.0f;

	UFUNCTION(BlueprintCallable)
	void IncreaseFood(float amount);
};
