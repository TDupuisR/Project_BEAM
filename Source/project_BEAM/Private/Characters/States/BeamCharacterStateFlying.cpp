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
}

void UBeamCharacterStateFlying::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Red,
		FString::Printf(TEXT("Tick State %d"), GetStateID())
	);


	if (IsKeyDown(EKeys::SpaceBar) || Character->GetInputJump()) {
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		//Character->GetCapsuleComponent()->SetSimulatePhysics(true);
		//Character->GetCharacterMovement()->Gravity = true;

		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
		return;
	}

	// Dash
	if ((IsKeyWasPressed(EKeys::J) || Character->GetInputDash()) && !dashIsStillActive) {

		dashIsStillActive = true;
		
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
		else
		{
			if (IsKeyDown(EKeys::Q)) {
				dashVector += -FVector::ForwardVector;
			}
			if (IsKeyDown(EKeys::D)) {
				dashVector += FVector::ForwardVector;
			}
			if (IsKeyDown(EKeys::S)) {
				dashVector += -FVector::UpVector;
			}
			if (IsKeyDown(EKeys::Z)) {
				dashVector += FVector::UpVector;
			}
		}

		Character->GetCharacterMovement()->AddImpulse(dashVector * Character->GetCharacterSettings()->Fly_DashForce);
	}
	else if (!Character->GetInputDash())
	{
		dashIsStillActive = false;
	}

	// Set Orientation
	if ((IsKeyDown(EKeys::Q) || Character->GetInputMove().X < 0) && Character->GetOrientX() == 1)
	{
		Character->SetOrientX(-1);
	}
	else if ((IsKeyDown(EKeys::D) || Character->GetInputMove().X > 0) && Character->GetOrientX() == -1)
	{
		Character->SetOrientX(1);
	}
	
	// Apply Movement
	if (Character->GetInputMove() != FVector2D::ZeroVector)
	{
		FVector moveVector = FVector(Character->GetInputMove().X,0,Character->GetInputMove().Y);
		moveVector.Normalize();
		Character->AddMovementInput(moveVector, Character->GetInputMove().Length());
	}
	// BrakingFrictionFactor (base : 40, fly : 10 pour movement moins arr�t�s)
	else
	{
		if (IsKeyDown(EKeys::Q)){
			Character->AddMovementInput(-FVector::ForwardVector);
		}
		else if (IsKeyDown(EKeys::D)){
			Character->AddMovementInput(FVector::ForwardVector);
		}
		
		if (IsKeyDown(EKeys::S)) {
			Character->AddMovementInput(-FVector::UpVector);
		}
		else if (IsKeyDown(EKeys::Z)) {
			Character->AddMovementInput(FVector::UpVector);
		}
	}
}
