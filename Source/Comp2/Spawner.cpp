// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Enemy.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Make mesh selectable from UE Editor
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSelection"));
	MeshSelection->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	TotalEnemies = (EnemiesInWave*NumberOfWaves);
	EnemiesLeft = TotalEnemies;



}

void ASpawner::SpawnEnemies()
{
	UWorld* World = GetWorld();
	if (World && EnemyBlueprint)
	{
		if (WavesCounter < NumberOfWaves)
		{
			FVector Offset{0.f};
			//AEnemy* tempPtr{nullptr};
			for (int i = 0; i < EnemiesInWave; ++i)
			{
				Offset.Y += DistanceBetweenEnemeies;
				World->SpawnActor<AEnemy>(EnemyBlueprint, GetActorLocation() + Offset, GetActorRotation());

//				UE_LOG(LogTemp, Warning, TEXT("TotalEnemies: %i"), TotalEnemies);
//				UE_LOG(LogTemp, Warning, TEXT("Enemies left: %i"), EnemiesLeft);


			}
			WavesCounter++;
		}
		
		
	}
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeGone += DeltaTime;
	if (TimeGone > SpawnTimer)
	{
		TimeGone = 0.f;
		SpawnEnemies();
	}

}

void ASpawner::SetEnemies()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemies left: %i"),EnemiesLeft);
	EnemiesLeft--;


	if (EnemiesLeft == 0)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(),Actors);
		if (Cast<APlayerPawn>(Actors[0])->GetHealth() > 0)
		{
			Cast<APlayerPawn>(Actors[0])->SetGameWon();
		}
	}

	
}

int32 ASpawner::GetTotalEnemies()
{
	return TotalEnemies;
}

int32 ASpawner::GetCurrentEnemies()
{
	return EnemiesLeft;
}







