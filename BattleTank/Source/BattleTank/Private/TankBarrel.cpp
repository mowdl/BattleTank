// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

/**
 * @brief Move the barrel upward or downward according to relative speed
 * @param RelativeSpeed value between 1 and -1
 */
void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float NewElevationPitch = FMath::Clamp<float>(
		// new pitch from old pitch + elevation change
		GetRelativeRotation().Pitch + ElevationChange,
		// clamping values
		MinElevationDegrees,
		MaxElevationDegrees
		);
	
	SetRelativeRotation(FRotator(NewElevationPitch, 0, 0));
	
	UE_LOG(LogTemp, Warning, TEXT("%f: Elevate by %f"), GetWorld()->GetTimeSeconds(),RelativeSpeed)
}
