// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BeamCharacterState.h"
#include "BeamCharacterStateProjection.generated.h"

UCLASS(ClassGroup = (BeamCharacterState), meta = (BlueprintSpawnableComponent))
class PROJECT_BEAM_API UBeamCharacterStateProjection : public UBeamCharacterState
{
	GENERATED_BODY()
	
public:
	virtual EBeamCharacterStateID GetStateID() override;

	virtual void StateEnter(EBeamCharacterStateID PreviousStateID) override;

	virtual void StateExit(EBeamCharacterStateID NextStateID) override;

	virtual void StateTick(float DeltaTime) override;


private:
	UPROPERTY() float TimeToWait = 0.4f;
	UPROPERTY() float Timer = 0.f;

	UPROPERTY() bool AfterProjection = false;

};
