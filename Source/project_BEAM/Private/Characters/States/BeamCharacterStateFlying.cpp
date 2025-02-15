// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateFlying.h"

#include "Characters/BeamCharacter.h"	
#include "Characters/BeamCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BeamCharacterSettings.h"



EBeamCharacterStateID UBeamCharacterStateFlying::GetStateID()
{
	return EBeamCharacterStateID::Fly;
}

void UBeamCharacterStateFlying::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	firstFrame = true;

	Character->GetCharacterMovement()->BrakingFrictionFactor = Character->GetCharacterSettings()->Fly_BrakingFrictionFactor;

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Enter State %d"), GetStateID())
	);

	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UBeamCharacterStateFlying::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	Character->GetCharacterMovement()->BrakingFrictionFactor = Character->GetCharacterSettings()->BrakingFrictionFactor;

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Exit State %d"), GetStateID())
	);

	firstFrame = true;
}

void UBeamCharacterStateFlying::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	if (Character->GetInputPush() && Character->CanPush()) {
		StateMachine->ChangeState(EBeamCharacterStateID::Push);
	}

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Red,
		FString::Printf(TEXT("Tick State %d"), GetStateID())
	);

	if (!canDash) {
		timerDash += DeltaTime;
		if (timerDash >= Character->GetCharacterSettings()->Fly_DashTimer) {
			canDash = true;
			timerDash = 0;
		}
	}

	if (!canMove) {
		timerInputs += DeltaTime;
		if (timerInputs >= Character->GetCharacterSettings()->Fly_InputsTimer) {
			canMove = true;
			timerInputs = 0;
		}
	}

	if (Character->GetInputFly() && !firstFrame) {
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		//Character->GetCapsuleComponent()->SetSimulatePhysics(true);
		//Character->GetCharacterMovement()->Gravity = true;

		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
		return;
	}

	// Dash
	if (Character->GetInputDash() && !dashIsStillActive && canDash) {

		dashIsStillActive = true;
		canDash = false;
		canMove = false;

		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Blue,
			FString::Printf(TEXT("Dash %d"), GetStateID())
		);
		
		FVector dashVector = FVector::ZeroVector;
		if (Character->GetInputMove() != FVector2D::ZeroVector)
		{
			dashVector = FVector(Character->GetInputMove().X,0,Character->GetInputMove().Y);
		}


		Character->GetCharacterMovement()->AddImpulse(dashVector * Character->GetCharacterSettings()->Fly_DashForce);
	}
	else if (!Character->GetInputDash())
	{
		dashIsStillActive = false;
	}

	if (canMove) {
		Character->SetOrientX(Character->GetInputMove().X);
	
		if (Character->GetInputMove() != FVector2D::ZeroVector)
		{
			FVector moveVector = FVector(Character->GetInputMove().X,0,Character->GetInputMove().Y);
			moveVector.Normalize();
			Character->AddMovementInput(moveVector, Character->GetInputMove().Length());
		}
	}

	if (firstFrame) {
		firstFrame = false;
	}
}

//void UBeamCharacterStateFlying::AfterDash()
//{
//	canDash = true;
//	canMove = true;
//}
