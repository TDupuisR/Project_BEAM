// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BeamCharacter.h"

#include "Characters/BeamCharacterStateMachine.h"

// Sets default values
ABeamCharacter::ABeamCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeamCharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateStateMachine();
	InitStateMachine();
	
}

// Called every frame
void ABeamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TickStateMachine(DeltaTime);


}

// Called to bind functionality to input
void ABeamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABeamCharacter::CreateStateMachine()
{
	StateMachine = NewObject<UBeamCharacterStateMachine>(this);
}

void ABeamCharacter::InitStateMachine()
{
	if (StateMachine == nullptr) return;
	StateMachine->Init(this);
}

void ABeamCharacter::TickStateMachine(float DeltaTime) const
{
	if (StateMachine == nullptr) return;
	StateMachine->Tick(DeltaTime);
}

