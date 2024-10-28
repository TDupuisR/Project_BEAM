// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerAim.h"
#include "Projectile.h"


// Sets default values for this component's properties
UPlayerAim::UPlayerAim()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UPlayerAim::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

FVector3f UPlayerAim::AimDir(const FVector2f& dir, const FVector3f& playerPos)
{	
	FVector2f DirNormal = dir.GetSafeNormal();
	return FVector3f(playerPos.X + DirNormal.X * Radius, playerPos.Y, playerPos.Z + DirNormal.Y * Radius );
}

void UPlayerAim::Shoot(FVector spawnLocation, FVector direction, AActor* playerActor, int power)
{
	if(ProjectileActor)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = playerActor;
		spawnParams.Instigator = playerActor->GetInstigator();
		
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileActor, spawnLocation, direction.ToOrientationRotator(), spawnParams);
		if(projectile == nullptr) return;

		if (power > 3) power = 3;
		if (power < 0) power = 0;
		projectile->InitialisePower(power);
	}
}

// Called every frame
void UPlayerAim::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

