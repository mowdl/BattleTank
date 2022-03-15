// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	const float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	const float NewRotationYaw = GetRelativeRotation().Yaw + RotationChange;
	
	try
	{
		SetRelativeRotation(FRotator(0, NewRotationYaw, 0));
	}
	catch (...)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Set Relative Rotation threw an execption"), *AActor::GetDebugName(GetOwner()))
	}
		
}
