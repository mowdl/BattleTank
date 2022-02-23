// Fill out your copyright notice in the Description page of Project Settings.


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


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
