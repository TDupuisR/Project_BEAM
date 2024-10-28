// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeapongCharge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_BEAM_API UWeapongCharge : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeapongCharge();
	UPROPERTY(EditAnywhere)
	bool isQteActive = false;
	UPROPERTY(EditAnywhere)
	bool chargeFail;
	UPROPERTY(EditAnywhere)
	float qteTimeLeft;
	UPROPERTY(EditAnywhere)
	float qteMaxTime = 5.f;
	UPROPERTY(EditAnywhere)
	float delayTime = 2.f;
	UPROPERTY(EditAnywhere)
	float qteFinaleTime = 3.f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	void onWayponCharge();
    
    UPROPERTY()
    void coroutineQteTime();
    
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
