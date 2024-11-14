// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateProjection.h"
#include "Characters/BeamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BeamCharacterStateMachine.h"
#include "Characters/BeamCharacterSettings.h"


EBeamCharacterStateID UBeamCharacterStateProjection::GetStateID()
{
	return EBeamCharacterStateID::Projection;
}

void UBeamCharacterStateProjection::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Character->SetCanTakeDamage(false);
	TimeToWait = Character->GetCharacterSettings()->TimeToWaitAfterProjection;
	Timer = 0.f;
}

void UBeamCharacterStateProjection::StateExit(EBeamCharacterStateID NextStateID)
{
	Character->SetCanTakeDamage(true);
	Character->SetCanTakeKnockback(true);

}

void UBeamCharacterStateProjection::StateTick(float DeltaTime)
{

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Red,
		FString::Printf(TEXT("Tick State PROJECTION"))
	);

	if (AfterProjection) {
		Timer += DeltaTime;
		if (Timer >= TimeToWait) {

			AfterProjection = false;
			Timer = 0.f;
			StateMachine->ChangeState(EBeamCharacterStateID::Idle);
		}
	}

	if (Character->GetCharacterMovement()->IsMovingOnGround() && Character->GetCharacterMovement()->GetLastUpdateVelocity().Size() <= Character->GetMinSizeVelocity()) 
	{
		AfterProjection = true;
		Character->SetCanTakeKnockback(false);
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.f,
			FColor::Purple,
			FString::Printf(TEXT("You know the doo scooby doo"))
		);
	}

}
