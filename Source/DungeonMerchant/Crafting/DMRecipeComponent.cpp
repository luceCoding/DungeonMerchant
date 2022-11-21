// Fill out your copyright notice in the Description page of Project Settings.


#include "DMRecipeComponent.h"

// Sets default values for this component's properties
UDMRecipeComponent::UDMRecipeComponent()
{
}

// Called when the game starts
void UDMRecipeComponent::BeginPlay()
{
	Super::BeginPlay();

	ensure(RecipeTable);
	ensure(ItemTable);
}

UDMItemBase* UDMRecipeComponent::GetItemFromRecipe(FName Item1, FName Item2, OUT float &out)
{
	FName ConcatKey = FName(Item1.ToString().Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase) 
		+ Item2.ToString().Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase));
	FDMRecipeInfoRow* FoundRecipeInfoRow = RecipeTable->FindRow<FDMRecipeInfoRow>(ConcatKey, "");
	if (!FoundRecipeInfoRow)
	{
		//Swap keys and try again.
		//TODO: Optimize with TMap
		ConcatKey = FName(Item2.ToString().Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase)
			+ Item1.ToString().Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase));
		FoundRecipeInfoRow = RecipeTable->FindRow<FDMRecipeInfoRow>(ConcatKey, "");
	}
	if (!FoundRecipeInfoRow)
	{
		UE_LOG(LogTemp, Log, TEXT("Recipe row not found."));
		return nullptr;
	}
	FName ItemKey = FName(FoundRecipeInfoRow->ItemNameResult.ToString().Replace(TEXT(" "), TEXT("")));
	FDMItemInfoRow* FoundItemInfoRow = ItemTable->FindRow<FDMItemInfoRow>(ItemKey, "");
	if (!FoundItemInfoRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item row not found."));
		return nullptr;
	}
	UDMItemBase* item = NewObject<UDMItemBase>(GetWorld(), UDMItemBase::StaticClass());
	item->SetParams(*FoundItemInfoRow);
	out = FoundRecipeInfoRow->TimeToCraft;
	return item;
}

UDMItemBase* UDMRecipeComponent::CreateRandomItem()
{
	TArray<FDMItemInfoRow*> AllRows;
	ItemTable->GetAllRows("", AllRows);
	auto RdmIdx = FMath::RandRange(0, AllRows.Num()-1);
	UDMItemBase* RdmItem = NewObject<UDMItemBase>(GetWorld(), UDMItemBase::StaticClass());
	if (RdmIdx > -1)
	{
		RdmItem->SetParams(*AllRows[RdmIdx]);
	}
	return RdmItem;
}

FDMItemInfoRow UDMRecipeComponent::GetRandomItemInfo(bool includeLegendary = false)
{
	TArray<FDMItemInfoRow*> AllRows;
	ItemTable->GetAllRows("", AllRows);

	for (int i = 0; i < 20; i++) //try 10 times
	{
		auto RdmIdx = FMath::RandRange(0, AllRows.Num() - 1);
		if (includeLegendary)
		{
			UE_LOG(LogTemp, Log, TEXT("Rdm Idx: %d"), RdmIdx);
			return *AllRows[RdmIdx];
		}
		else if (!AllRows[RdmIdx]->isLegendary && !AllRows[RdmIdx]->isResource)
		{
			UE_LOG(LogTemp, Log, TEXT("Rdm Idx: %d"), RdmIdx);
			return *AllRows[RdmIdx];
		}
	}
	return FDMItemInfoRow();
}

TArray<FDMFullRecipeInfoRow> UDMRecipeComponent::GetAllRecipes() const
{
	TArray<FDMFullRecipeInfoRow> RecipesFound;

	TArray<FDMRecipeInfoRow*> AllRecipeRows;
	RecipeTable->GetAllRows("", AllRecipeRows);
	if (!AllRecipeRows.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get recipe table."));
	}

	for (FDMRecipeInfoRow* row : AllRecipeRows)
	{
		FDMFullRecipeInfoRow FullRecipe;
		FName item1Key = row->Item1;
		FName item2Key = row->Item2;
		FName item3Key = row->Item2;
		FullRecipe.Item1 = *ItemTable->FindRow<FDMItemInfoRow>(item1Key, "");
		FullRecipe.Item2 = *ItemTable->FindRow<FDMItemInfoRow>(item2Key, "");
		FullRecipe.ItemNameResult = *ItemTable->FindRow<FDMItemInfoRow>(item3Key, "");
		RecipesFound.Add(FullRecipe);
	}
	return RecipesFound;
}
