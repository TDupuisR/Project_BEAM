// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BeamCharacterInputdata.h"
#include "Arena/ArenaPlayerStart.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"

class UInputMappingContext;
class ABeamCharacter;

UCLASS()
class PROJECT_BEAM_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;


protected:
	UPROPERTY()
	TArray<ABeamCharacter*> CharactersInArena;
	
private:
	
	UBeamCharacterInputData* LoadInputDataFromConfig();

	UInputMappingContext* LoadInputMappingContextFromConfig();
	
	void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors);

	void SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints);
	
	TSubclassOf<ABeamCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;
	
	void CreateAndInitPlayers() const;

#pragma region MancheSystem

public:
	UFUNCTION()
	void OnPlayerDeath(ABeamCharacter* pointeur);
	UFUNCTION(BlueprintCallable)
	bool IsPlayer1Win() const;

private:
	void AddEventsPlayers() const;
	


#pragma endregion

};
