// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(const FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelRefrence(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) const
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	const bool bIsReloaded = FPlatformTime::Seconds() > (LastFireTime + FireReloadTimeSeconds);

		
	if (Barrel && bIsReloaded)
	{
		// Spawn a projectile at projectile's socket location with location
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		// Launch the projectile
		Projectile->LaunchProjectile(LaunchSpeed);

		// update last fire time
		LastFireTime = FPlatformTime::Seconds();
	}
}
