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

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	BeaverController = Cast<ABeaverPlayerController>(GetWorld()->GetFirstPlayerController());
}

void APlayerCharacter::MoveFB(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value * MoveSpeed);
}

void APlayerCharacter::MoveLR(float Value)
{
	AddMovementInput(GetActorRightVector(), Value * MoveSpeed);
}

void APlayerCharacter::RotateY(float Value)
{

	AddControllerPitchInput(Value * RotationSpeed);
}

void APlayerCharacter::Interact()
{
	BeaverController->PlayerInteract();

	if (bIsNearWater)
	{
		DrinkWater();
	}
}

void APlayerCharacter::RotateX(float Value)
{
	AddControllerYawInput(Value * RotationSpeed);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &APlayerCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &APlayerCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("RotateX"), this, &APlayerCharacter::RotateX);
	PlayerInputComponent->BindAxis(TEXT("RotateY"), this, &APlayerCharacter::RotateY);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("EatBerry", IE_Pressed, this, &APlayerCharacter::EatBerry);
	
}

void APlayerCharacter::PushBackAttack()
{

}

void APlayerCharacter::EatBerry()
{
	if (BeaverController->berriesCount > 0)
	{
		IncreaseFood(30);
		BeaverController->berriesCount--;
	}
}

void APlayerCharacter::DrinkWater()
{
	Thirst+=10;

	if (Thirst > MaxThirst)
	{
		Thirst = MaxThirst;
	}
}

void APlayerCharacter::IncreaseFood(float amount)
{
	Food += amount;

	if (Food > MaxFood)
	{
		Food = MaxFood;
	}
}

void APlayerCharacter::IncreaseThirst(float amount)
{
	Thirst += amount;

	if (Thirst > MaxThirst)
	{
		Thirst = MaxThirst;
	}	
}
