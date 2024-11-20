// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MatchTypeID.h"

#include "GM_BeamGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChangePoints);


UCLASS()
class PROJECT_BEAM_API UGM_BeamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnChangePoints OnChangePoints;

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
	void DeployEvent();

	void SetPlayerPoints(TArray<int> NewPoints);

	UFUNCTION(BlueprintCallable)
	TArray<int> GetPlayersPoints();

	UFUNCTION(BlueprintCallable)
	void SetMaxManche(int NewMaxManche);

	UFUNCTION(BlueprintCallable)
	int GetMaxManche();

	UFUNCTION(BlueprintCallable)
	EMatchTypeID GetMatchType();

	UFUNCTION(BlueprintCallable)
	void SetMatchType(EMatchTypeID NewMatchType);

	UFUNCTION(BlueprintCallable)
	void SetLastSpawnNumber(int NewSpawnNumber);

	UFUNCTION(BlueprintCallable)
	int GetLastSpawnNumber();

	UFUNCTION(BlueprintCallable)
	void SetNumberPairAppeared(int NewNumber);

	UFUNCTION(BlueprintCallable)
	int GetNumberPairAppeared();

private:
	UPROPERTY()
	int Manche = 0;

	UPROPERTY()
	int LastSpawnNumber = 0;

	UPROPERTY()
	int NumberPairAppeared = 0;

	UPROPERTY()
	TArray<int> PlayerPoints = {0, 0};

	UPROPERTY()
	int MaxManche = 3;	

	UPROPERTY()
	EMatchTypeID MatchType = EMatchTypeID::Deathmatch;

};
