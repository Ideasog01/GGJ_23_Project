// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawObject.h"
#include "Interaction/Resource.h"



class Resource;


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
	AActor* SpawnedActor = nullptr;
	
	if (ActorClassToSpawn)
	{
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(SpawnedActor);
		CollisionParams.bTraceComplex = true;
		
		FVector SpawnLocation = BoxBounds.Origin;
		
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToSpawn, &SpawnLocation);

		SpawnedActor->SetActorLocation(SpawnLocation);


		

		AResource* Resource = Cast<AResource>(SpawnedActor);
		Resource->ResetResource(resourceArray[FMath::RandRange(0, resourceArray.Num() - 1)]);
		UStaticMeshComponent* ObjectMeshComponent = SpawnedActor->FindComponentByClass<UStaticMeshComponent>();

		if (ObjectMeshComponent)
		{
			
			
			FVector ObjectMeshExtent = ObjectMeshComponent->Bounds.GetBox().GetExtent();
			float ObjectHalfHeight = ObjectMeshExtent.Z;

			SpawnLocation.X += BoxBounds.BoxExtent.X * FMath::FRandRange(-1.0f, 1.0f);

			SpawnLocation.Y += BoxBounds.BoxExtent.Y * FMath::FRandRange(-1.0f, 1.0f);

			
			

			if (GetWorld()->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation - FVector(0, 0, 10000), ECC_Visibility, CollisionParams))
			{
				SpawnLocation.Z = HitResult.Location.Z;
				SpawnLocation.Z += ObjectHalfHeight;
				SpawnedActor->SetActorLocation(SpawnLocation);
			}
		}
		

	}
	
	

	return SpawnedActor != nullptr;
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
