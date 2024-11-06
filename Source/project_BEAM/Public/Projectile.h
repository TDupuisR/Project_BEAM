// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "ProjectileInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FProjectileParameters

{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float speed = 100.f;
	UPROPERTY(EditAnywhere)
	float width = 100.f;
	UPROPERTY(EditAnywhere)
	float height = 100.f;
	UPROPERTY(EditAnywhere)
	float lifeSpan = 100000.f;
};


UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Projectile"))
class PROJECT_BEAM_API AProjectile : public AActor, public IProjectileInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
	UFUNCTION()
	void InitialisePower(int power);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float height;
	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere)
	UStaticMesh* projectileMesh;

	UPROPERTY()
	AActor* actorParent;
	
	virtual EProjectileType ProjectileGetType() override;
	virtual AProjectile* GetProjectile() override;
	virtual bool ProjectileContext(int power, FVector position) override;

	UFUNCTION(BlueprintCallable)
	int GetPower();
	UFUNCTION(BlueprintCallable)
	void GetDestroyed();
	UFUNCTION(BlueprintCallable)
	void FakeDestroy(int power);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	FCollisionQueryParams params;
	
	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* projectileComponent;
	
	UPROPERTY(Config, EditAnywhere, Category="Power Parameters") 
	TMap<int, FProjectileParameters> powerParameters;
	UPROPERTY()
	FProjectileParameters projectileCurrentParam;
	
	UPROPERTY(EditAnywhere)
	FHitResult projectileHitResult;

private:
	UPROPERTY()
	bool canAccess = true;
	UPROPERTY()
	int ownPower;
	
};
