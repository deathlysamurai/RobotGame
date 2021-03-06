// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverboardCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHoverboardCharacter::AHoverboardCharacter()
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

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
}

// Called when the game starts or when spawned
void AHoverboardCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GetCapsuleMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	

	//AttachHoverboard();
}

void AHoverboardCharacter::AttachHoverboard() 
{
	UWorld *world = GetWorld();
	FVector location = GetActorLocation();
	location.Z -= 5;
	FRotator rotation = GetActorRotation();
	AActor* Hoverboard = world->SpawnActor(HoverboardClass, &location, &rotation);
	AttachToActor(Hoverboard, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "StandSocket");
}

// Called every frame
void AHoverboardCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHoverboardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AHoverboardCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AHoverboardCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AHoverboardCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AHoverboardCharacter::AddControllerYawInput);
}

void AHoverboardCharacter::MoveForward(float AxisValue)
{
	if (Controller != NULL && AxisValue != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, AxisValue);
	}
}

void AHoverboardCharacter::MoveRight(float AxisValue)
{
	if (Controller != NULL && AxisValue != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, AxisValue);
	}
}

