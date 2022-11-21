// Fill out your copyright notice in the Description page of Project Settings.


#include "DMCraftingStationBase.h"

#include "DungeonMerchant/Inventory/DMInventoryComponent.h"


// Sets default values
ADMCraftingStationBase::ADMCraftingStationBase()
{
	UncraftedInventoryComp = CreateDefaultSubobject<UDMInventoryComponent>("UncraftedInventoryComp");
	UncraftedInventoryComp->Capacity = 2;
	CraftedInventoryComp = CreateDefaultSubobject<UDMInventoryComponent>("CraftedInventoryComp");
	CraftedInventoryComp->Capacity = 1;
	RecipeComp = CreateDefaultSubobject<UDMRecipeComponent>("RecipeComp");
	DefaultCraftDelay = 15;
}

// Called when the game starts or when spawned
void ADMCraftingStationBase::BeginPlay()
{
	Super::BeginPlay();
	ensure(ScrapCraftItem);
	ensure(UncraftedInventoryComp->Capacity == 2);
	ensure(CraftedInventoryComp->Capacity == 1);
}

/*
void ADMCraftingStationBase::Interact_Implementation(APawn* InstigatorPawn)
{
	//Super::Interact_Implementation();
	UE_LOG(LogTemp, Log, TEXT("====Interact craft."));
	CraftStart_Implementation();
}
*/

void ADMCraftingStationBase::CraftStart_Implementation()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_CraftDelayed))
	{
		UE_LOG(LogTemp, Log, TEXT("====Crafting in progress."));
		return;
	}
	if (CraftedInventoryComp->InventoryItems.Num())
	{
		UE_LOG(LogTemp, Log, TEXT("====Collect craft item first."));
		return;
	}
	if (UncraftedInventoryComp->InventoryItems.Num() != 2)
	{
		UE_LOG(LogTemp, Log, TEXT("====Need two items to craft."));
		return;
	}
	UDMItemBase* Item1 = UncraftedInventoryComp->InventoryItems[0];
	UDMItemBase* Item2 = UncraftedInventoryComp->InventoryItems[1];
	if (Item1 == nullptr || Item2 == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("====Null items."));
		return;
	}
	float outTimeToCraft;
	TargetItemToCraft = RecipeComp->GetItemFromRecipe(Item1->ItemDisplayName, Item2->ItemDisplayName, outTimeToCraft);
	if (TargetItemToCraft == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("====Invalid item combo."));
		GetWorldTimerManager().SetTimer(TimerHandle_CraftDelayed, this, &ADMCraftingStationBase::CraftFinished_Implementation, DefaultCraftDelay);
		//return;
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle_CraftDelayed, this, &ADMCraftingStationBase::CraftFinished_Implementation, outTimeToCraft);
	}
	UE_LOG(LogTemp, Log, TEXT("====Crafting Started."));
	OnCraftUpdated.Broadcast();
	OnCraftStart.Broadcast();
}

void ADMCraftingStationBase::CraftFinished_Implementation()
{
	if (TargetItemToCraft)
	{
		UE_LOG(LogTemp, Log, TEXT("====Crafting Finished."));
		GetWorldTimerManager().SetTimer(TimerHandle_CraftScrappedDelayed, this, &ADMCraftingStationBase::CraftScrappedDelay_Implementation, CraftScrappedDelay);
		UDMItemBase* CraftedItem = DuplicateObject(TargetItemToCraft, GetWorld());
		CraftedInventoryComp->AddItem(CraftedItem);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("====Crafted scraps."));
		UDMItemBase* CraftedItem = DuplicateObject(ScrapCraftItem, GetWorld());
		CraftedInventoryComp->AddItem(CraftedItem);
	}
	UncraftedInventoryComp->InventoryItems.Empty();
	OnCraftUpdated.Broadcast();
	OnCraftFinished.Broadcast();
}

void ADMCraftingStationBase::CraftScrappedDelay_Implementation()
{
	if (CraftedInventoryComp->InventoryItems.Num())
	{
		UE_LOG(LogTemp, Log, TEXT("====Crafting item overcooked, turned into scraps."));
		UDMItemBase* CraftedItem = DuplicateObject(ScrapCraftItem, GetWorld());;
		CraftedInventoryComp->RemoveItem(CraftedInventoryComp->InventoryItems[0]);
		CraftedInventoryComp->AddItem(CraftedItem);
		OnCraftUpdated.Broadcast();
		OnCraftScrapped.Broadcast();
	}
}

bool ADMCraftingStationBase::CancelCrafting_Implementation()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_CraftDelayed))
	{
		UE_LOG(LogTemp, Log, TEXT("====Crafting Node Cancelled."));
		GetWorldTimerManager().ClearTimer(TimerHandle_CraftDelayed);
		OnCraftUpdated.Broadcast();
		OnCraftCanceled.Broadcast();
		return true;
	}
	return false;
}

UDMItemBase* ADMCraftingStationBase::CollectItem_Implementation()
{
	if (!GetWorldTimerManager().IsTimerActive(TimerHandle_CraftDelayed) && CraftedInventoryComp->InventoryItems.Num())
	{
		UE_LOG(LogTemp, Log, TEXT("====Crafting Node Collected."));
		GetWorldTimerManager().ClearTimer(TimerHandle_CraftScrappedDelayed);
		UDMItemBase* CraftedItem = CraftedInventoryComp->InventoryItems[0];
		CraftedInventoryComp->RemoveItem(CraftedInventoryComp->InventoryItems[0]);
		OnCraftUpdated.Broadcast();
		OnCraftCollected.Broadcast();
		return CraftedItem;
	}
	UE_LOG(LogTemp, Log, TEXT("====No Item to Collect."));
	return nullptr;
}

bool ADMCraftingStationBase::AddCraftItem1(UDMItemBase* ItemToAdd)
{
	if (UncraftedInventoryComp->InventoryItems.IsValidIndex(0))
	{
		return false;
	}
	return UncraftedInventoryComp->AddItemByIdx(ItemToAdd, 0);
}

bool ADMCraftingStationBase::AddCraftItem2(UDMItemBase* ItemToAdd)
{
	if (UncraftedInventoryComp->InventoryItems.IsValidIndex(1))
	{
		return false;
	}
	return UncraftedInventoryComp->AddItemByIdx(ItemToAdd, 1);
}

UDMItemBase* ADMCraftingStationBase::RemoveCraftItem1()
{
	if (UncraftedInventoryComp->InventoryItems.IsValidIndex(0))
	{
		UDMItemBase* tmpPtr = UncraftedInventoryComp->InventoryItems[0];
		UncraftedInventoryComp->RemoveItemByIdx(tmpPtr, 0);
		return tmpPtr;
	}
	return nullptr;
}

UDMItemBase* ADMCraftingStationBase::RemoveCraftItem2()
{
	if (UncraftedInventoryComp->InventoryItems.IsValidIndex(1))
	{
		UDMItemBase* tmpPtr = UncraftedInventoryComp->InventoryItems[1];
		UncraftedInventoryComp->RemoveItemByIdx(tmpPtr, 1);
		return tmpPtr;
	}
	return nullptr;
}