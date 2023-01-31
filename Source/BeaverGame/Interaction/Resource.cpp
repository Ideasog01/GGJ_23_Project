// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Interaction/Resource.h"

// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ResourceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Resource Mesh"));
	ResourceMesh->SetupAttachment(RootComponent);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AResource::OnOverlapBegin);
	PlayerController = Cast<ABeaverPlayerController>(GetWorld()->GetFirstPlayerController());
	
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResource::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision Occurred"));

	if(ActorHasTag("Player"))
	{
		//Add Resource to Inventory
		PlayerController->AddResource(*this, resourceAmount);
	}
}

int AResource::GetResourceType()
{
	return Type;
}

