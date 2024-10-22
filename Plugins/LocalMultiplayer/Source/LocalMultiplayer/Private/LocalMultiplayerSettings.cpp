// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key) const
{

	TArray<FEnhancedActionKeyMapping> Mappings = IMCGames->GetMappings();

	for (int16 i = 0; i < Mappings.Num(); i++)
	{
		if (Mappings[i].Key == Key)
			return true;
	}

	return false;
}

int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfileIndexFromKey(const FKey& Key) const
{
	for (int16 i = 0; i < KeyboardProfilesData.Num(); i++)
	{
		if(KeyboardProfilesData[i].ContainsKey(Key))
			return i;
	}
	
	return -1;
}