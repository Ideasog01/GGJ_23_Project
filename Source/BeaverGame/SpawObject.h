// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"


#include "Materials/MaterialInterface.h"
#include "Engine/StaticMesh.h"

#include "SpawObject.generated.h"



USTRUCT(BlueprintType) 
struct FResourceProperties
{
	GENERATED_USTRUCT_BODY()

public:

	FResourceProperties() {}
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
		int resourceindex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
		UMaterialInterface* material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
		UStaticMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", meta = (AllowPrivateAccess = true))
		FVector scale;



public:
	int GetIndex() { return resourceindex; }

	UMaterialInterface* GetMaterial() { return material; }

	UStaticMesh* GetMesh() { return mesh; }

	FVector GetScale() { return scale; }

};



UCLASS()
class BEAVERGAME_API ASpawObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawObject();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 0.5f;


	UFUNCTION(BlueprintCallable)
	void EnableActorSpawnning(bool Enable);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceProperties> resourceArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	UBoxComponent* SpawnBox;
private:

	UPROPERTY(EditAnywhere)
	bool ShouldSpawn = true;

	UFUNCTION()
	void SpawnScheduled();

	void ScheduleSpawn();
	
	

	FTimerHandle SpawnTimer;
};