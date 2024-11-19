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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void InitCharacter(ABeamCharacter* playerCharacter);
	UFUNCTION()
	void InitWeapon(UWeaponCharge* playerWeapon);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABeamCharacter* Character;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponCharge> Weapon;

	UFUNCTION()
	void ShotCall(int power);
	
	UFUNCTION(BlueprintCallable)
	bool GetIsActive() const;
	
protected:
	// Called when the game starts
	
	UFUNCTION(BlueprintCallable)
	FVector AimCursorPos(const FVector2D& dir, const FVector& playerPos);
	UFUNCTION(BlueprintCallable)
	void Shoot(FVector spawnLocation, FVector2D direction, AActor* playerActor, int power);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> ProjectileActor;
	UPROPERTY(BlueprintReadOnly)
	FVector aimPos;
	
private:
	UPROPERTY(EditAnywhere)
	float shootDelay = 0.f;
	UPROPERTY(EditAnywhere)
	float shootDelayInit = 3.f;

	UPROPERTY()
	bool wasShootTriggered = false;
	
};
