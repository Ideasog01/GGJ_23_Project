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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
		float Thirst = 100.0f;


	UFUNCTION(BlueprintCallable)
		void IncreaseFood(float amount);
	
	UFUNCTION(BlueprintCallable)
		void IncreaseThirst(float amount);
	
private:
	float MaxFood = 100.0f;
	float MaxThirst = 100.0f;
};
