// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BeamCharacterSettings.generated.h"

class UBeamCharacterInputData;
class UInputMappingContext;

UCLASS(Config=Game, DefaultConfig, meta =(DisplayName = "Beam Character Settings"))
class PROJECT_BEAM_API UBeamCharacterSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	TSoftObjectPtr<UBeamCharacterInputData> InputData;

	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

#pragma region General 

	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "Vie max du personnage"))
	int MaxLife;

	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "Vie pour aller à la phase 2"))
	int LifeToFly;



	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "Permet de ralentir les dï¿½placements, valeur haute -> ralenti enormï¿½ment, valeur petite -> ralenti un peu"))
	double BrakingFrictionFactor;

	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "L'acceleration, grande -> Va trï¿½s vite ï¿½ sa vitesse max, petite -> va accelerer beaucoup plus lentement pour aller ï¿½ la vitesse max"))
	double MaxAcceleration;

	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "Permet de rendre comme une patinoire ou l'inverse"))
	double GroundFriction;

	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "Pour jouer sur le fait de retomber plus vite"))
	double GravityScale;

	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (ToolTip = "La masse du character :O"))
	double Mass;



#pragma endregion

#pragma region Walk

	UPROPERTY(Config, EditAnywhere, Category="Walk", meta = (ToolTip = "La vitesse maximale que le character peut avoir en ï¿½tat de marche"))
	double Walk_VelocityMax;

	UPROPERTY(Config, EditAnywhere, Category = "Walk", meta = (ToolTip = "Permet de stopper net avec une grande valeur"))
	double BreakingDecelerationWalking;


#pragma endregion

#pragma region Jump

	UPROPERTY(Config, EditAnywhere, Category = "Jump", meta = (ToolTip = "Pour le dï¿½placement dans les airs"))
	double Jump_VelocityMax;

	UPROPERTY(Config, EditAnywhere, Category = "Jump", meta = (ToolTip = "Force ï¿½ laquelle le joueur est projetï¿½"))
	double Jump_Force;

	UPROPERTY(Config, EditAnywhere, Category = "Jump", meta = (ToolTip = "Bas -> Pas beaucoup bouger, Haut -> Bouge comme si il ï¿½tait au sol mais dans les airs"))
	double AirControl;

#pragma endregion

#pragma region Falling
	
	UPROPERTY(Config, EditAnywhere, Category = "Fall", meta = (ToolTip = "Friction pour quand il tombe (ralentir la chute)"))
	double FallingLateralFriction;

#pragma endregion

#pragma region Flying

	UPROPERTY(Config, EditAnywhere, Category = "Fly", meta = (ToolTip = "Vitesse ï¿½ laquelle il se dï¿½place en flying"))
	double Fly_MaxSpeed;

	UPROPERTY(Config, EditAnywhere, Category = "Fly", meta = (ToolTip = "Permet de ralentir les dï¿½placements, valeur haute -> ralenti enormï¿½ment, valeur petite -> ralenti un peu"))
	double Fly_BrakingFrictionFactor;

	UPROPERTY(Config, EditAnywhere, Category = "Fly", meta = (ToolTip = "Force du dash (faut mettre une trï¿½s grande force, genre 100000)"))
	double Fly_DashForce;

	UPROPERTY(Config, EditAnywhere, Category = "Fly", meta = (ToolTip = "Timer du dash"))
	float Fly_DashTimer;

	UPROPERTY(Config, EditAnywhere, Category = "Fly", meta = (ToolTip = "Timer pour remettre les inputs"))
	float Fly_InputsTimer;

#pragma endregion





};
