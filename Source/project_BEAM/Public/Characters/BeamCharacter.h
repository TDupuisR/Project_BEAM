// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "BeamCharacterInputdata.h"
#include "InputMappingContext.h"
#include "ProjectileInterface.h"
#include "GameFramework/Character.h"


#include "BeamCharacter.generated.h"

class UBeamCharacterStateMachine;
class UBeamCharacterSettings;
class UBoxComponent;
class UPlayerAim;

UCLASS()
class PROJECT_BEAM_API ABeamCharacter : public ACharacter, public IProjectileInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABeamCharacter();
	virtual EProjectileType ProjectileGetType() override;
	virtual void ProjectileContext(int power, FVector position) override;
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
	float GetOrientX() const;

	void SetOrientX(float NewOrientX);

protected:
	UPROPERTY(BlueprintReadOnly)
	float OrientX = 1.f;

	void RotateMeshUsingOrientX() const;

#pragma endregion


# pragma region State Machine

public: 
	void CreateStateMachine();

	void InitStateMachine();

	void TickStateMachine(float DeltaTime) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBeamCharacterStateMachine> StateMachine;


# pragma endregion

# pragma region Character Settings

public:
	void InitCharacterSettings();

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

	UPROPERTY()
	APlayerController* playerController;

	FVector2D GetInputMove() const;
	bool GetInputJump() const;
	bool GetInputDash() const;

	bool GetInputCharge() const;
	FVector2D GetInputAim() const;
	bool GetInputShoot() const;

	bool GetInputPunch() const;

	bool GetInputFly() const;
	
protected:
	void SetupMappingContextIntoController();

	UPROPERTY() FVector2D InputMove = FVector2D::ZeroVector;
	UPROPERTY() bool InputJump = false;
	UPROPERTY() bool InputDash = false;

	UPROPERTY() bool InputCharge = false;
	UPROPERTY() FVector2D InputAim = FVector2D::ZeroVector;
	UPROPERTY() bool InputShoot = false;

	UPROPERTY() bool InputPunch = false;

	UPROPERTY() bool InputFly = false;

private:
	void BindInputActions(UEnhancedInputComponent* EnhancedInputComponent);

	void OnInputMove(const FInputActionValue& InputActionValue);
	void OnInputJump(const FInputActionValue& InputActionValue);
	void OnInputDash(const FInputActionValue& InputActionValue);
	
	void OnInputCharge(const FInputActionValue& InputActionValue);
	void OnInputAim(const FInputActionValue& InputActionValue);
	void OnInputShoot(const FInputActionValue& InputActionValue);
	
	void OnInputPunch(const FInputActionValue& InputActionValue);

	void OnInputFly(const FInputActionValue& InputActionValue);
	
# pragma endregion

# pragma region Fight

public:
	UFUNCTION(BlueprintCallable)
	void KnockBack(FVector Direction, float Force);


# pragma endregion

# pragma region Life

	// GETTERS
	int const GetLife() const;

	int const GetMaxLife() const;

	int const GetLifeToFly() const;


	// SETTERS
	void SetLife(const int NewLife);

	void const SetMaxLife(const int NewMaxLife);

	void const SetLifeToFly(const int NewLifeToFly);


	// OTHERS
	void TakeDamage(const int Damage = 1);

	void const ResetLife();

	bool IsPhaseTwo() const;

protected:

	void CheckLife();

	

	UPROPERTY(BlueprintReadOnly)
	int Life;

	UPROPERTY(BlueprintReadOnly)
	int MaxLife;

	UPROPERTY(BlueprintReadOnly)
	int LifeToFly;

# pragma endregion

# pragma region Punch

public:
	void Push();

	bool CanPush() const;

	void SetCanPush(bool NewCanPush);

private:
	UPROPERTY()
	UBoxComponent* boxCollision;

	UPROPERTY()
	TArray<ABeamCharacter*> PlayersInZone;

	UPROPERTY()
	bool canPush = true;

	UPROPERTY()
	float timerPush = 0.0f;

	UPROPERTY()
	float timeToWaitPush = 2.0f;

	void TickPush(float DeltaTime);

	void SetupCollision();

	UFUNCTION()
	void OnBeginOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapZone(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


# pragma endregion


#pragma region playerAim

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerAim> localPlayerAim;
	
private:
	UFUNCTION()
	void creatAim();
	
	UFUNCTION()
	void playerAimInit();

	
#pragma endregion
};
