// (C) Evolved Brick 2023


#include "Rock1.h"

// Sets default values
ARock1::ARock1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMeshComponent"));
	InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = InstancedMeshComponent;
	
	
}

// Called when the game starts or when spawned
void ARock1::BeginPlay()
{
	Super::BeginPlay();
	
	if (StaticMesh)
	{
		InstancedMeshComponent->SetStaticMesh(StaticMesh);
		InstancedMeshComponent->AddInstance(FTransform(FVector(0.f, 0.f, 0.f)));
	}
}


// Called every frame
void ARock1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

