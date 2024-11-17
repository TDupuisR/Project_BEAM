// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponCharge.generated.h"

class ABeamCharacter;
class UPlayerAim;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_BEAM_API UWeaponCharge : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponCharge();

	UFUNCTION(BlueprintCallable)
	void StartWeaponCharge();
	UFUNCTION(BlueprintCallable)
	void CancelWeaponCharge();
	UFUNCTION(BlueprintCallable)
	void InitValues();
	
	UFUNCTION()
	void InitCharacter(ABeamCharacter* playerCharacter);
	UFUNCTION()
	void InitAim(UPlayerAim* playerAim);

	bool GetIsQteActive() const;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABeamCharacter> Character;
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UPlayerAim> pointAim;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float qteMaxTime = 5.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float qteFinaleDelay = 3.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<float> qteTimeStamp = {2.f, 1.5f, 1.f};
	
private:
	UPROPERTY()
	bool isQteActive = false;
	UPROPERTY()
	bool chargeWasPushed = false;
	UPROPERTY()
	float qteTimeLeft;
	UPROPERTY()
	int power = 0;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
