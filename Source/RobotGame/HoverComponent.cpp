// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverComponent.h"
#include "HoverboardCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HoverDistance = 100.0f;
	Acceleration = 980;
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	RefToHoverboard = Cast<UPrimitiveComponent>(GetAttachParent());

	if (RefToHoverboard) {
		Stiffness = RefToHoverboard->GetMass() * Acceleration;
		Damping = Stiffness / 10;
	}
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (RefToHoverboard) {
	//	FVector start = GetComponentLocation();
	//	FVector end = start - (GetUpVector() * (HoverDistance * 2));
	//	FCollisionQueryParams CollisionParams;
	//	CollisionParams.AddIgnoredActor(GetOwner());
	//	FHitResult OutHit;

	//	DrawDebugLine(GetWorld(), start, end, FColor::Green, false, -1.0f, ECC_WorldStatic, 2.0f);

	//	if (GetWorld()->LineTraceSingleByChannel(OutHit, start, end, ECC_Visibility, CollisionParams)) {
	//		float compression = ((HoverDistance - OutHit.Distance) / HoverDistance);
	//		float stiffnessFactor = Stiffness * compression;
	//		float dampingFactor = Damping * ((compression - PreviousCompression) / GetWorld()->DeltaTimeSeconds);

	//		HoverForce = stiffnessFactor + dampingFactor;
	//		PreviousCompression = compression;

	//		FVector force = GetUpVector() * HoverForce;
	//		RefToHoverboard->AddForceAtLocation(force, GetComponentLocation());
	//	}
	//}
}

