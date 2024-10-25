// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateFall.h"

#include "Characters/BeamCharacter.h"	
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BeamCharacterStateMachine.h"


EBeamCharacterStateID UBeamCharacterStateFall::GetStateID()
{
	return EBeamCharacterStateID::Fall;
}

void UBeamCharacterStateFall::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Purple,
		FString::Printf(TEXT("ENTER FALL"), GetStateID())
	);
}

void UBeamCharacterStateFall::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Purple,
		FString::Printf(TEXT("EXIT FALL"), GetStateID())
	);
}

void UBeamCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Purple,
		FString::Printf(TEXT("TICK FALL"), GetStateID())
	);

	if (Character->GetMovementComponent()->IsMovingOnGround()) {
		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
	}

	
}
