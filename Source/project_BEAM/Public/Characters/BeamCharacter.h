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
	UFUNCTION()
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
	void SetupMappingContextIntoController();

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
