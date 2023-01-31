// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeaverGame/Characters/BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Engine/StaticMesh.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BEAVERGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	APlayerCharacter();
	
private:
	
	void MoveFB(float Value);
	void MoveLR(float Value);
	void Rotate(float Value);

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraBoom;
	

		
public:

	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void PushBackAttack();

	UFUNCTION(BlueprintCallable)
	void EatBerry();
	
	
};
