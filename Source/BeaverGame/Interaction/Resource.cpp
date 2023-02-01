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
	
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AResource::ResetResource(FResourceProperties resourceProperties)
{
	Type = (ResourceType)resourceProperties.GetIndex();
	
	ResourceMesh->SetStaticMesh(resourceProperties.GetMesh());

	ResourceMesh->SetMaterial(0, resourceProperties.GetMaterial());

	ResourceMesh->SetWorldScale3D(resourceProperties.GetScale());

	ResourceMesh->SetWorldLocation(resourceProperties.GetLocation());
	
}

void AResource::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		//Add Resource to Inventory

		ABeaverPlayerController* PlayerController = Cast<ABeaverPlayerController>(GetWorld()->GetFirstPlayerController());
		
		if(PlayerController != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Resource Added!"));
			PlayerController->AddResource(Type, resourceAmount);
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			SetActorTickEnabled(false);
		}
	}
}

