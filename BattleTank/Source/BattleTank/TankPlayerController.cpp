// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const ATank* Tank = GetControlledTank();


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
	AimAtCrossHair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrossHair() const
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
	FVector traceEnd = cameraLocation + (GetLookDirection() * LineTraceReach);

	// ignore the tank
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
	CollisionQueryParams.AddIgnoredActor(GetControlledTank());
	
	// raytrace
	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		cameraLocation,
		traceEnd,
		ECollisionChannel::ECC_Visibility,
		CollisionQueryParams
	))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	
	OutHitLocation = FVector(0);
	return false;
}

FVector ATankPlayerController::GetLookDirection() const
{
	FVector LookDirection;

	// get crosshair screen location
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D crosshairScreenLocation = { ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY };

	// get look direction
	FVector Tmp;
	DeprojectScreenPositionToWorld(crosshairScreenLocation.X, crosshairScreenLocation.Y, Tmp, LookDirection);
	return LookDirection;
}
