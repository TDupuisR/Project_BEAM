// Fill out your copyright notice in the Description page of Project Settings.

#include "Match/MatchGameMode.h"

#include "LandscapeProxy.h"
#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayerStartActorInArena(PlayerStartsPoints);
	SpawnCharacters(PlayerStartsPoints);

	
}

void AMatchGameMode::FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArenaPlayerStart::StaticClass(), FoundActors);

	for(int i = 0; i < FoundActors.Num(); i++)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if(ArenaPlayerStartActor == nullptr) continue;
		
		ResultsActors.Add(ArenaPlayerStartActor);
	}
}

void AMatchGameMode::SpawnPlayers(const TArray<AArenaPlayerStart*>& SpawnPoints)
{
	for(AArenaPlayerStart* SpawnPoint : SpawnPoints)
	{
		EAutoReceiveInput::Type InputType = SpawnPoint->AutoReceive.GetValue();
		TSubclassOf<APlayerCharacter> playerClass = GetPlayerCharacterClassFromInputType(InputType);
		if(playerClass == nullptr)continue;

		APlayerCharacter* NewPlayerCharacter = GetWorld()->SpawnActorDeferred<APlayerCharacter>(playerClass, SpawnPoint->GetTransform());
		if(NewPlayerCharacter == nullptr)continue;
		NewPlayerCharacter->AutoPossessPlayer = SpawnPoint ->AutoReceiveInput;
		NewPlayerCharacter->SetOrientX(SpawnPoint->GetStartOrientX());
		NewPlayerCharacter->FinishSpawning(SpawnPoint->GetTransform());

		PlayerCharacterInsideArena.Add(NewPlayerCharacter);	
	}
}

TSubclassOf<APlayerCharacter> AMatchGameMode::GetPayerCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const
{
	const UArenaSettings = Default<UArenaSettings>();
	Switch (InputType)
	{
	case EAutoReceiveInputType::Player0:
		return PlayerCharacterClassP0;
	Default:
		return nullptr;
	}
}
