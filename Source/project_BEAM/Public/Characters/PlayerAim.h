// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponCharge.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

#include "PlayerAim.generated.h"

class ABeamCharacter;
class AProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_BEAM_API UPlayerAim : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerAim();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 100.f;

	UFUNCTION()
	void InitCharacter(ABeamCharacter* playerCharacter);
	UFUNCTION()
	void initWeapon(UWeaponCharge* playerweapon);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABeamCharacter* Character;
	UPROPERTY()
	TObjectPtr<UWeaponCharge> Weapon;
	
	void ShotCall(int power);
	
	
protected:
	// Called when the game starts
	
	UFUNCTION(BlueprintCallable)
	FVector AimCursorPos(const FVector2D& dir, const FVector& playerPos);
	UFUNCTION(BlueprintCallable)
	void Shoot(FVector spawnLocation, FVector2D direction, AActor* playerActor, int power);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileActor;
	UPROPERTY()
	FVector aimPos;

public:


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY(EditAnywhere)
	float shootDelay = 2.f;
	UPROPERTY(EditAnywhere)
	float shootDelayInit = 2.f;

	UPROPERTY()
	bool wasShootTriggered = false;
	
};
