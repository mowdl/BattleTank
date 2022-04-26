// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

#include "Tank.h"
#include "../TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	
	if (PlayerTank)
	{
		// move towards player

		
		// Aim at player 
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();
	}
}