// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateJump.h"

#include "Characters/BeamCharacterStateMachine.h"

#include "Characters/BeamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/BeamCharacterSettings.h"



EBeamCharacterStateID UBeamCharacterStateJump::GetStateID()
{
	return EBeamCharacterStateID::Jump;
}

void UBeamCharacterStateJump::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Blue,
		FString::Printf(TEXT("Enter State %d"), GetStateID())
	);

	Character->GetCharacterMovement()->JumpZVelocity = Character->GetCharacterSettings()->Jump_Force;
	Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetCharacterSettings()->Jump_VelocityMax;

	Character->Jump();


}

void UBeamCharacterStateJump::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Blue,
		FString::Printf(TEXT("Exit State %d"), GetStateID())
	);
}

void UBeamCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Blue,
		FString::Printf(TEXT("STATE TICK JUMP"))
	);
	
	if (IsKeyDown(EKeys::Q) || IsKeyDown(EKeys::D) || Character->GetInputMove().X != 0) 
	{
	/*	if ((IsKeyDown(EKeys::Q) || Character->GetInputMove().X < 0) && Character->GetOrientX() == 1)
		{
			Character->SetOrientX(-1);
		}
		else if ((IsKeyDown(EKeys::D) || Character->GetInputMove().X > 0) && Character->GetOrientX() == -1)
		{
			Character->SetOrientX(1);
		}*/

		float appliedForce = .0f;
		if (Character->GetInputMove().X != 0)
		{
			appliedForce = Character->GetInputMove().X;
		}
		else
		{
			appliedForce = Character->GetOrientX();
		}
		
		Character->AddMovementInput(FVector::ForwardVector, appliedForce);
	}

	if (Character->GetMovementComponent()->Velocity.Y <= 0) {
		StateMachine->ChangeState(EBeamCharacterStateID::Fall);
	}
}
