// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	ATank* Tank = GetPlayerTank();


	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank found is %s"), *ATank::GetDebugName(Tank))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is null"))
	}

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
}

