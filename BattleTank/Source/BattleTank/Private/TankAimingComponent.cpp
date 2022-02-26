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

	if (UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		LaunchVelocity,
		Barrel->GetComponentLocation(),
		hitLocation,
		LaunchSpeed,
		false,
		20.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true
	))
	{
		LaunchVelocity.Normalize();

		// Draw debug helpers
		DrawDebugLine(GetWorld(), Barrel->GetComponentLocation(), (Barrel->GetComponentLocation() + (LaunchVelocity * 200)), FColor::Red);

		UE_LOG(LogTemp, Warning, TEXT("Leanch Velocity is: %s"), *LaunchVelocity.ToString())
		return;
	}
	
	UE_LOG(LogTemp, Error, TEXT("Leanch Velocity Failed"))


}

void UTankAimingComponent::SetBarrelRefrence(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

