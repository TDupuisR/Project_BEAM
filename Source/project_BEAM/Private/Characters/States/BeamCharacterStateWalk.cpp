// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/BeamCharacterStateWalk.h"

#include "Characters/BeamCharacter.h"
#include "Characters/BeamCharacterStateMachine.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/BeamCharacterSettings.h"

EBeamCharacterStateID UBeamCharacterStateWalk::GetStateID()
{
	return EBeamCharacterStateID::Walk;
}

void UBeamCharacterStateWalk::StateEnter(EBeamCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Enter State %d"), GetStateID())
	);

	Character->GetCharacterMovement()->MaxWalkSpeed = GetDefault<UBeamCharacterSettings>()->Walk_VelocityMax;

}

void UBeamCharacterStateWalk::StateExit(EBeamCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Exit State %d"), GetStateID())
	);
}

void UBeamCharacterStateWalk::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Red,
		FString::Printf(TEXT("Tick State %d"), GetStateID())
	);


	if (IsKeyDown(EKeys::SpaceBar)) {

		GEngine->AddOnScreenDebugMessage(
			-1,
			3.f,
			FColor::Red,
			FString::Printf(TEXT("Change STATE Jump"), GetStateID())
		);


		StateMachine->ChangeState(EBeamCharacterStateID::Jump);
		return;
	}

	if (!IsKeyDown(EKeys::Q) && !IsKeyDown(EKeys::D))
	{
		StateMachine->ChangeState(EBeamCharacterStateID::Idle);
	}
	else {

		if (IsKeyDown(EKeys::Q)) {
			Character->SetOrientX(-1);
		}
		else {
			Character->SetOrientX(1);
		}
		Character->AddMovementInput(FVector::ForwardVector, Character->GetOrientX());

	}


}

