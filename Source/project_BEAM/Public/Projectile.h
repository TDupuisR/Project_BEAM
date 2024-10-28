// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "ProjectileInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

USTRUCT(BlueprintType)
struct FProjectileParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float speed = 100.f;
	float width = 100.f;
	float height = 100.f;
	float lifeSpan = 100000.f;
};


UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Projectile"))
class PROJECT_BEAM_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
	void InitialisePower(int power);
	int ownPower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* projectileComponent;
	UPROPERTY(Config, EditAnywhere, Category="Power Parameters")
	TMap<int, FProjectileParameters> powerParameters;
	FProjectileParameters projectileCurrentParam;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	class UStaticMesh* ProjectileMesh;

private:
	EProjectileType objType = EProjectileType::Bullet;
	bool canAccess = true;
	
	virtual EProjectileType ProjectileGetType();
	virtual AProjectile& GetProjectile();
};
