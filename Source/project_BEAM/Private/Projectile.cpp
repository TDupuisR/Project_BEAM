// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("Projectile Mesh"));
	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	projectileComponent-> InitialSpeed = 50.f;
	projectileComponent-> MaxSpeed = 50.f;
	projectileComponent->ProjectileGravityScale = 0.f;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Capsule->SetCollisionProfileName(TEXT("OverlapAll"));
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	powerParameters.Add( 0, FProjectileParameters(500.f, 50.f, 50.f, 5.f ));
	powerParameters.Add( 1, FProjectileParameters(500.f, 100.f, 100.f, 5.f ));
	powerParameters.Add( 2, FProjectileParameters(500.f, 150.f, 150.f, 5.f ));
	powerParameters.Add( 3, FProjectileParameters(500.f, 200.f, 200.f, 5.f ));
	
}

void AProjectile::InitialisePower(int power)
{
	ownPower = power;
	projectileCurrentParam = powerParameters[power];
}


void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this) //check if actor is not null
	{
		params.AddIgnoredActor(this); // disable collider to detected self
		if(OtherActor->Implements<IProjectileInterface>())
		{
			IProjectileInterface* interface = Cast<IProjectileInterface>(OtherActor);
			EProjectileType type = interface->ProjectileGetType();
			switch (type)
			{
			case EProjectileType::Player:
				//case player
					return;
			case EProjectileType::Bullet:
				//case bullet
					return;
			case EProjectileType::DestructWall:
				//case block
				return;
			}
		}
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EProjectileType AProjectile::ProjectileGetType()
{
	return EProjectileType::Bullet;
}
AProjectile& AProjectile::GetProjectile()
{
	canAccess = false;
	return *this;
}

