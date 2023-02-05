// (C) Evolved Brick 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/InstancedStaticMesh.h"
#include "Rock1.generated.h"

UCLASS()
class BEAVERGAME_API ARock1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARock1();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMesh")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InstancedMesh")
	UInstancedStaticMeshComponent* InstancedMeshComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
