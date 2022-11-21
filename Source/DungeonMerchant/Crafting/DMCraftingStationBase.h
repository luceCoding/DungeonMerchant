// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMCraftInterface.h"
#include "DMRecipeComponent.h"
#include "DungeonMerchant/Interaction/DMInteractableBase.h"
#include "DungeonMerchant/Inventory/DMInventoryInterface.h"
#include "DungeonMerchant/Item/DMItemBase.h"
#include "Engine/DataTable.h"
#include "DMCraftingStationBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftScrapped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftCanceled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCraftCollected);

UCLASS()
class DUNGEONMERCHANT_API ADMCraftingStationBase : public ADMInteractableBase, public IDMCraftInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMCraftingStationBase();

	UFUNCTION(BlueprintCallable, Category = "Craft")
		void CraftStart_Implementation();

	UFUNCTION()
		void CraftFinished_Implementation();

	UFUNCTION()
		void CraftScrappedDelay_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Craft")
		bool CancelCrafting_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Craft")
		UDMItemBase* CollectItem_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddCraftItem1(class UDMItemBase* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddCraftItem2(class UDMItemBase* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UDMItemBase* RemoveCraftItem1();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UDMItemBase* RemoveCraftItem2();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UDMRecipeComponent* RecipeComp;

	UPROPERTY(BlueprintReadWrite, Category = "Time")
		FTimerHandle TimerHandle_CraftDelayed;

	UPROPERTY(BlueprintReadWrite, Category = "Time")
		FTimerHandle TimerHandle_CraftScrappedDelayed;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Craft")
		UDMItemBase* ScrapCraftItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Craft")
		UDMItemBase* TargetItemToCraft;

	UPROPERTY(BlueprintAssignable, Category = "Craft")
		FOnCraftUpdated OnCraftUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Craft")
		FOnCraftStart OnCraftStart;

	UPROPERTY(BlueprintAssignable, Category = "Craft")
		FOnCraftFinished OnCraftFinished;

	UPROPERTY(BlueprintAssignable, Category = "Craft")
		FOnCraftScrapped OnCraftScrapped;

	UPROPERTY(BlueprintAssignable, Category = "Craft")
		FOnCraftCanceled OnCraftCanceled;

	UPROPERTY(BlueprintAssignable, Category = "Craft")
		FOnCraftCollected OnCraftCollected;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UDMInventoryComponent* UncraftedInventoryComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UDMInventoryComponent* CraftedInventoryComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
		float DefaultCraftDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
		float CraftScrappedDelay;
};
