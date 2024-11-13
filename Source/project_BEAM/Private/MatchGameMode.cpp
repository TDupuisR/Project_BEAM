// Fill out your copyright notice in the Description page of Project Settings.

#include "MatchGameMode.h"

#include "LocalMutliplayerSubsystem.h"
#include "Arena/ArenaPlayerStart.h"
#include "Arena/ArenaCamera.h"
#include "Characters/BeamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Arena/ArenaSettings.h"
#include "Characters/BeamCharacterSettings.h"

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateAndInitPlayers();
	
	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayerStartActorsInArena(PlayerStartsPoints);
	SpawnCharacters(PlayerStartsPoints);
	
	// TObjectPtr<AActor> camera = UGameplayStatics::GetActorOfClass(GetWorld(), AArenaCamera::StaticClass());
	//
	// TObjectPtr<APlayerController> playerController = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	// if (playerController)
	// {
	// 	playerController->SetViewTargetWithBlend(camera);
	// 	UE_LOG(LogTemp, Warning, TEXT("Player controller is true"));
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Player controller is null"));
	// }
}

void AMatchGameMode::FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultsActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArenaPlayerStart::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart>(FoundActors[i]);
		if (ArenaPlayerStartActor == nullptr) continue;

		ResultsActors.Add(ArenaPlayerStartActor);
	}
}

TSubclassOf<ABeamCharacter> AMatchGameMode::GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const
{
	const UArenaSettings* ArenaSettings = GetDefault<UArenaSettings>();

	GEngine->AddOnScreenDebugMessage(
		-1,
		10.0f,
		FColor::Red,
		FString::Printf(TEXT("WOW OMG : %d"), InputType)
		);
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.0f,
		FColor::Red,
		FString::Printf(TEXT("PAS : %d"), EAutoReceiveInput::Player0)
		);

	GEngine->AddOnScreenDebugMessage(
		-1,
		10.0f,
		FColor::Red,
		FString::Printf(TEXT("PAS : %d"), EAutoReceiveInput::Player1)
		);
	
	switch (InputType)
	{
	case EAutoReceiveInput::Player0:
		return ArenaSettings->BeamCharacterClassP1;

	case EAutoReceiveInput::Player1:
		return ArenaSettings->BeamCharacterClassP2;

	default:
		return nullptr;
	}
}

void AMatchGameMode::CreateAndInitPlayers() const
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if (GameInstance == nullptr) return;

	ULocalMultiplayerSubsystem* LocalMultiplayerSubsystem = GameInstance->GetSubsystem<ULocalMultiplayerSubsystem>();
	if (LocalMultiplayerSubsystem == nullptr) return;

	LocalMultiplayerSubsystem->CreateAndInitPlayers();
}

void AMatchGameMode::SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints)
{
	UBeamCharacterInputData* InputData = LoadInputDataFromConfig();
	UInputMappingContext* InputMappingContext = LoadInputMappingContextFromConfig();

	for (AArenaPlayerStart* SpawnPoint : SpawnPoints)
	{
		EAutoReceiveInput::Type InputType = SpawnPoint->AutoReceiveInput.GetValue();
		TSubclassOf<ABeamCharacter> SmashCharacterClass = GetSmashCharacterClassFromInputType(InputType);
		if (SmashCharacterClass == nullptr) continue;

		ABeamCharacter* NewCharacter = GetWorld()->SpawnActorDeferred<ABeamCharacter>(
			SmashCharacterClass,
			SpawnPoint->GetTransform()
			);

		if (NewCharacter == nullptr) continue;
		NewCharacter->InputData = InputData;
		NewCharacter->InputMappingContext = InputMappingContext;
		NewCharacter->AutoPossessPlayer = SpawnPoint->AutoReceiveInput;
		NewCharacter->SetOrientX(SpawnPoint->GetStartOrientX());
		NewCharacter->FinishSpawning(SpawnPoint->GetTransform());

		CharactersInArena.Add(NewCharacter);
	}
}


UBeamCharacterInputData* AMatchGameMode::LoadInputDataFromConfig()
{
	const UBeamCharacterSettings* CharacterSettings = GetDefault<UBeamCharacterSettings>();
	if (CharacterSettings == nullptr) return nullptr;
	return CharacterSettings->InputData.LoadSynchronous();
}



UInputMappingContext* AMatchGameMode::LoadInputMappingContextFromConfig()
{
	const UBeamCharacterSettings* CharacterSettings = GetDefault<UBeamCharacterSettings>();
	if (CharacterSettings == nullptr) return nullptr;
	return CharacterSettings->InputMappingContext.LoadSynchronous();
}

