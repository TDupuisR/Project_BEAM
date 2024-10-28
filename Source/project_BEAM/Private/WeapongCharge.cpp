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
	qteTimeLeft = qteMaxTime;
	while(qteTimeLeft > .0f) // remplace par le timer
	{
		isQteActive = true;
		if(!isQteActive && chargeFail && power < 3)
		{
			power++;
			qteTimeLeft = qteMaxTime;
		}
		else if(!isQteActive && power >= 3)
		{
			qteTimeLeft = qteFinaleTime;
			isQteActive = false;
			return;
		}
		if( && chargeFail == true) //ecoute linput 
		{
			//shoot();
			isQteActive = false;
			return;
		}
		qteTimeLeft -= GetWorld()->DeltaTimeSeconds;
		//wait for delta time
	}
	//shoot()
}

void UWeapongCharge::coroutineQteTime()
{
	//
	delayTime -= GetWorld()->DeltaTimeSeconds;
}


// Called every frame
void UWeapongCharge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	
	// ...
}

