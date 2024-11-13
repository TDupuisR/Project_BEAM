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
	UFUNCTION(BlueprintCallable)
	int GetManche();

	UFUNCTION(BlueprintCallable)
	void SetManche(int NewManche);

	UFUNCTION(BlueprintCallable)
	void AddManche();

	UFUNCTION(BlueprintCallable)
	int GetPlayerPoints(int PlayerIndex);

	UFUNCTION(BlueprintCallable)
	void SetPlayerPoints(int PlayerIndex, int NewPoints);

	UFUNCTION(BlueprintCallable)
	void AddPlayerPoints(int PlayerIndex, int Points);

	UFUNCTION(BlueprintCallable)
	void ResetPlayerPoints();

	UFUNCTION(BlueprintCallable)
	void SetPlayerPoints(TArray<int> NewPoints);

	UFUNCTION(BlueprintCallable)
	TArray<int> GetPlayerPoints();

	UFUNCTION(BlueprintCallable)
	void SetMaxManche(int NewMaxManche);

	UFUNCTION(BlueprintCallable)
	int GetMaxManche();

private:
	int Manche = 0;

	TArray<int> PlayerPoints = {0, 0};

	int MaxManche = 3;	

};
