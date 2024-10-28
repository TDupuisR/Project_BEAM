// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponCharge.h"
#include "Engine/World.h"

#include "MaterialHLSLTree.h"


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
	qteTimeLeft = qteMaxTime;
	isQteActive = true;
	chargeWasPushed = false;
}
void UWeaponCharge::CancelWeaponCharge()
{
	isQteActive = false;
}



// Called every frame
void UWeaponCharge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isQteActive)
	{
		if(qteTimeLeft > .0f) // remplace par le timer
		{
			if (true && !chargeWasPushed && power < 3) // Is Charge button == true
			{
				chargeWasPushed = true;
				
				if (qteTimeLeft <= qteTimeStamp[power]) // if QTE success
				{
					power++;
					qteTimeLeft = qteMaxTime;
					//PlayAnimQTE()
				}
				else // if QTE Fail
				{
					CancelWeaponCharge();
					//shoot(power)
				}
			}
			else if (!false && chargeWasPushed && power < 3) // Is Charge button == false
			{
				chargeWasPushed = false;
			}

			if(power >= 3 && chargeWasPushed) // if Niv3 wait for x sec and shoot
			{
				qteTimeLeft = qteFinaleDelay;
				chargeWasPushed = false;
			}
			
			qteTimeLeft -= GetWorld()->DeltaTimeSeconds;
		}
		else
		{
			CancelWeaponCharge();
			//shoot(power)
		}
	}
}

