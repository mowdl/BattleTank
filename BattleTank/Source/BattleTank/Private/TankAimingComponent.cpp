// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

#include "DrawDebugHelpers.h"

#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float LaunchSpeed) const
{
	FVector LaunchVelocity;

	const FVector LaunchLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,								// context object
		LaunchVelocity,						// OUT launch velocity
		LaunchLocation,						// launch location
		hitLocation,						// hit location
		LaunchSpeed,						// launch speed
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,		// do not trace (Cant we trace here?)
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	))
	{
		const FVector AimDirection = LaunchVelocity.GetSafeNormal();

		// Draw debug helpers
		DrawDebugLine(GetWorld(), LaunchLocation, (LaunchLocation + (AimDirection * 800)), FColor::Red, false, -1.0f, (uint8)0U, 10);

		MoveBarrel(AimDirection);

		UE_LOG(LogTemp, Warning, TEXT("%f: Aim Direction: %s"), GetWorld()->GetTimeSeconds(), *AimDirection.ToString())
		return;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%f: Aim Direction Not Found"), GetWorld()->GetTimeSeconds())
	}

	UE_LOG(LogTemp, Error, TEXT("Leanch Velocity Failed"))
}

void UTankAimingComponent::SetBarrelRefrence(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) const
{
	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel Reference is null"))
		return;
	}

	// Difference between barrel rotation and AimDirection
	const FRotator rotationDifference = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();
	
	Barrel->Elevate(rotationDifference.Pitch);

	// move barrel the right amount this frame
}
