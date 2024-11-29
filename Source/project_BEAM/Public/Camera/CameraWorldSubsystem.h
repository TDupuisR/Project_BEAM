// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <Arena/ArenaCamera.h>
#include "CameraMode.h"
#include "CameraFollowMode.h"

#include "CameraWorldSubsystem.generated.h"


class UObject;
class UCameraComponent;


/**
 * 
 */
UCLASS()
class PROJECT_BEAM_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public: 
	virtual void PostInitialize() override;

	virtual void OnWorldBeginPlay(UWorld& World) override;
	
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override { return TStatId(); };

	void AddFollowTarget(UObject* FollowTarget);

	void RemoveFollowTarget(UObject* FollowTarget);

	void TickUpdateCameraZoom(float DeltaTime);

protected:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;

	UPROPERTY()
	TObjectPtr<AArenaCamera> ArenaCamera;

	UPROPERTY()
	TArray<UObject*> FollowTargets;

	void TickUpdateCameraPosition(float DeltaTime);

	FVector CalculateAveragePositionBetweenTargets();

	float CalculateGreatestDistanceBetweenTargets();

	UCameraComponent* FindCameraByTag(const FName& Tag) const;

#pragma region Bounds

protected:
	UPROPERTY()
	FVector2D CameraBoundsMin;

	UPROPERTY()
	FVector2D CameraBoundsMax;

	UPROPERTY()
	FVector Origin;

	UPROPERTY()
	float CameraBoundsYProjectionCenter;

	AActor* FindCameraBoundsActor();

	void InitCameraBounds(AActor* CameraBoundsActor);

	void ClampPositionIntoCameraBounds(FVector& Position);

	void GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax);

	FVector CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition);


#pragma endregion

#pragma region Zoom

protected:
	UPROPERTY()
	float CameraZoomYMin = 0.f;

	UPROPERTY()
	float CameraZoomYMax = 0.f;

	UPROPERTY()
	float CameraZoomDistanceBetweenTargetsMin = 300.f;

	UPROPERTY()
	float CameraZoomDistanceBetweenTargetsMax = 700.f;

	UFUNCTION()
	void InitCameraZoomParameters();


#pragma endregion

#pragma region CamereMode

public:

	/// GETTERS

	UFUNCTION(BlueprintCallable)
	float GetCameraSpeed() const {return cameraSpeed;}

	UFUNCTION(BlueprintCallable)
	float GetShakeForce() const {return shakeForce;}
	
	UFUNCTION(BlueprintCallable)
	ECameraMode GetCameraMode() const {return cameraMode;}

	UFUNCTION(BlueprintCallable)
	ECameraFollowMode GetCameraFollowMode() const {return cameraFollowMode;}

	UFUNCTION(BlueprintCallable)
	FVector GetPosToFollow() const {return posToFollow;}

	UFUNCTION(BlueprintCallable)
	bool GetIsShaking() const {return isShaking;}

	// SETTERS

	UFUNCTION(BlueprintCallable)
	void SetShakeForce(float NewShakeForce) {shakeForce = NewShakeForce;}

	UFUNCTION(BlueprintCallable)
	void SetCameraSpeed(float NewCameraSpeed) {cameraSpeed = NewCameraSpeed;}

	UFUNCTION(BlueprintCallable)
	void ChangeCameraMode(ECameraMode NewCameraMode) {cameraMode = NewCameraMode;}

	UFUNCTION(BlueprintCallable)
	void ChangeCameraFollowMode(ECameraFollowMode NewCameraFollowMode) {cameraFollowMode = NewCameraFollowMode;}

	UFUNCTION(BlueprintCallable)
	void ShakeForSeconds(float Seconds, float ForceShake);



private:

	bool isShaking = false;

	float timerShake = 0;

	float timerShakeMax = 0;

	float cameraSpeed = 10.f;

	float shakeForce = 10;

	FVector posToFollow;

	ECameraMode cameraMode = ECameraMode::Follow;

	ECameraFollowMode cameraFollowMode = ECameraFollowMode::Normal;

#pragma endregion

};

//enum class ECameraMode : uint8
//{
//	None,
//	Follow,
//};

//enum class ECameraFollowMode : uint8
//{
//	Normal,
//	Shake,
//};