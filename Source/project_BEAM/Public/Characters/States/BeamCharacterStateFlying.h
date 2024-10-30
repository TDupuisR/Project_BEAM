// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BeamCharacterState.h"
#include "BeamCharacterStateFlying.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (BeamCharacterState), meta = (BlueprintSpawnableComponent))
class PROJECT_BEAM_API UBeamCharacterStateFlying : public UBeamCharacterState
{
	GENERATED_BODY()

public:
	virtual EBeamCharacterStateID GetStateID() override;

	virtual void StateEnter(EBeamCharacterStateID PreviousStateID) override;

	virtual void StateExit(EBeamCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;

private:
	bool dashIsStillActive = false;

	bool canDash = true;
	bool canMove = true;

	float timerDash = 0.0f;
	float timerInputs = 0.0f;

	bool firstFrame = true;

	void AfterDash();

};
