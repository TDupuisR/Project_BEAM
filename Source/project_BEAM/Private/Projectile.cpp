// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/BeamCharacter.h"
#include "Engine/StaticMeshActor.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	projectileMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Projectile Mesh"));
	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	projectileComponent-> InitialSpeed = 50.f;
	projectileComponent-> MaxSpeed = 50.f;
	projectileComponent->ProjectileGravityScale = 0.f;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Capsule->SetCollisionProfileName(TEXT("OverlapAll"));
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	params.AddIgnoredActor(this);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	powerParameters.Add( 0, FProjectileParameters(500.f, 50.f, 50.f, 100000.f ));
	powerParameters.Add( 1, FProjectileParameters(500.f, 100.f, 100.f, 100000.f ));
	powerParameters.Add( 2, FProjectileParameters(500.f, 150.f, 150.f, 100000.f ));
	powerParameters.Add( 3, FProjectileParameters(500.f, 200.f, 200.f, 100000.f ));
}

void AProjectile::InitialisePower(int power)
{
	ownPower = power;
	projectileCurrentParam = powerParameters[power];

	//Set here: POWER, HEIGHT, WIDTH, SPEED, SIZE OF COLLIDER
}


void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (actorParent == OverlappedComp->GetAttachParentActor()) return;
	
	if(OtherActor && OtherActor != this) //check if actor is not null
	{
		 // disable collider to detected self
		if(OtherActor->Implements<UProjectileInterface>())
		{
			IProjectileInterface* interface = Cast<IProjectileInterface>(OtherActor);
			if (interface == nullptr) return;
			
			switch (interface->ProjectileGetType())
			{
			case EProjectileType::Player:
				{
					if (!OtherComp->ComponentTags.Contains("Player")) break;
					
					if (interface->ProjectileContext(ownPower, GetActorLocation())) GetDestroyed();
					else return;
				};
			
			case EProjectileType::Bullet:
				{
					if (!canAccess) break;
					
					TObjectPtr<AProjectile> otherBullet = interface->GetProjectile();
					if (otherBullet == nullptr) break;
					
					int otherPower = otherBullet->GetPower();
					
					if (otherPower > ownPower)
					{
						int newPower = ((otherPower +1) - (ownPower +1)) -1;
						if (newPower < 0) newPower = 0;
						
						if (otherBullet != nullptr) otherBullet->FakeDestroy(newPower);
						GetDestroyed();
					}
					else if (otherPower < ownPower)
					{
						int newPower = ((ownPower +1) - (otherPower +1)) -1;
						if (newPower < 0) newPower = 0;

						if (otherBullet != nullptr) otherBullet->GetDestroyed();
						FakeDestroy(newPower);
					}
					else
					{
						if (otherBullet != nullptr) otherBullet->GetDestroyed();
						GetDestroyed();
					}
				};

			case EProjectileType::DestructWall:
				{
					if (interface->ProjectileContext(ownPower, GetActorLocation())) GetDestroyed();
					else break;
				};
			}
		}
		else
		{
			GetDestroyed();
		}
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


int AProjectile::GetPower()
{
	return ownPower;
}

EProjectileType AProjectile::ProjectileGetType()
{
	return EProjectileType::Bullet;
}
AProjectile* AProjectile::GetProjectile()
{
	canAccess = false;
	return this;
}
bool AProjectile::ProjectileContext(int power, FVector position) // Should not be called in any circumstances
{
	return false;
}

void AProjectile::GetDestroyed() // Destroy the projectile
{
	// Call an Explosion effect
	this->Destroy();
}
void AProjectile::FakeDestroy(int power) // Produce a destruction effect and reset the projectile parameters, does not destroy the Actor
{
	// Call an Explosion effect
	InitialisePower(power);
}


