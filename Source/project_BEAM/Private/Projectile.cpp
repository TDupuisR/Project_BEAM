// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Projectile Mesh"));
	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	projectileComponent-> InitialSpeed = 50.f;
	projectileComponent-> MaxSpeed = 50.f;
	projectileComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::InitialisePower(int power)
{
	ownPower = power;
	projectileCurrentParam = powerParameters[power];
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EProjectileType AProjectile::ProjectileGetType()
{
	return objType;
}
AProjectile& AProjectile::GetProjectile()
{
	canAccess = false;
	return *this;
}

