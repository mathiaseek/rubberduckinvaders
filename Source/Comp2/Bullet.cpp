// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Engine/TriggerBase.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates the collider
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	
	// Assigning the Collider to the RootComponent
	RootComponent = Collider;
	
	// Makes mesh selectable from the UE Editor
	MeshSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSelection"));
	
	// Makes MeshSelection appear as a child of the Root (the Collider) in the UE Editor
	MeshSelection->SetupAttachment(RootComponent);


	Collider->SetGenerateOverlapEvents(true);

	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// Casting rootcomponent to become a sphere component
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation(), 0.3);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// A timer updating the time each frame
	TimeLived += DeltaTime;

	// Checks if the bullet be destroyed based on the time lived
	if (TimeLived > TimeToDestruction)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet died naturally from old age"));
		Destroy();
	}

	// If not, it updates the location of the bullet
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += GetActorForwardVector() * MoveSpeed * DeltaTime;
		SetActorLocation(CurrentLocation);
	}

	
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet hit: %s"), *OtherActor->GetName());
	
	if (OtherActor->IsA(AEnemy::StaticClass()))
	{
		// Calls the hit function of the enemy. Will make it easier to implement HP or change what happens on a hit
		Cast<AEnemy>(OtherActor)->Hit();
		Destroy();
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());

	}

	if (OtherActor->IsA(ATriggerBase::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Bullet hit trigger: %s"), *OtherActor->GetName());

	}

}
