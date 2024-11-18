// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerAim.h"
#include "Projectile.h"
#include "Characters/BeamCharacter.h"
#include "WeaponCharge.h"


// Sets default values for this component's properties
UPlayerAim::UPlayerAim()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UPlayerAim::InitCharacter(ABeamCharacter* playerCharacter)
{
	Character = playerCharacter;
}

void UPlayerAim::InitWeapon(UWeaponCharge* playerWeapon)
{
	if (playerWeapon == nullptr) return;
	Weapon = playerWeapon;
	Weapon->InitValues();
}

void UPlayerAim::ShotCall(int power)
{
	Shoot(aimPos, Character->GetInputAim().GetSafeNormal(), Character, power);
}

bool UPlayerAim::GetIsActive() const
{
	return wasShootTriggered;
}


FVector UPlayerAim::AimCursorPos(const FVector2D& dir, const FVector& playerPos)
{	
	FVector2D DirNormal = dir.GetSafeNormal();
	return FVector(playerPos.X + DirNormal.X * Radius, playerPos.Y, playerPos.Z - DirNormal.Y * Radius );
}

void UPlayerAim::Shoot(FVector spawnLocation, FVector2D direction, AActor* playerActor, int power)
{
	if(shootDelay <= 0.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Shot Delay good")));
		if(ProjectileActor)
		{
			FVector newDir = FVector(direction.X, .0f, -direction.Y);
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = Character->GetOwner();
			spawnParams.Instigator = Character->GetInstigator();
		
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileActor, spawnLocation, newDir.ToOrientationRotator(), spawnParams);
			if(projectile == nullptr) return;

			if (power > 3) power = 3;
			if (power < 0) power = 0;
			projectile->InitialisePower(power);
			projectile->actorParent = playerActor;
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Blue,FString::Printf(TEXT("shot")));
			Character->KnockBack(-newDir, 1000.f);
		}
	}
	shootDelay = shootDelayInit;
}

// Called every frame
void UPlayerAim::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(Character->GetInputShoot() && !wasShootTriggered) //check input and if it was recently pressed
	{
		wasShootTriggered = true;
		if(shootDelay <= 0.f) Weapon->StartWeaponCharge(); //activate qte
		
	}
	if(!Character->GetInputShoot() && wasShootTriggered) //no input enter and no recent action
	{
		wasShootTriggered = false;
		
		if (Weapon->GetIsQteActive()) Weapon->CancelWeaponCharge(); //if qte still active -> deactivate Qte
	}

	aimPos = AimCursorPos(Character->GetInputAim(), Character->GetActorLocation());
	
	if (shootDelay > .0f) shootDelay -= GetWorld()->GetDeltaSeconds();
}

