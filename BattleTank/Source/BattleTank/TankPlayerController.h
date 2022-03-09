// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
		float CrossHairLocationX = 0.5;

	UPROPERTY(EditAnywhere)
		float CrossHairLocationY = 0.3;

	UPROPERTY(EditAnywhere)
		float LineTraceReach = 1000000;

private:
	void AimAtCrossHair() const;

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	FVector GetLookDirection() const;
};
