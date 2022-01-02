// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverboardMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AHoverboardMovement::AHoverboardMovement()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 300.0f;
	BoomArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	//bUseControllerRotationPitch = false;
	//bUseControllerRotationRoll = false;
	//bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AHoverboardMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoverboardMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHoverboardMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AHoverboardMovement::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRIght"), this, &AHoverboardMovement::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AHoverboardMovement::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AHoverboardMovement::AddControllerYawInput);
}

void AHoverboardMovement::MoveForward(float AxisValue)
{
	if (Controller != NULL && AxisValue != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, AxisValue);
	}
}

void AHoverboardMovement::MoveRight(float AxisValue)
{
	if (Controller != NULL && AxisValue != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, AxisValue);
	}
}

