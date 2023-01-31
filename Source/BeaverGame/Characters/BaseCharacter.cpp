// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Characters/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::TakeDamage(float amount)
{
	if (Health - amount < 0)
		Health = 0;
	else
		Health -= amount;
}

void ABaseCharacter::IncreaseHealth(float amount)
{
	Health += amount;

	if (Health > MaxHealth)
		Health = MaxHealth;
}


// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ABaseCharacter::GetHealth()
{
	return Health;
}


