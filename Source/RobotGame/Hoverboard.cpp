// Fill out your copyright notice in the Description page of Project Settings.


#include "Hoverboard.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HoverComponent.h"
#include "HoverboardMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHoverboard::AHoverboard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ForwardSpeedRate = 1000.0f;
	RightSpeedRate = 100.0f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Hoverboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hoverboard"));
	Hoverboard->SetupAttachment(RootComponent);

	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));
	BoomArm->SetupAttachment(Hoverboard);
	BoomArm->TargetArmLength = 300.0f;
	BoomArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Hover_FL = CreateDefaultSubobject<UHoverComponent>(TEXT("Hover_FL"));
	Hover_FL->SetupAttachment(Hoverboard, "FLSocket");

	Hover_FR = CreateDefaultSubobject<UHoverComponent>(TEXT("Hover_FR"));
	Hover_FR->SetupAttachment(Hoverboard, "FRSocket");

	Hover_BL = CreateDefaultSubobject<UHoverComponent>(TEXT("Hover_BL"));
	Hover_BL->SetupAttachment(Hoverboard, "BLSocket");

	Hover_BR = CreateDefaultSubobject<UHoverComponent>(TEXT("Hover_BR"));
	Hover_BR->SetupAttachment(Hoverboard, "BRSocket");

	HoverboardMovement = CreateDefaultSubobject<UHoverboardMovementComponent>(TEXT("HoverboardMovement"));

	HoverDistance = 100.0f;
	Acceleration = 980;
}

// Called when the game starts or when spawned
void AHoverboard::BeginPlay()
{
	Super::BeginPlay();

	Stiffness = Hoverboard->GetMass() * Acceleration;
	Damping = Stiffness / 10;
}

// Called every frame
void AHoverboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector start = Hoverboard->GetComponentLocation();
	//FVector end = start - (Hoverboard->GetUpVector() * (HoverDistance));
	//FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredComponent(Hoverboard);
	//FHitResult OutHit;

	//DrawDebugLine(GetWorld(), start, end, FColor::Green, false, -1.0f, ECC_WorldStatic, 2.0f);

	//if (GetWorld()->LineTraceSingleByChannel(OutHit, start, end, ECC_Visibility, CollisionParams)) {
	//	float compression = ((HoverDistance - OutHit.Distance) / HoverDistance);
	//	float stiffnessFactor = Stiffness * compression;
	//	float dampingFactor = Damping * ((compression - PreviousCompression) / GetWorld()->DeltaTimeSeconds);

	//	HoverForce = stiffnessFactor + dampingFactor;
	//	PreviousCompression = compression;

	//	FVector force = Hoverboard->GetUpVector() * HoverForce * 10;
	//	Hoverboard->AddForce(force);
	//}
}

// Called to bind functionality to input
void AHoverboard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AHoverboard::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AHoverboard::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AHoverboard::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AHoverboard::AddControllerYawInput);
}

void AHoverboard::MoveForward(float AxisValue)
{
	HoverboardMovement->SetTargetSpeed(AxisValue * ForwardSpeedRate);
}

void AHoverboard::MoveRight(float AxisValue)
{
	HoverboardMovement->SetTargetAngularSpeed(AxisValue * RightSpeedRate);
}