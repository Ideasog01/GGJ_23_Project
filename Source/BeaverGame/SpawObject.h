// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "SpawObject.generated.h"

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


private:

	UPROPERTY(EditAnywhere)
		bool ShouldSpawn = true;

	UFUNCTION()
	void SpawnScheduled();

	void ScheduleSpawn();

	UPROPERTY(EditDefaultsOnly)
		
	UBoxComponent* SpawnBox;

	FTimerHandle SpawnTimer;
};