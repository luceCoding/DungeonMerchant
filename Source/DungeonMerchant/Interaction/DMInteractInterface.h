// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DMInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDMInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONMERCHANT_API IDMInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void InteractStarted(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void InteractDelayed(APawn* InstigatorPawn);
};
