// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ProjectileSettings.generated.h"


UCLASS(Config=Game, DefaultConfig, meta =(DisplayName = "Projectile Settings"))
class PROJECT_BEAM_API UProjectileSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:

	#pragma region Projectile
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv0", meta = (ToolTip = "vitesse du projectile"))
	float speed_0;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv0", meta = (ToolTip = "largeur du projectile"))
	float width_0;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv0", meta = (ToolTip = "longueur du projectile"))
	float height_0;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv0", meta = (ToolTip = "duree de vie du projectile"))
	float lifespan_0;
	
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv1", meta = (ToolTip = "vitesse du projectile"))
	float speed_1;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv1", meta = (ToolTip = "largeur du projectile"))
	float width_1;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv1", meta = (ToolTip = "longueur du projectile"))
	float height_1;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv1", meta = (ToolTip = "duree de vie du projectile"))
	float lifespan_1;

	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv2", meta = (ToolTip = "vitesse du projectile"))
	float speed_2;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv2", meta = (ToolTip = "largeur du projectile"))
	float width_2;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv2", meta = (ToolTip = "longueur du projectile"))
	float height_2;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv2", meta = (ToolTip = "duree de vie du projectile"))
	float lifespan_2;

	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv3", meta = (ToolTip = "vitesse du projectile"))
	float speed_3;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv3", meta = (ToolTip = "largeur du projectile"))
	float width_3;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv3", meta = (ToolTip = "longueur du projectile"))
	float height_3;
	UPROPERTY(Config, EditAnywhere, Category = "Projectile Nv3", meta = (ToolTip = "duree de vie du projectile"))
	float lifespan_3;
#pragma endregion
};
