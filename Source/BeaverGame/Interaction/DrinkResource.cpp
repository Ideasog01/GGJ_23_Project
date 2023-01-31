// Fill out your copyright notice in the Description page of Project Settings.


#include "BeaverGame/Interaction/DrinkResource.h"

// Sets default values
ADrinkResource::ADrinkResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADrinkResource::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ADrinkResource::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ADrinkResource::OnOverlapEnd);
}

void ADrinkResource::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter->bIsNearWater = true;
	UE_LOG(LogTemp, Warning, TEXT("Player Near Water!"));
}

void ADrinkResource::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerCharacter->bIsNearWater = false;
	UE_LOG(LogTemp, Warning, TEXT("Player left the Water :("));
}

// Called every frame
void ADrinkResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

