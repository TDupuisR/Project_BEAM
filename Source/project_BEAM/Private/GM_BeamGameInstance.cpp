// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_BeamGameInstance.h"

int UGM_BeamGameInstance::GetManche()
{
	return Manche;
}

void UGM_BeamGameInstance::SetManche(int NewManche)
{
	Manche = NewManche;
}

void UGM_BeamGameInstance::AddManche()
{
	Manche++;
}

int UGM_BeamGameInstance::GetPlayerPoints(int PlayerIndex)
{
	return PlayerPoints[PlayerIndex];
}

void UGM_BeamGameInstance::SetPlayerPoints(int PlayerIndex, int NewPoints)
{
	PlayerPoints[PlayerIndex] = NewPoints;
}

void UGM_BeamGameInstance::AddPlayerPoints(int PlayerIndex, int Points)
{
	PlayerPoints[PlayerIndex] += Points;
}

void UGM_BeamGameInstance::ResetPlayerPoints()
{
	PlayerPoints[0] = 0;
	PlayerPoints[1] = 0;
}

void UGM_BeamGameInstance::SetPlayerPoints(TArray<int> NewPoints)
{
	PlayerPoints = NewPoints;
}

TArray<int> UGM_BeamGameInstance::GetPlayersPoints()
{
	return PlayerPoints;
}

void UGM_BeamGameInstance::SetMaxManche(int NewMaxManche)
{
	MaxManche = NewMaxManche;	
}

int UGM_BeamGameInstance::GetMaxManche()
{
	return MaxManche;
}
