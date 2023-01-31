// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverGame/Characters/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Engine/StaticMesh.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "BeaverGame/Controllers/BeaverPlayerController.h"

#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	APlayerCharacter();

protected:

	void BeginPlay();
	
private:
	
	void MoveFB(float Value);
	void MoveLR(float Value);
	void RotateX(float Value);
	void RotateY(float Value);

	void Interact();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float MoveSpeed = 1.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float RotationSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraBoom;

	ABeaverPlayerController* BeaverController;
		
public:
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void PushBackAttack();

	UFUNCTION(BlueprintCallable)
	void EatBerry();

	UFUNCTION(BlueprintCallable)
	void DrinkWater();

	bool bIsNearWater = false;
	
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	float Food = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	float Thirst = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacter")
	int Stamina;

	UFUNCTION(BlueprintCallable)
	void IncreaseFood(float amount);
	
	UFUNCTION(BlueprintCallable)
	void IncreaseThirst(float amount);
	
private:
	float MaxFood = 100.0f;
	float MaxThirst = 100.0f;
};
