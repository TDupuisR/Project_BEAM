// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_BeamGameInstance.h"
#include "MatchSystemBeam.h"

#include "Match/BeamMatchSystem.h"

void UGM_BeamGameInstance::Init()
{
	Super::Init();
	matchSystem = NewObject<UMatchSystemBeam>(this);
}

void UGM_BeamGameInstance::DeployEvent()
{
	OnChangePoints.Broadcast();
}


void UGM_BeamGameInstance::SetLastSpawnNumber(int NewSpawnNumber)
{
	LastSpawnNumber = NewSpawnNumber;
}

int UGM_BeamGameInstance::GetLastSpawnNumber()
{
	return LastSpawnNumber;
}

void UGM_BeamGameInstance::SetNumberPairAppeared(int NewNumber)
{
	NumberPairAppeared = NewNumber;
}

int UGM_BeamGameInstance::GetNumberPairAppeared()
{
	return NumberPairAppeared;
}

void UGM_BeamGameInstance::ChangeMatchType(EMatchTypeID NewMatchType)
{
	matchSystem->SetMatchType(NewMatchType);
}

TArray<int> UGM_BeamGameInstance::GetPlayersPoints() const
{
	return matchSystem->GetPlayersPoints();
}

