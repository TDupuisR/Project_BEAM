// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateProjection.h"
#include "Characters/BeamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BeamCharacterStateMachine.h"


EBeamCharacterStateID UBeamCharacterStateProjection::GetStateID()
{
	return EBeamCharacterStateID::Projection;
}

void UBeamCharacterStateProjection::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Character->SetCanTakeDamage(false);
}

void UBeamCharacterStateProjection::StateExit(EBeamCharacterStateID NextStateID)
{
	Character->SetCanTakeDamage(true);
}

void UBeamCharacterStateProjection::StateTick(float DeltaTime)
{

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Red,
		FString::Printf(TEXT("Tick State PROJECTION"))
	);


	if (Character->GetCharacterMovement()->IsMovingOnGround() && Character->GetCharacterMovement()->GetLastUpdateVelocity().Size() <= Character->GetMinSizeVelocity()) 
	{
		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
	}

}
