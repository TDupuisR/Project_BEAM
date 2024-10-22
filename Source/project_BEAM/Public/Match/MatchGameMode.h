// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"

class APlayerCharacter;
class AArenaPlayerStart;
/**
 * 
 */
UCLASS()
class PROJECT_BEAM_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere)
	TArray<APlayerCharacter*> PlayerCharacterInsideArena;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerCharacter> PlayerCharacterClassP0;

private:
	void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors);
	void SpawnPlayers(const TArray<AArenaPlayerStart*>& SpawnPoints);
	TSubclassOf<APlayerCharacter> GetPayerCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;
};
