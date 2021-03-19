// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class COMP2_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// This is the mesh
	UPROPERTY(EditAnywhere, Category = "Setup");
	UStaticMeshComponent* MeshSelection{nullptr};
	
	// This is for controlling the collision of the bullet.
	UPROPERTY(EditAnywhere, Category = "Setup")
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MoveSpeed{ 400.f };

	float TimeLived{0.f};
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float TimeToDestruction{ 3.f };

	UPROPERTY(EditAnywhere, Category = "Setup")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Setup")
	USoundBase* ShootSound;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	UParticleSystem* HitFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 EnemiesHit{0};

	
	

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	        UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	        bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
