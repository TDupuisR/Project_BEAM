// Fill out your copyright notice in the Description page of Project Settings.


#include "WeapongCharge.h"
#include "Engine/World.h"

#include "MaterialHLSLTree.h"


// Sets default values for this component's properties
UWeapongCharge::UWeapongCharge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapongCharge::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeapongCharge::onWayponCharge()
{
	int power = 0;
	while(!isQteActive) // remplace par le timer
	{
		if( && power < 3)
		{
			power++;
			qteTimeLeft = qteReset;
		}
		else if(power <= 3)
		{
			//wait for x sec
			//shoot();
			return;
		}
		if(chargeFail == true)
		{
			//shoot();
			return;
		}
		qteTimeLeft -= GetWorld()->DeltaTimeSeconds;
		//whait for delta time
	}
}


// Called every frame
void UWeapongCharge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

