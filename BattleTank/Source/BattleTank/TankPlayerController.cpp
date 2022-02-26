// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* Tank = GetControlledTank();


	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank is %s"), *ATank::GetDebugName(Tank))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is null"))
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if(!GetControlledTank()) {return;}

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// get raytrace end location
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector traceEnd = cameraLocation + (GetLookDirection() * lineTraceReach);

	// ignore the tank
	FCollisionQueryParams collisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
	collisionQueryParams.AddIgnoredActor(GetControlledTank());
	
	// raytrace
	FHitResult hitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		cameraLocation,
		traceEnd,
		ECollisionChannel::ECC_Visibility,
		collisionQueryParams
	))
	{
		DrawDebugPoint(GetWorld(), hitResult.Location, 10, FColor::Red);
		OutHitLocation = hitResult.Location;
		return true;
	}
	
	OutHitLocation = FVector(0);
	return false;
}

FVector ATankPlayerController::GetLookDirection() const
{
	FVector lookDirection;

	// get crosshair screen location
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D crosshairScreenLocation = { viewportSizeX * crossHairLocationX, viewportSizeY * crossHairLocationY };

	// get look direction
	FVector tmp;
	DeprojectScreenPositionToWorld(crosshairScreenLocation.X, crosshairScreenLocation.Y, tmp, lookDirection);
	return lookDirection;
}
