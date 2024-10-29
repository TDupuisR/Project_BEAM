// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateIdle.h"

#include "Characters/BeamCharacter.h"	
#include "Characters/BeamCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


EBeamCharacterStateID UBeamCharacterStateIdle::GetStateID()
{
	return EBeamCharacterStateID::Idle;
}

void UBeamCharacterStateIdle::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Enter State %d"), GetStateID())
	);
}

void UBeamCharacterStateIdle::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Exit State %d"), GetStateID())
	);
}

void UBeamCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Red,
		FString::Printf(TEXT("Tick State %d"), GetStateID())
	);

	if (Character->GetInputJump()) {
		StateMachine->ChangeState(EBeamCharacterStateID::Jump);
		return;
	}
	
	if (Character->GetInputMove() != FVector2D::ZeroVector)
	{

		GEngine->AddOnScreenDebugMessage(
			-1,
			0.1f,
			FColor::Red,
			FString::Printf(TEXT("Pressed"), GetStateID())
		);

		StateMachine->ChangeState(EBeamCharacterStateID::Walk);
	}

	if (!Character->GetMovementComponent()->IsMovingOnGround()) {
		StateMachine->ChangeState(EBeamCharacterStateID::Fall);
	}

	if (Character->GetInputFly()) {
		StateMachine->ChangeState(EBeamCharacterStateID::Fly);
	}

}
