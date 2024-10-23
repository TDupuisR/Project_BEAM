// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BeamCharacterSettings.generated.h"

class ABeamCharacter;

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta =(DisplayName = "Beam Character Settings"))
class PROJECT_BEAM_API UBeamCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, Category="Walk")
	double Walk_VelocityMax;

	UPROPERTY(Config, EditAnywhere, Category = "Jump")
	double Jump_VelocityMax;

	UPROPERTY(Config, EditAnywhere, Category = "Jump")
	double Jump_Force;





};
