// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateFlying.h"

#include "Characters/BeamCharacter.h"	
#include "Characters/BeamCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"


EBeamCharacterStateID UBeamCharacterStateFlying::GetStateID()
{
	return EBeamCharacterStateID::Fly;
}

void UBeamCharacterStateFlying::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

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


	if (IsKeyDown(EKeys::SpaceBar)) {
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		//Character->GetCapsuleComponent()->SetSimulatePhysics(true);
		//Character->GetCharacterMovement()->Gravity = true;

		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
		return;
	}


	if (IsKeyDown(EKeys::Q) || IsKeyDown(EKeys::D))
	{
		if (IsKeyDown(EKeys::Q)) {
			Character->SetOrientX(-1);
		}
		else if (IsKeyDown(EKeys::D)) {
			Character->SetOrientX(1);
		}
		Character->AddMovementInput(FVector::ForwardVector, Character->GetOrientX());
	}

	if (IsKeyDown(EKeys::S) || IsKeyDown(EKeys::Z))
	{
		if (IsKeyDown(EKeys::S)) {
			Character->AddMovementInput(FVector::DownVector);
		}
		else if (IsKeyDown(EKeys::Z)) {
			Character->AddMovementInput(FVector::UpVector);
		}
	}
}
