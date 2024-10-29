// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BeamCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/BeamCharacterStateMachine.h"

#include "Characters/BeamCharacterSettings.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/BeamCharacterStateID.h"


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

	Life = MaxLife;

	InitCharacterSettings();
	CreateStateMachine();
	InitStateMachine();

	StartLocation = this->GetActorLocation();

	
}

// Called every frame
void ABeamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickStateMachine(DeltaTime);
	RotateMeshUsingOrientX();

	if (GetActorLocation().Y != StartLocation.Y)
	{
		SetActorLocation(FVector(GetActorLocation().X, StartLocation.Y, GetActorLocation().Z));
	}

}

// Called to bind functionality to input
void ABeamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABeamCharacter::GetOrientX() const
{
	return OrientX;
}

void ABeamCharacter::SetOrientX(float NewOrientX)
{
	OrientX = NewOrientX;
}

void ABeamCharacter::RotateMeshUsingOrientX() const
{
	FRotator Rotation = GetMesh()->GetRelativeRotation();

	Rotation.Yaw = -90.f * OrientX;
	GetMesh()->SetRelativeRotation(Rotation);
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

void ABeamCharacter::InitCharacterSettings()
{
	CharacterSettings = GetDefault<UBeamCharacterSettings>();

	if (CharacterSettings == nullptr) return;

	GetCharacterMovement()->MaxAcceleration = CharacterSettings->MaxAcceleration;
	GetCharacterMovement()->GroundFriction = CharacterSettings->GroundFriction;
	GetCharacterMovement()->GravityScale = CharacterSettings->GravityScale;
	GetCharacterMovement()->Mass = CharacterSettings->Mass;
	GetCharacterMovement()->BrakingDecelerationWalking = CharacterSettings->BreakingDecelerationWalking;
	GetCharacterMovement()->JumpZVelocity = CharacterSettings->Jump_Force;
	GetCharacterMovement()->AirControl = CharacterSettings->AirControl;
	GetCharacterMovement()->FallingLateralFriction = CharacterSettings->FallingLateralFriction;
	GetCharacterMovement()->MaxFlySpeed = CharacterSettings->Fly_MaxSpeed;
}

const UBeamCharacterSettings* ABeamCharacter::GetCharacterSettings() const
{
	return CharacterSettings;
}

void ABeamCharacter::KnockBack(FVector Direction, float Force)
{
	this->GetCharacterMovement()->Launch(Direction * Force);
}

int const ABeamCharacter::GetLife() const
{
	return Life;
}

int const ABeamCharacter::GetMaxLife() const
{
	return MaxLife;
}

int const ABeamCharacter::GetLifeToFly() const
{
	return LifeToFly;
}

void ABeamCharacter::SetLife(const int NewLife)
{
	Life = NewLife;
}

void const ABeamCharacter::SetMaxLife(const int NewMaxLife)
{
	MaxLife = NewMaxLife;
}

void const ABeamCharacter::SetLifeToFly(const int NewLifeToFly)
{
	LifeToFly = NewLifeToFly;
}

void ABeamCharacter::TakeDamage(const int Damage)
{
	Life -= Damage;
	if (Life <= 0) {
		Life = 0;
	}
	CheckLife();
}

void const ABeamCharacter::ResetLife()
{
	Life = MaxLife;
}

void ABeamCharacter::CheckLife()
{
	if (Life > 0 && Life <= LifeToFly) {
		if (StateMachine->GetCurrentStateID() != EBeamCharacterStateID::Fly) {
			StateMachine->ChangeState(EBeamCharacterStateID::Fly);
		}
	}
	else if (Life > LifeToFly) {
		if (StateMachine->GetCurrentStateID() != EBeamCharacterStateID::Idle) {
			StateMachine->ChangeState(EBeamCharacterStateID::Idle);
		}
	}
	else {
		StateMachine->ChangeState(EBeamCharacterStateID::Dead);
	}
}

