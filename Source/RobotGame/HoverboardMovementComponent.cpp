// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverboardMovementComponent.h"

// Sets default values for this component's properties
UHoverboardMovementComponent::UHoverboardMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpeedToForceFactor = 10;
	LateralSpeedToForceFactor = 10;
	AngularSpeedToTorqueFactor = 1000000;
}


// Called when the game starts
void UHoverboardMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	RefToHoverboard = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
}


// Called every frame
void UHoverboardMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RefToHoverboard) {
		//UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f"), CurrentSpeed);
		CalculateForwardForce();
		CalculateLateralForce();
		CalculateLateralStabilityForce();
	}
}

void UHoverboardMovementComponent::CalculateForwardForce()
{
	FVector linearVelocity = RefToHoverboard->GetPhysicsLinearVelocity();
	//FVector forwardVector = RefToHoverboard->GetForwardVector();
	FVector forwardVector = -(RefToHoverboard->GetRightVector());
	CurrentSpeed = FVector::DotProduct(linearVelocity, forwardVector);

	float speedDifference = TargetSpeed - CurrentSpeed;
	float speedForce = speedDifference * SpeedToForceFactor;
	RefToHoverboard->AddForce(forwardVector * speedForce);
}

void UHoverboardMovementComponent::CalculateLateralForce()
{
	FVector angularVelocity = RefToHoverboard->GetPhysicsAngularVelocityInDegrees();
	FVector upVector = RefToHoverboard->GetUpVector();
	CurrentAngularSpeed = FVector::DotProduct(angularVelocity, upVector);

	float angularSpeedDifference = TargetAngularSpeed - CurrentAngularSpeed;
	float angularSpeedForce = angularSpeedDifference * AngularSpeedToTorqueFactor;
	RefToHoverboard->AddTorqueInDegrees(upVector * angularSpeedForce);
}

void UHoverboardMovementComponent::CalculateLateralStabilityForce()
{
	FVector lateralVelocity = RefToHoverboard->GetPhysicsLinearVelocity();
	//FVector rightVector = RefToHoverboard->GetRightVector();
	FVector rightVector = RefToHoverboard->GetForwardVector();
	float lateralSpeed = FVector::DotProduct(lateralVelocity, rightVector);
	float lateralForce = -(lateralSpeed * LateralSpeedToForceFactor);

	RefToHoverboard->AddForce(lateralForce * rightVector);
}