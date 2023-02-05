// (C) Evolved Brick 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "StaticSpawn.generated.h"


UCLASS()
	class BEAVERGAME_API AStaticSpawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStaticSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UFUNCTION(BlueprintCallable)
		void SpawnActor();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
		UStaticMesh* StaticMeshToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
		UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedMesh")
		UInstancedStaticMeshComponent* InstancedMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpawnAmount = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ResourceIndex = 0;
	
	float spawnIndex;
	
	UPROPERTY()
	TArray<UInstancedStaticMeshComponent*> InstancedStaticMeshes;

private:
};