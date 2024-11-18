// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCharge.h"
#include "Engine/World.h"
#include "Characters/BeamCharacter.h"
#include "Characters/PlayerAim.h"


// Sets default values for this component's properties
UWeaponCharge::UWeaponCharge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponCharge::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponCharge::StartWeaponCharge()
{
	power = 0;
	qteTimeLeft = 5.0f;
	chargeWasPushed = false;
	isQteActive = true;

	Character->DisplayQte_Implementation();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("QTE start")));
}
void UWeaponCharge::CancelWeaponCharge(bool isFail)
{
	isQteActive = false;
	pointAim->ShotCall(power);
	OnFailEvent.Broadcast();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("QTE cancel")));
}

void UWeaponCharge::InitCharacter(ABeamCharacter* playerCharacter)
{
	Character = playerCharacter;
}

void UWeaponCharge::InitAim(UPlayerAim* playerAim)
{
	pointAim = playerAim;
}

bool UWeaponCharge::GetIsQteActive() const
{
	return isQteActive;
}

float UWeaponCharge::GetQteTimeLeft() const
{
	return qteTimeLeft;
}

float UWeaponCharge::GetQteMaxTime() const
{
	return qteMaxTime;
}

float UWeaponCharge::GetQteTimeStamp() const
{;
	if (power < 0 || power > 2) return .0f;
	else return qteTimeStamp[power];
}


// Called every frame
void UWeaponCharge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isQteActive) // enter the QTE condition
	{
		if(qteTimeLeft >= .0f)
		{
			if (Character->GetInputCharge() && !chargeWasPushed && power < 3)
			{
				chargeWasPushed = true;
				
				if (qteTimeLeft <= qteTimeStamp[power]) // if QTE success
				{
					power++;
					qteTimeLeft = qteMaxTime;
					
					GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("QTE success to power: %d "), power));
					//PlayAnimQTE()
					OnSucceedEvent.Broadcast();
				}
				else // if QTE Fail
				{
					CancelWeaponCharge(true);
				}
			}
			else if (!Character->GetInputCharge() && chargeWasPushed && power < 3)
			{
				chargeWasPushed = false;
			}

			if(power >= 3 && chargeWasPushed)
			{
				qteTimeLeft = qteFinaleDelay;
				chargeWasPushed = false;
			}
			
			qteTimeLeft -= GetWorld()->DeltaTimeSeconds;
		}
		else // Time over
		{
			CancelWeaponCharge(false);
		}
	}
}
