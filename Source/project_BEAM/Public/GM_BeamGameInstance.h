// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GM_BeamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_BEAM_API UGM_BeamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	int GetManche();

	void SetManche(int NewManche);

	void AddManche();

	int GetPlayerPoints(int PlayerIndex);

	void SetPlayerPoints(int PlayerIndex, int NewPoints);

	void AddPlayerPoints(int PlayerIndex, int Points);

	void ResetPlayerPoints();

	void SetPlayerPoints(TArray<int> NewPoints);

	TArray<int> GetPlayerPoints();

	void SetMaxManche(int NewMaxManche);

	int GetMaxManche();

private:
	int Manche = 0;

	TArray<int> PlayerPoints = {0, 0};

	int MaxManche = 3;	

};
