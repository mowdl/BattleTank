// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "../TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* playerTank = GetPlayerTank();

	if (playerTank)
	{
		// Aim at player
		GetControlledTank()->AimAt(playerTank->GetActorLocation());
		
		// Move towrds player

		// Fire if ready
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

