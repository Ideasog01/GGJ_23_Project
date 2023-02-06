// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawObject.h"

// Sets default values
ASpawObject::ASpawObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;

	InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMesh"));
	InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InstancedMeshComponent->SetupAttachment(RootComponent);
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
	if (StaticMeshToSpawn)
	{
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.bTraceComplex = true;
		
		FVector SpawnLocation = BoxBounds.Origin;

		SpawnLocation.X += BoxBounds.BoxExtent.X * FMath::FRandRange(-1.0f, 1.0f);
		SpawnLocation.Y += BoxBounds.BoxExtent.Y * FMath::FRandRange(-1.0f, 1.0f);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, SpawnLocation, SpawnLocation - FVector(0, 0, 10000), ECC_Visibility, CollisionParams))
		{
			SpawnLocation.Z = HitResult.Location.Z;
			
			// spawn at location relative to this actor, but rotated to match the normal of the surface
			FRotator SpawnRotation = GetActorRotation() + HitResult.ImpactNormal.Rotation();

			//FRotator SpawnRotation = HitResult.ImpactNormal.Rotation();
			InstancedMeshComponent->SetWorldScale3D(FVector(1, 1, 1));
			// spawn the instanced mesh
			InstancedMeshComponent->AddInstance(FTransform(SpawnRotation, SpawnLocation));
			
			// make sure the Transform of the instance is in world location
			InstancedMeshComponent->UpdateInstanceTransform(InstancedMeshComponent->GetInstanceCount() - 1, FTransform(SpawnRotation, SpawnLocation), true, true, true);
			
			// 
			
		}
		return true;
	}

	return false;
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
