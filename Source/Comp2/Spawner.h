// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class COMP2_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Setup")
	USceneComponent* MeshSelection{nullptr};

	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<class AEnemy> EnemyBlueprint{nullptr};

	UPROPERTY(EditAnywhere, Category="Setup")
	float SpawnTimer{5.f};

	UPROPERTY(EditAnywhere, Category="Setup")
	float DistanceBetweenEnemeies{100.f};

	UPROPERTY(EditAnywhere, Category="Setup")
	int32 EnemiesInWave{5};

	UPROPERTY(EditAnywhere, Category="Setup")
	int32 NumberOfWaves{5};

	int32 WavesCounter{0};
	
	UPROPERTY(BlueprintReadOnly)
	int32 TotalEnemies{EnemiesInWave*NumberOfWaves};

	UPROPERTY(BlueprintReadOnly)
	int32 EnemiesLeft{TotalEnemies};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetEnemies();

	int32 GetTotalEnemies();

	int32 GetCurrentEnemies();


private:
	float TimeGone{0.f};

	void SpawnEnemies();

};
