// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Hoverboard.generated.h"

UCLASS()
class ROBOTGAME_API AHoverboard : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hoverboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* BoomArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class UHoverComponent* Hover_FL;

	UPROPERTY(EditAnywhere)
	class UHoverComponent* Hover_FR;

	UPROPERTY(EditAnywhere)
	class UHoverComponent* Hover_BL;

	UPROPERTY(EditAnywhere)
	class UHoverComponent* Hover_BR;

	UPROPERTY(EditAnywhere)
	class UHoverboardMovementComponent* HoverboardMovement;

public:
	// Sets default values for this pawn's properties
	AHoverboard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	float ForwardSpeedRate;
	float RightSpeedRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float HoverDistance;
	float Stiffness;
	float Damping;
	float PreviousCompression;
	float HoverForce;
	float Acceleration;
};
