// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "BeamCharacterInputdata.h"
#include "InputMappingContext.h"
#include "ProjectileInterface.h"
#include "Camera/CameraFollowTarget.h"
#include "GameFramework/Character.h"


#include "BeamCharacter.generated.h"

class UBeamCharacterStateMachine;
class UBeamCharacterSettings;
class UEnhancedInputComponent;
class UBoxComponent;
class UPlayerAim;

UCLASS()
class PROJECT_BEAM_API ABeamCharacter : public ACharacter, , public IProjectileInterface, public ICameraFollowTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABeamCharacter();
	virtual EProjectileType ProjectileGetType() override;
	virtual bool ProjectileContext(int power, FVector position) override;
	virtual AProjectile* GetProjectile() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector StartLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Orient

public:
	UFUNCTION()
	float GetOrientX() const;
	UFUNCTION()
	void SetOrientX(float NewOrientX);

protected:
	UPROPERTY(BlueprintReadOnly)
	float OrientX = 1.f;
	UFUNCTION()
	void RotateMeshUsingOrientX() const;

#pragma endregion


# pragma region State Machine

public: 
	UFUNCTION()
	void CreateStateMachine();
	UFUNCTION()
	void InitStateMachine();
	UFUNCTION()
	void TickStateMachine(float DeltaTime) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBeamCharacterStateMachine> StateMachine;


# pragma endregion

# pragma region Character Settings

public:
	UFUNCTION()
	void InitCharacterSettings();

	UFUNCTION(BlueprintCallable)
	void ReattributeCharacterSettings();

	const UBeamCharacterSettings* GetCharacterSettings() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	const UBeamCharacterSettings* CharacterSettings;

# pragma endregion

# pragma region Character Input

public:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<UBeamCharacterInputData> InputData;

	UFUNCTION() FVector2D GetInputMove() const;
	UFUNCTION() bool GetInputJump() const;
	UFUNCTION() bool GetInputDash() const;

	UFUNCTION() bool GetInputCharge() const;
	UFUNCTION() FVector2D GetInputAim() const;
	UFUNCTION() bool GetInputShoot() const;

	UFUNCTION() bool GetInputPush() const;

	UFUNCTION() bool GetInputFly() const;

protected:
	UFUNCTION()
	void SetupMappingContextIntoController() const;

	UPROPERTY() FVector2D InputMove = FVector2D::ZeroVector;
	UPROPERTY() bool InputJump = false;
	UPROPERTY() bool InputDash = false;

	UPROPERTY() bool InputCharge = false;
	UPROPERTY() FVector2D InputAim = FVector2D::ZeroVector;
	UPROPERTY() bool InputShoot = false;

	UPROPERTY() bool InputPush = false;

	UPROPERTY() bool InputFly = false;

private:
	UFUNCTION()
	void BindInputActions(UEnhancedInputComponent* EnhancedInputComponent);

	UFUNCTION() void OnInputMove(const FInputActionValue& InputActionValue);
	UFUNCTION() void OnInputJump(const FInputActionValue& InputActionValue);
	UFUNCTION() void OnInputDash(const FInputActionValue& InputActionValue);

	UFUNCTION() void OnInputCharge(const FInputActionValue& InputActionValue);
	UFUNCTION() void OnInputAim(const FInputActionValue& InputActionValue);
	UFUNCTION() void OnInputShoot(const FInputActionValue& InputActionValue);

	UFUNCTION() void OnInputPush(const FInputActionValue& InputActionValue);

	UFUNCTION() void OnInputFly(const FInputActionValue& InputActionValue);

# pragma endregion

# pragma region Fight

public:
	UFUNCTION(BlueprintCallable)
	void KnockBack(FVector Direction, float Force);

	UFUNCTION(BlueprintCallable)
	void Bounce(FVector Normal);

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent,  // The component that was hit
		AActor* OtherActor,                // The other actor involved in the hit
		UPrimitiveComponent* OtherComp,    // The other actor's component that was hit
		FVector NormalImpulse,             // The force applied to resolve the collision
		const FHitResult& Hit              // Detailed information about the hit)
	);

	UFUNCTION(BlueprintCallable)
	float GetBounciness() const;

	UFUNCTION(BlueprintCallable)
	float GetMinSizeVelocity() const;

	UFUNCTION(BlueprintCallable)
	bool GetCanTakeDamage() const;

	UFUNCTION(BlueprintCallable)
	void SetCanTakeDamage(bool NewCanTakeDamage);

	UFUNCTION(BlueprintCallable)
	bool GetCanTakeKnockback();

	UFUNCTION(BlueprintCallable)
	void SetCanTakeKnockback(bool NewCanTakeKnockback);

	UFUNCTION(BlueprintCallable)
	bool GetIsDashing() const;

	UFUNCTION(BlueprintCallable)
	void SetIsDashing(bool NewIsDashing);

private:

	UPROPERTY()
	bool IsDashing = false;

	UPROPERTY()
	float Bounciness = 0.7;

	UPROPERTY()
	float MinSizeVelocity = 100;

	UPROPERTY()
	bool CanTakeDamage = true;

	UPROPERTY()
	bool CanTakeKnockBack = true;

# pragma endregion

# pragma region Life

public:
	// GETTERS
	UFUNCTION(BlueprintCallable)
	int const GetLife() const;
	UFUNCTION(BlueprintCallable)
	int const GetMaxLife() const;
	UFUNCTION(BlueprintCallable)
	int const GetLifeToFly() const;


	// SETTERS
	UFUNCTION()
	void SetLife(const int NewLife);
	UFUNCTION()
	void const SetMaxLife(const int NewMaxLife);
	UFUNCTION()
	void const SetLifeToFly(const int NewLifeToFly);


	// OTHERS
	UFUNCTION()
	void TakeDamage(const int Damage = 1);
	UFUNCTION()
	void const ResetLife();
	UFUNCTION()
	bool IsPhaseTwo() const;

protected:
	UFUNCTION()
	void CheckLife();

	UPROPERTY(BlueprintReadOnly)
	int Life;
	UPROPERTY(BlueprintReadOnly)
	int MaxLife;
	UPROPERTY(BlueprintReadOnly)
	int LifeToFly;

# pragma endregion
# pragma region Push

public:
	UFUNCTION()
	void Push();
	UFUNCTION()
	bool CanPush() const;
	UFUNCTION()
	void SetCanPush(bool NewCanPush);

private:
	UPROPERTY()
	UBoxComponent* boxCollision;
	UPROPERTY()
	TArray<ABeamCharacter*> PlayersInZone;

	UPROPERTY()
	UCapsuleComponent* capsuleCollision;

	bool canPush = true;

	UPROPERTY()
	float timerPush = 0.0f;
	UPROPERTY()
	float timeToWaitPush = 2.0f;

	UFUNCTION()
	void TickPush(float DeltaTime);
	UFUNCTION()
	void SetupCollision();

	UFUNCTION()
	void OnBeginOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


# pragma endregion

# pragma region Stun

public:

	void Stun(float TimeToStun);

	float GetStunTime() const;

	void SetStunTime(float NewStunTime);

	void SetMultiplierStun(float NewMultiplierStun);

	float GetMultiplierStun();

private:

	UPROPERTY()
	float StunTime = 1.f;

	UPROPERTY()
	float MultiplierStun = 0.f;

# pragma endregion

# pragma region Player Aim

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerAim> localPlayerAim;

private:
	UFUNCTION()
	void creatAim();
	UFUNCTION()
	void playerAimInit();

#pragma endregion

#pragma region FollowTarget

	virtual bool IsFollowable() override;

	virtual FVector GetFollowPosition() override;

#pragma endregion


};
