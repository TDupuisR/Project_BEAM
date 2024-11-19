// Fill out your copyright notice in the Description page of Project Settings.

#include "MatchGameMode.h"

#include "LocalMutliplayerSubsystem.h"
#include "Arena/ArenaPlayerStart.h"
#include "Arena/ArenaCamera.h"
#include "Characters/BeamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Arena/ArenaSettings.h"
#include "Characters/BeamCharacterSettings.h"
#include "GM_BeamGameInstance.h"

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateAndInitPlayers();
	
	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayerStartActorsInArena(PlayerStartsPoints);
	SpawnCharacters(PlayerStartsPoints);
	AddEventsPlayers();

	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UGM_BeamGameInstance* BeamGameInstance = Cast<UGM_BeamGameInstance>(GameInstance);

	if (BeamGameInstance->GetPlayersPoints()[0] - BeamGameInstance->GetPlayersPoints()[1] >= GetDefault<UArenaSettings>()->MancheDiffShield) {
		CharactersInArena[1]->SetShield(1);
	}
	else if (BeamGameInstance->GetPlayersPoints()[0] - BeamGameInstance->GetPlayersPoints()[1] <= -GetDefault<UArenaSettings>()->MancheDiffShield) {
		CharactersInArena[0]->SetShield(1);
	}
	
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

void AMatchGameMode::AddEventsPlayers() const
{
	for (int i = 0; i < CharactersInArena.Num(); i++)
	{
		ABeamCharacter* Character = CharactersInArena[i];
		if (Character == nullptr) continue;

		Character->OnDeathEvent.AddDynamic(this, &AMatchGameMode::OnPlayerDeath);
	}
}

void AMatchGameMode::OnPlayerDeath(ABeamCharacter* DeadPlayer)
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UGM_BeamGameInstance* BeamGameInstance = Cast<UGM_BeamGameInstance>(GameInstance);

	GEngine->AddOnScreenDebugMessage(
		-1,
		15.0f,
		FColor::Purple,
		FString::Printf(TEXT("PLAYER DEATH"))
	);

	if (BeamGameInstance == nullptr) return;

	if (BeamGameInstance->GetMatchType() == EMatchTypeID::Free)
	{

		BeamGameInstance->AddPlayerPoints(0, 1);
		BeamGameInstance->AddPlayerPoints(1, 1);

		TArray<int> PointsPlayers = BeamGameInstance->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 B : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 B : %d"), PointsPlayers[1]);

		if (CharactersInArena.Find(DeadPlayer) < 0) return;
		BeamGameInstance->SetPlayerPoints(CharactersInArena.Find(DeadPlayer), -1);

		PointsPlayers = BeamGameInstance->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 A : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 A : %d"), PointsPlayers[1]);


		BeamGameInstance->AddManche();

		BeamGameInstance->DeployEvent();


		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Purple,
			FString::Printf(TEXT("MATCH TYPE FREE"))
		);

		// AFFICHE LE MENU DE FIN DE PARTIE (RECOMMENCE OU QUITTER)
		// Here ->
		// Appeler ResetPlayerPoints() pour remettre les points à 0

		BeamGameInstance->ResetPlayerPoints();

		// A enlever quand menu fin
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

		return;
	}
	else if (BeamGameInstance->GetMatchType() == EMatchTypeID::Deathmatch) {

		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Purple,
			FString::Printf(TEXT("MATCH TYPE GAMEMODE"))
		);

		BeamGameInstance->AddPlayerPoints(0, 1);
		BeamGameInstance->AddPlayerPoints(1, 1);

		TArray<int> PointsPlayers = BeamGameInstance->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 B : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 B : %d"), PointsPlayers[1]);

		if (CharactersInArena.Find(DeadPlayer) < 0) return;
		BeamGameInstance->SetPlayerPoints(CharactersInArena.Find(DeadPlayer), -1);

		PointsPlayers = BeamGameInstance->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 A : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 A : %d"), PointsPlayers[1]);


		BeamGameInstance->AddManche();

		BeamGameInstance->DeployEvent();

		if (BeamGameInstance->GetPlayersPoints()[0] >= BeamGameInstance->GetMaxManche() || BeamGameInstance->GetPlayersPoints()[1] >= BeamGameInstance->GetMaxManche())
		{
			// END OF THE GAME
			// GO TO MENU
			GEngine->AddOnScreenDebugMessage(
				-1,
				20.0f,
				FColor::Purple,
				FString::Printf(TEXT("------------- END GAME ------------"))
			);

			// AFFICHE LE MENU DE FIN DE PARTIE (RECOMMENCE OU QUITTER)
			// Here ->

		}
		else {
			UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		}

	}

	
	


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

