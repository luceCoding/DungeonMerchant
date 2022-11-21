// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DMInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONMERCHANT_API UDMInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDMInventoryComponent();
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Inventory")
		TArray<class UDMItemBase*> DefaultItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
		TArray<class UDMItemBase*> InventoryItems;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItem(class UDMItemBase* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool AddItemByIdx(UDMItemBase* ItemToAdd, int32 InsertIdx);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItem(class UDMItemBase* ItemToRemove);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool RemoveItemByIdx(UDMItemBase* ItemToRemove, int32 RemoveIdx);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		static bool TransferItemTo(UDMItemBase* ItemToTransfer, UDMInventoryComponent* TransferFrom, UDMInventoryComponent* TransferTo);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		bool isThereItemByName(FName NameOfItem) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		UDMItemBase* RemoveItemByName(FName NameOfItem);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
