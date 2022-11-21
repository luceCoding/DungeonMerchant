// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMInventoryComponent.h"
#include "UObject/Interface.h"
#include "DMInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDMInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONMERCHANT_API IDMInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
		bool AddItem(class UDMItemBase* ItemToAdd);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Inventory")
		bool RemoveItem(class UDMItemBase* ItemToRemove);
};
