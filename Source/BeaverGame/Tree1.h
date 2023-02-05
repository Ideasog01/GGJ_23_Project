// (C) Evolved Brick 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tree1.generated.h"

UCLASS()
class BEAVERGAME_API ATree1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
