// Fill out your copyright notice in the Description page of Project Settings.


#include "DMItemBase.h"

UDMItemBase::UDMItemBase()
{
	ItemDisplayName = FName("Item Name");
	DropActionText = FText::FromString("Drop Item");
}

void UDMItemBase::DropItem(ADMCharacterBase* Character)
{
	if (Character)
	{
		if (OwningInventory)
		{
			OwningInventory->RemoveItem(this);
			UE_LOG(LogTemp, Log, TEXT("====Dropped item."));
		}
	}
}

void UDMItemBase::SetParams(FDMItemInfoRow ItemRowToCopyFrom)
{
	this->ItemDisplayName = ItemRowToCopyFrom.ItemDisplayName;
	this->ItemTooltip = ItemRowToCopyFrom.ItemTooltip;
	this->DropActionText = ItemRowToCopyFrom.DropActionText;
	this->Thumbnail = ItemRowToCopyFrom.Thumbnail;
	this->Thumbnail->AddToRoot();
}
