// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Camera/CameraActor.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Make mesh selectable from UE Editor
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshSelection"));
	MeshSelection->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Find player
	APlayerController* PlayerController{GetWorld()->GetFirstPlayerController()};

	// Player views through selected camera
	PlayerController->SetViewTarget(ChooseCamera);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Soundtrack, GetActorLocation());

	CurrentHealth = MaxHealth;


}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Removed following line and put everything into SetActorLocation 
	// FVector Location = GetActorLocation() + (CurrentMovement * DeltaTime);

	// Updates player location by adding current location and movement
	SetActorLocation(GetActorLocation() + (CurrentMovement * DeltaTime));

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAxis("Forward", this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerPawn::Shoot);

}


void APlayerPawn::MoveForward(float Number)
{
	CurrentMovement.X = FMath::Clamp(Number, -1.f, 1.f) * MoveSpeed;
}

void APlayerPawn::MoveRight(float Number)
{
	CurrentMovement.Y = FMath::Clamp(Number, -1.f, 1.f) * MoveSpeed;

}

void APlayerPawn::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm shooting"));

	// Making a pointer to the in game world. To be able to spawn, we must first get the gameworld to spawn into.
	// Should be cheaper to make a variable of the world instead of calling it all the time
	UWorld* World = GetWorld();
	if (World)
	{
		if (CurrentAmmo > 0)
		{
			CurrentAmmo--;

		}
		else if (CurrentAmmo <= 0 && GameWon != true)
		{
			GameOver = true;
		}
		
		// Spawns the BulletBlueprint in the game world at the spawn location
		// Template function, choosing class and a blueprint compatible with the class
		// Gets the actor location plus an offset we have defined (spawnlocation) as the spawn point
		World->SpawnActor<ABullet>(BulletBlueprint, GetActorLocation() + SpawnLocation, GetActorRotation());
	}

}

void APlayerPawn::SetGameWon()
{
	GameWon = true;
}

void APlayerPawn::LooseHealth()
{

	CurrentHealth--;

	if (CurrentHealth <= 0)
	{
		GameOver = true;		
	}
}

int32 APlayerPawn::GetHealth()
{
	return CurrentHealth;
}

