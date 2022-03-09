// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief Tank Aiming Component Pointer
	 */
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	UTankAimingComponent* TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation) const;

	/**
	 * @brief Sets the reference to TankBarrel in the TankAimingComponent
	 * @param BarrelToSet Barrel to Set 
	 */
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet) const;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; // 1 Km/s


};
