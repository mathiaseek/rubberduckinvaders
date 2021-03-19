// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class COMP2_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Make mesh assignable in UE
	UPROPERTY(EditAnywhere, Category = "Setup");
	UStaticMeshComponent* MeshSelection{nullptr};

	// Make speed changeable in UE
	UPROPERTY(EditAnywhere, Category = "Setup");
	float MoveSpeed{100.f};

	// Make camera able to be set at a static angle inside UE
	UPROPERTY(EditAnywhere, Category = "Setup");
	ACameraActor* ChooseCamera{nullptr};
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Setup");
	int32 Ammo{100};

	UPROPERTY(BlueprintReadOnly, Category = "Setup");
	int32 CurrentAmmo{Ammo};

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Setup");
	int32 MaxHealth{10};
	UPROPERTY(BlueprintReadWrite);
	int32 CurrentHealth{MaxHealth};
	
	// For making the blueprint version of the Bullet (not the C++ class) possible to choose in the UE Editor
	UPROPERTY(EditAnywhere, Category = "Setup");
	TSubclassOf<class ABullet> BulletBlueprint;

	// Makes the spawn location adjustable from the UE Editor. It's easier to adjust the correct location from there
	UPROPERTY(EditAnywhere, Category = "Setup");
	FVector SpawnLocation{ 0.f, 0.f, 0.f };

	UPROPERTY(EditAnywhere, Category = "Setup")
	USoundBase* Soundtrack;

	UPROPERTY(BlueprintReadWrite);
	bool GameWon {false};
	
	UPROPERTY(BlueprintReadWrite);
	bool GameOver {false};


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void LooseHealth();
	int32 GetHealth();
	void SetGameWon();



private:
	void MoveForward(float Number);
	void MoveRight(float Number);
	void Shoot();

	FVector CurrentMovement{0.f};
};
