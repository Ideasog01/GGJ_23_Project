// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawObject.h"

// Sets default values
ASpawObject::ASpawObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));

	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShouldSpawn)
	{
		ScheduleSpawn();
	}
	
}

void ASpawObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorldTimerManager().ClearAllTimersForObject(this);
}

bool ASpawObject::SpawnActor()
{
	bool SpawnedActor = false;
	if (ActorClassToSpawn)
	{
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += BoxBounds.BoxExtent.X * FMath::FRandRange(-1.0f, 1.0f);

		SpawnLocation.Y += BoxBounds.BoxExtent.Y * FMath::FRandRange(-1.0f, 1.0f);

		SpawnLocation.Z += BoxBounds.BoxExtent.Z * FMath::FRandRange(-1.0f, 1.0f);
		
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToSpawn, &SpawnLocation) != nullptr;
	}
	return SpawnedActor;
}

void ASpawObject::ScheduleSpawn()
{
	float DeltaToNextSpawn = AvgSpawnTime + RandomSpawnTimeOffset * FMath::FRandRange(-1.0f, 1.0f);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawObject::SpawnScheduled, DeltaToNextSpawn, false);
}

void ASpawObject::EnableActorSpawnning(bool Enable)
{
	ShouldSpawn = Enable;
	if (Enable)
	{
		ScheduleSpawn();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASpawObject::SpawnScheduled()
{

	if (SpawnActor())
	{
		if (ShouldSpawn)
		{
			ScheduleSpawn();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor"));
	}
	
}
