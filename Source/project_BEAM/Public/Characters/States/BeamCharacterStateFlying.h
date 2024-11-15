// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BeamCharacterState.h"
#include "BeamCharacterStateFlying.generated.h"


UCLASS(ClassGroup = (BeamCharacterState), meta = (BlueprintSpawnableComponent))
class PROJECT_BEAM_API UBeamCharacterStateFlying : public UBeamCharacterState
{
	GENERATED_BODY()

public:
	virtual EBeamCharacterStateID GetStateID() override;

	virtual void StateEnter(EBeamCharacterStateID PreviousStateID) override;

	virtual void StateExit(EBeamCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;

	virtual void RedoParams() override;

private:
	UPROPERTY() bool dashIsStillActive = false;

	UPROPERTY() bool canDash = true;
	UPROPERTY() bool canMove = true;

	UPROPERTY() float timerDash = 0.0f;
	UPROPERTY() float timerInputs = 0.0f;

	UPROPERTY() bool firstFrame = true;

	//UFUNCTION() void AfterDash();

};
