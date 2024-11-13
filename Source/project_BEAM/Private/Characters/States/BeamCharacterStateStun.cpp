// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateStun.h"
#include "Characters/BeamCharacter.h"	
#include "Characters/BeamCharacterStateMachine.h"

EBeamCharacterStateID UBeamCharacterStateStun::GetStateID()
{
	return EBeamCharacterStateID::Stun;
}

void UBeamCharacterStateStun::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	timeToStun = Character->GetStunTime();
}

void UBeamCharacterStateStun::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
}

void UBeamCharacterStateStun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	stunTimer += DeltaTime;

	if (stunTimer >= timeToStun) {
		stunTimer = 0.f;
		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
	}

}
