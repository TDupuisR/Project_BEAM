// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerAim.h"


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

FVector3f UPlayerAim::AimDir(const FVector2f& Dir, const FVector3f& PlayerPos)
{	
	FVector2f DirNormal = Dir.GetSafeNormal();
	return FVector3f(PlayerPos.X + DirNormal.X * Radius, PlayerPos.Y, PlayerPos.Z + DirNormal.Y * Radius );
}

// Called every frame
void UPlayerAim::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

