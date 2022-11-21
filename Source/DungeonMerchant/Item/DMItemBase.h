// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonMerchant/Inventory/DMInventoryComponent.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "DMItemBase.generated.h"

USTRUCT(BlueprintType)
struct FDMItemInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FDMItemInfoRow()
	{
		ItemDisplayName = FName(TEXT("ItemDisplayName"));
		DropActionText = FText::FromString(TEXT("DropActionText"));
		ItemTooltip = FText::FromString(TEXT("ItemTooltip"));
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FName ItemDisplayName; // Key for lookup

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemTooltip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText DropActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		bool isLegendary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		bool isResource;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class DUNGEONMERCHANT_API UDMItemBase : public UObject
{
	GENERATED_BODY()

public:

	UDMItemBase();

	virtual UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
		UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FName ItemDisplayName; // Key for lookup

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText DropActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemTooltip;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		//UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail;

	UPROPERTY()
		UDMInventoryComponent* OwningInventory;

	virtual void DropItem(class ADMCharacterBase* Character);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDropItem(class ADMCharacterBase* Character);

	UFUNCTION(BlueprintCallable)
		void SetParams(FDMItemInfoRow ItemRowToCopyFrom);
};
