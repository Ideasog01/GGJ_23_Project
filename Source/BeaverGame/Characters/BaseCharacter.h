// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BEAVERGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int health;
	
	UPROPERTY(EditAnywhere)
	int maxHealth;

	UPROPERTY(EditAnywhere)
	int hunger;

	UPROPERTY(EditAnywhere)
	int thirst;
	
	UPROPERTY(EditAnywhere)
	int stamina;

	
	
	int GetHealth();
	
};
