// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonMerchant/Item/DMItemBase.h"
#include "UObject/Interface.h"
#include "DMCraftInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDMCraftInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONMERCHANT_API IDMCraftInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void CraftStart();

	UFUNCTION(BlueprintNativeEvent)
		void CraftDelayed();

	UFUNCTION(BlueprintNativeEvent)
		void CraftScrappedDelayed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool CancelCrafting();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		UDMItemBase* CollectItem();
};
