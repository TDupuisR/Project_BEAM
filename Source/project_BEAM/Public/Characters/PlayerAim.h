// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

#include "PlayerAim.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_BEAM_API UPlayerAim : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerAim();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* IMCPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* InputActionPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* AimRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 100.f;
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	FVector3f AimDir(const FVector2f& Dir, const FVector3f& PlayerPos);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
