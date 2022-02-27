// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"

#include "TankAimingComponent.h"

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

void UTankAimingComponent::AimAt(FVector hitLocation, float LaunchSpeed)
{
	FVector LaunchVelocity;

	FVector LaunchLocation = Barrel->GetSocketLocation(FName("Projectile"));

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
		
		FVector AimDirection = LaunchVelocity.GetSafeNormal();

		// Draw debug helpers
		DrawDebugLine(GetWorld(), LaunchLocation, (LaunchLocation + (AimDirection * 800)), FColor::Red, false, -1.0f, (uint8)0U, 10);
		
		MoveBarrel(AimDirection);

		return;
	}
	
	UE_LOG(LogTemp, Error, TEXT("Leanch Velocity Failed"))


}

void UTankAimingComponent::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// difference between current barrel rotation and AimDirection
	FRotator rotationDifference = AimDirection.Rotation() - Barrel->GetForwardVector().Rotation();

	FRotator yawDifference = FRotator(0.0f, rotationDifference.Yaw, 0.0f);
	FRotator pitchDifference = FRotator(rotationDifference.Pitch, 0.0f, 0.0f);

	float yawRotationSpeed = 1.0f;

	Barrel->AddLocalRotation(pitchDifference * (GetWorld()->GetDeltaSeconds() * yawRotationSpeed));

	// move barrel the right amount this frame
}

