// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BeaverGame/Controllers/BeaverPlayerController.h"
#include "Resource.generated.h"

UENUM(BlueprintType)
enum ResourceType
{
	Roots UMETA(DisplayName = "Roots"),
	Logs UMETA(DisplayName = "Logs"),
	Stone UMETA(DisplayName = "Stone"),
	Water UMETA(DisplayName = "Water"),
	Berry UMETA(DisplayName = "Berry")
};

UCLASS()
class BEAVERGAME_API AResource : public AActor
{
	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	AResource();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ResourceMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = Resource)
	TEnumAsByte<ResourceType> Type;

	UPROPERTY(EditAnywhere, Category = Resource)
	int resourceAmount;

};