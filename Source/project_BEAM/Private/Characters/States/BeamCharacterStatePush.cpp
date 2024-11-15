// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStatePush.h"

#include "Characters/BeamCharacterStateMachine.h"
#include "Characters/BeamCharacter.h"
#include "Characters/BeamCharacterSettings.h"
#include "GameFramework/CharacterMovementComponent.h"


EBeamCharacterStateID UBeamCharacterStatePush::GetStateID()
{
	return EBeamCharacterStateID::Push;
}

void UBeamCharacterStatePush::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	timeToWait = Character->GetCharacterSettings()->Push_WaitTime;
	timerPush = 0.0f;

	Character->Push();

	Character->SetCanPush(false);

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UBeamCharacterStatePush::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);


	if (!Character->IsPhaseTwo()) {
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else {
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}


}

void UBeamCharacterStatePush::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	timerPush += DeltaTime;

	if (timerPush >= timeToWait) {
		if (Character->IsPhaseTwo()) {
			StateMachine->ChangeState(EBeamCharacterStateID::Fly);
		}
		else {
			StateMachine->ChangeState(EBeamCharacterStateID::Idle);
		}
	}
}
