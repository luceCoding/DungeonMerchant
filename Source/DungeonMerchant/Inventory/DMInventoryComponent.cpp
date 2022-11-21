// Fill out your copyright notice in the Description page of Project Settings.


#include "DMInventoryComponent.h"

#include "DungeonMerchant/Item/DMItemBase.h"

// Sets default values for this component's properties
UDMInventoryComponent::UDMInventoryComponent()
{
	Capacity = 10;
}

// Called when the game starts
void UDMInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

bool UDMInventoryComponent::AddItem(UDMItemBase* ItemToAdd)
{
	if (!ItemToAdd)
	{
		UE_LOG(LogTemp, Error, TEXT("Item is null."));
		return false;
	}
	if (InventoryItems.Num() >= Capacity)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory full."));
		return false;
	}

	ItemToAdd->OwningInventory = this;
	ItemToAdd->World = GetWorld();
	InventoryItems.Add(ItemToAdd);
	OnInventoryUpdated.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("Inventory: %d"), InventoryItems.Num());
	return true;
}

bool UDMInventoryComponent::AddItemByIdx(UDMItemBase* ItemToAdd, int32 InsertIdx)
{
	if (!ItemToAdd)
	{
		UE_LOG(LogTemp, Error, TEXT("Item is null."));
		return false;
	}
	if (InventoryItems.Num() >= Capacity)
	{
		UE_LOG(LogTemp, Log, TEXT("Inventory full."));
		return false;
	}

	ItemToAdd->OwningInventory = this;
	ItemToAdd->World = GetWorld();
	InventoryItems.Insert(ItemToAdd, InsertIdx);
	OnInventoryUpdated.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("Inventory: %d"), InventoryItems.Num());
	return true;
}

bool UDMInventoryComponent::RemoveItem(UDMItemBase* ItemToRemove)
{
	if (ItemToRemove)
	{
		ItemToRemove->OwningInventory = nullptr;
		ItemToRemove->World = nullptr;
		InventoryItems.RemoveSingle(ItemToRemove);
		OnInventoryUpdated.Broadcast();
		UE_LOG(LogTemp, Log, TEXT("Inventory: %d"), InventoryItems.Num());
		return true;
	}
	return false;
}

bool UDMInventoryComponent::RemoveItemByIdx(UDMItemBase* ItemToRemove, int32 RemoveIdx)
{
	if (ItemToRemove && InventoryItems.IsValidIndex(RemoveIdx) && InventoryItems[RemoveIdx] == ItemToRemove)
	{
		ItemToRemove->OwningInventory = nullptr;
		ItemToRemove->World = nullptr;
		InventoryItems.RemoveAt(RemoveIdx);
		OnInventoryUpdated.Broadcast();
		UE_LOG(LogTemp, Log, TEXT("Inventory: %d"), InventoryItems.Num());
		return true;
	}
	return false;
}

bool UDMInventoryComponent::TransferItemTo(UDMItemBase* ItemToTransfer, UDMInventoryComponent* TransferFrom,
	UDMInventoryComponent* TransferTo)
{
	if (ItemToTransfer && TransferFrom && TransferTo)
	{
		if (TransferFrom->RemoveItem(ItemToTransfer))
		{
			return TransferTo->AddItem(ItemToTransfer);
		}
	}
	return false;
}

bool UDMInventoryComponent::isThereItemByName(FName NameOfItem) const
{
	for (UDMItemBase* item : InventoryItems)
	{
		if (item && item->ItemDisplayName == NameOfItem)
		{
			return true;
		}
	}
	return false;
}

UDMItemBase* UDMInventoryComponent::RemoveItemByName(FName NameOfItem)
{
	for (UDMItemBase* item : InventoryItems)
	{
		if (item && item->ItemDisplayName == NameOfItem)
		{
			RemoveItem(item);
			return item;
		}
	}
	return nullptr;
}
