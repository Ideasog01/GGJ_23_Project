// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Interaction/BuildObject.h"

// Sets default values
ABuildObject::ABuildObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	ObjectMesh->SetupAttachment(RootComponent);
	ObjectMesh->SetVisibility(false);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

}

void ABuildObject::Build()
{
	if(BeaverController->HasResources(requiredRoots, requiredLogs, requiredStone))
	{
		ObjectMesh->SetVisibility(true);
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough resources!!"));
	}
	
}

// Called when the game starts or when spawned
void ABuildObject::BeginPlay()
{
	Super::BeginPlay();
	BeaverController = Cast<ABeaverPlayerController>(GetWorld()->GetFirstPlayerController());

	if (BeaverController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: Player Controller was equal to nullptr!!"));
	}

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABuildObject::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ABuildObject::OnOverlapEnd);
}

void ABuildObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		//Assign this build object to current in player controller

		if (BeaverController != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Build Object Active!"));
			BeaverController->CurrentBuildObject = this;
		}
	}
}

void ABuildObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		//Assign this build object to current in player controller

		if (BeaverController != nullptr)
		{
			if (BeaverController->CurrentBuildObject == this)
			{
				UE_LOG(LogTemp, Warning, TEXT("Build Object Deactivated!"));
				BeaverController->CurrentBuildObject = nullptr;
			}
		}
	}
}

// Called every frame
void ABuildObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

