// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoverboardMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROBOTGAME_API UHoverboardMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverboardMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CalculateForwardForce();
	void CalculateLateralForce();
	void CalculateLateralStabilityForce();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetTargetSpeed(float targetSpeed) { TargetSpeed = targetSpeed; }
	void SetTargetAngularSpeed(float targetAngularSpeed) { TargetAngularSpeed = targetAngularSpeed; }
	float GetCurrentSpeed() { return CurrentSpeed; }

private:
	float TargetSpeed;
	float CurrentSpeed;
	float TargetAngularSpeed;
	float CurrentAngularSpeed;
	float SpeedToForceFactor;
	float AngularSpeedToTorqueFactor;	
	float LateralSpeedToForceFactor;

	class UPrimitiveComponent* RefToHoverboard;
};
