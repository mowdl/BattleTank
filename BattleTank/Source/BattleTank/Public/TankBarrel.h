// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), HideCategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
		
public:
	// -1 is max downward and +1 is max up movement
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 20.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 5.0f;
};
