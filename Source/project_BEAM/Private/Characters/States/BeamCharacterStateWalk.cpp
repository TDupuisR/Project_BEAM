// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateWalk.h"

EBeamCharacterStateID UBeamCharacterStateWalk::GetStateID()
{
	return EBeamCharacterStateID::Walk;
}

void UBeamCharacterStateWalk::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Enter State %d"), GetStateID())
	);
}

void UBeamCharacterStateWalk::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Exit State %d"), GetStateID())
	);
}

void UBeamCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Tick State %d"), GetStateID())
	);



}
