// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Characters/PlayerCharacter.h"



APlayerCharacter::APlayerCharacter()
{

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetCapsuleComponent());
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	// Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.0f;
	
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	
}

void APlayerCharacter::MoveFB(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void APlayerCharacter::MoveLR(float Value)
{
	AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
}

void APlayerCharacter::Rotate(float Value)
{
	AddControllerYawInput(Value * RotationSpeed);
}



void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &APlayerCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &APlayerCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &APlayerCharacter::Rotate);
	
	
}


void APlayerCharacter::Sprint()
{
	// increase speed while tab key is held
	MoveSpeed *= 4;
	stamina -= 1 * GetWorld()->GetDeltaSeconds();
}

void APlayerCharacter::PushBackAttack()
{

}

void APlayerCharacter::EatBerry()
{
	health += 10;
	hunger -= 5;
	stamina += 10;
}
