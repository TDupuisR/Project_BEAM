// Fill out your copyright notice in the Description page of Project Settings.

#include "MatchGameMode.h"

#include "LocalMutliplayerSubsystem.h"
#include "Arena/ArenaPlayerStart.h"
#include "Characters/BeamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Arena/ArenaSettings.h"
#include "Characters/BeamCharacterSettings.h"
#include "GM_BeamGameInstance.h"
#include "HAL/PlatformProcess.h"
#include "Match/BeamMatchSystem.h"




void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();
	CreateAndInitPlayers();

	TArray<AArenaPlayerStart*> PlayerStartsPoints;
	FindPlayerStartActorsInArena(PlayerStartsPoints);
	CalculateNewPair(PlayerStartsPoints);
	SpawnCharacters(PlayerStartsPoints);
	AddEventsPlayers();

	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UGM_BeamGameInstance* BeamGameInstance = Cast<UGM_BeamGameInstance>(GameInstance);
	BeamGameInstance->GetMancheSystem()->InitializeMatch(CharactersInArena.Num());
	BeamGameInstance->GetMancheSystem()->SetCharacters(CharactersInArena);



	/*if (BeamGameInstance->GetPlayersPoints()[0] - BeamGameInstance->GetPlayersPoints()[1] >= GetDefault<UArenaSettings>()->MancheDiffShield) {
		CharactersInArena[1]->SetShield(1);
	}
	else if (BeamGameInstance->GetPlayersPoints()[0] - BeamGameInstance->GetPlayersPoints()[1] <= -GetDefault<UArenaSettings>()->MancheDiffShield) {
		CharactersInArena[0]->SetShield(1);
	}*/
	
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

void AMatchGameMode::SetSelectedPair(int NewPair)
{
	SelectedPair = NewPair;
}

int AMatchGameMode::GetSelectedPair() const
{
	return SelectedPair;
}

void AMatchGameMode::SetPairNumberMax(int NewMax)
{
	PairNumberMax = NewMax;
}

int AMatchGameMode::GetPairNumberMax() const
{
	return PairNumberMax;
}

void AMatchGameMode::CheckSpawnPairs(TArray<AArenaPlayerStart*> PlayerStartsPoints)
{

	TArray<int> listPairsMax;

	for (int i = 0; i < GetPairNumberMax()+1; i++) {
		listPairsMax.Add(0);
	}

	for (AArenaPlayerStart* SpawnPoint : PlayerStartsPoints) { 
		listPairsMax[SpawnPoint->SpawnPair]++;
	}

	for (int i = 0; i < listPairsMax.Num(); i++) {
		if (listPairsMax[i] > 1) {
			listSpawnPairPossible.Add(i);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("PAIR NOT POSSIBLE : %d"), listPairsMax[i]);
		}
	}
}

void AMatchGameMode::NewPair(int Max)
{
	if (Max == 0) return;

	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	UGM_BeamGameInstance* BeamGameInstance = Cast<UGM_BeamGameInstance>(GameInstance);

	if (BeamGameInstance == nullptr) return;

	int random = FMath::RandRange(0, listSpawnPairPossible.Num()-1);

	if (BeamGameInstance->GetLastSpawnNumber() == listSpawnPairPossible[random]) {
		BeamGameInstance->SetLastSpawnNumber(listSpawnPairPossible[random]);
		BeamGameInstance->SetNumberPairAppeared(BeamGameInstance->GetNumberPairAppeared() + 1);

		if (BeamGameInstance->GetNumberPairAppeared() >= 3) {
			BeamGameInstance->SetNumberPairAppeared(0);
			listSpawnPairPossible[0];

			if (listSpawnPairPossible[random] != BeamGameInstance->GetLastSpawnNumber()) {
				BeamGameInstance->SetLastSpawnNumber(listSpawnPairPossible[random]);
			}
			else {
				listSpawnPairPossible[1];
				BeamGameInstance->SetLastSpawnNumber(listSpawnPairPossible[random]);
			}
		}
	}
	else {
		BeamGameInstance->SetNumberPairAppeared(0);
	}


	SetSelectedPair(listSpawnPairPossible[random]);

}

void AMatchGameMode::CalculateNewPair(TArray<AArenaPlayerStart*> PlayerStartsPoints)
{


	SetPairNumberMax(0);

	for (int i = 0; i < PlayerStartsPoints.Num(); i++)
	{
		if (PlayerStartsPoints[i]->SpawnPair > GetPairNumberMax())
		{
			SetPairNumberMax(PlayerStartsPoints[i]->SpawnPair);
		}
	}
	
	CheckSpawnPairs(PlayerStartsPoints);
	NewPair(GetPairNumberMax());
}

void AMatchGameMode::OnPlayerDeath(ABeamCharacter* pointeur)
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

	if (MancheEnd) return;

	if (!BeamGameInstance->GetMancheSystem()->IsMancheFinished()) return;

	MancheEnd = true;
	if (BeamGameInstance->GetMancheSystem()->GetMatchType() == EMatchTypeID::Free)
	{

		BeamGameInstance->GetMancheSystem()->AddPlayerPoints(0, 1);
		BeamGameInstance->GetMancheSystem()->AddPlayerPoints(1, 1);

		TArray<int> PointsPlayers = BeamGameInstance->GetMancheSystem()->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 B : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 B : %d"), PointsPlayers[1]);

		if (CharactersInArena.Find(pointeur) < 0) return;
		BeamGameInstance->GetMancheSystem()->SetPlayerPoints(CharactersInArena.Find(pointeur), -1);

		PointsPlayers = BeamGameInstance->GetMancheSystem()->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 A : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 A : %d"), PointsPlayers[1]);


		BeamGameInstance->GetMancheSystem()->AddManche();

		BeamGameInstance->DeployEvent();


		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Purple,
			FString::Printf(TEXT("MATCH TYPE FREE"))
		);

		// AFFICHE LE MENU DE FIN DE PARTIE (RECOMMENCE OU QUITTER)
		// Here ->
		// Appeler ResetPlayerPoints() pour remettre les points � 0

		BeamGameInstance->GetMancheSystem()->ResetPlayerPoints();
		BeamGameInstance->GetMancheSystem()->SetManche(0);

		// A enlever quand menu fin
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMatchGameMode::ResetLevel, 3.0f, false);

		return;
	}
	else if (BeamGameInstance->GetMancheSystem()->GetMatchType() == EMatchTypeID::Deathmatch) {


		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Purple,
			FString::Printf(TEXT("MATCH TYPE GAMEMODE"))
		);

		BeamGameInstance->GetMancheSystem()->ChangePointWin();

		TArray<int> PointsPlayers = BeamGameInstance->GetMancheSystem()->GetPlayersPoints();

		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 1 B : %d"), PointsPlayers[0]);
		UE_LOG(LogTemp, Error, TEXT("PLAYER POINT 2 B : %d"), PointsPlayers[1]);

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("uizahe %d %d"), PointsPlayers[0], PointsPlayers[1]));

		BeamGameInstance->GetMancheSystem()->AddManche();

		BeamGameInstance->DeployEvent();

		if (BeamGameInstance->GetMancheSystem()->IsMatchFinished())
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
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMatchGameMode::ResetLevel, 3.0f, false);
		}

	}
}

bool AMatchGameMode::GetMancheEnd() const
{
	return MancheEnd;
}

void AMatchGameMode::ResetLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

bool AMatchGameMode::IsPlayer1Win() const {return;}

void AMatchGameMode::SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints)
{
	UBeamCharacterInputData* InputData = LoadInputDataFromConfig();
	UInputMappingContext* InputMappingContext = LoadInputMappingContextFromConfig();

	uint8_t PlayerInstantiated = 0;

	TArray<EAutoReceiveInput::Type> listInputTypes = {EAutoReceiveInput::Player0 ,EAutoReceiveInput::Player1};

	std::vector<ABeamCharacter*> subCharactersInArena = {};

	for (int i = 0; i < listInputTypes.Num(); i++) {
		subCharactersInArena.push_back(nullptr);
	}

	for (AArenaPlayerStart* SpawnPoint : SpawnPoints)
	{

		if (SpawnPoint->SpawnPair != GetSelectedPair()) continue;

		

		if (listInputTypes.Num() <= 0) continue;

		EAutoReceiveInput::Type InputType = SpawnPoint->AutoReceiveInput;

		uint8_t RandomNumber = 0;


		if (listInputTypes.Num() > 0) {
			RandomNumber = FMath::RandRange(0, listInputTypes.Num()-1);
			InputType = listInputTypes[RandomNumber];
		}

		

		SpawnPoint->AutoReceiveInput = InputType;

		GEngine->AddOnScreenDebugMessage(
			-1,
			20.0f,
			FColor::Purple,
			FString::Printf(TEXT("INPUT TYPE : %d"), InputType)
		);

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


		subCharactersInArena[RandomNumber] = NewCharacter;
		//CharactersInArena.Add(NewCharacter);

		listInputTypes.RemoveAt(RandomNumber);

		PlayerInstantiated++;

	}

	for (int i = 0; i < subCharactersInArena.size(); i++) {
		CharactersInArena.Add(subCharactersInArena[i]);
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

