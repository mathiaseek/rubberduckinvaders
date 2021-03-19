 // Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PlayerPawn.h"
#include "Engine/TriggerBase.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSelection"));
	MeshSelection->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Cast<UStaticMeshComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += GetActorForwardVector() * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);

}

 void AEnemy::Hit()
 {
	Destroy();
	
	// Probably not the cheapest way to get access to Spawners functiuons, but the only way I managed to make it work	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(),Actors);
	Cast<ASpawner>(Actors[0])->SetEnemies();
	UE_LOG(LogTemp, Warning, TEXT("TotalEnemies: %i"), Cast<ASpawner>(Actors[0])->GetTotalEnemies());
	UE_LOG(LogTemp, Warning, TEXT("CurrentEnemies: %i"), Cast<ASpawner>(Actors[0])->GetCurrentEnemies());

	//				UE_LOG(LogTemp, Warning, TEXT("Enemies left: %i"), EnemiesLeft);
 }

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor->IsA(ATriggerBase::StaticClass()))
	{
		TArray<AActor*> PlayerActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(),PlayerActors);
		Cast<APlayerPawn>(PlayerActors[0])->LooseHealth();

		UE_LOG(LogTemp, Warning, TEXT("%s hit triggerbox"), *AEnemy::GetName());
		UE_LOG(LogTemp, Warning, TEXT("You lost a life"));

		TArray<AActor*> SpawnActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(),SpawnActors);
		Cast<ASpawner>(SpawnActors[0])->SetEnemies();

		
		// Trigger loose condition

	}

}
