// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "UObject/Interface.h"
#include "ProjectileInterface.generated.h"

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	Player,
	Bullet,
	DestructWall
};

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UProjectileInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_BEAM_API IProjectileInterface
{
	GENERATED_BODY()

public:
	/** */
	virtual EProjectileType ProjectileGetType() = 0;
	virtual void ProjectileContext(int power, FVector position) = 0;
	virtual AProjectile& GetProjectile() = 0;
};