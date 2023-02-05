// (C) Evolved Brick 2023

#include "StaticSpawn.h"
#include "Characters/PlayerCharacter.h"

#include "BeaverGame/Controllers/BeaverPlayerController.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Containers/Array.h"


// Sets default values
AStaticSpawn::AStaticSpawn()
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
void AStaticSpawn::BeginPlay()
{
	Super::BeginPlay();
	SpawnActor();
	InstancedMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AStaticSpawn::OnOverlapBegin);
	InstancedMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AStaticSpawn::OnOverlapEnd);
}

void AStaticSpawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AStaticSpawn::SpawnActor()
{
	if (StaticMeshToSpawn)
	{
		for (int i = 0; i < SpawnAmount; i++)
		{
			InstancedMeshComponent->SetStaticMesh(StaticMeshToSpawn);
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
				//FRotator SpawnRotation = GetActorRotation() + HitResult.ImpactNormal.Rotation();

				//FRotator SpawnRotation = HitResult.ImpactNormal.Rotation();
				InstancedMeshComponent->SetWorldScale3D(FVector(1, 1, 1));

				// add instance and add index
				int32 NewInstanceIndex = InstancedMeshComponent->AddInstance(FTransform(SpawnLocation));
				
				// Set custom data values for this instance
				InstancedMeshComponent->SetCustomDataValue(NewInstanceIndex, 0, i);

				// make sure the Transform of the instance is in world location
				InstancedMeshComponent->UpdateInstanceTransform(InstancedMeshComponent->GetInstanceCount() - 1, FTransform(SpawnLocation), true, true, true);
				
				// add collision to the instance, and bind the OnOverlapBegin function
				InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				InstancedMeshComponent->SetCollisionProfileName("OverlapAllDynamic");
			}
		}
	}
}

void AStaticSpawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapping Component"));
		// remove the instance from the instanced mesh component
		InstancedMeshComponent->RemoveInstance(SweepResult.Item);
	}
}

void AStaticSpawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass())) 
	{
		ABeaverPlayerController* PlayerController = Cast<ABeaverPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerController->AddResource(ResourceIndex, 1);
	}
}
