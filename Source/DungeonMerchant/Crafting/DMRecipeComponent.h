// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonMerchant/Item/DMItemBase.h"
#include "Engine/DataTable.h"
#include "DMRecipeComponent.generated.h"

USTRUCT(BlueprintType)
struct FDMRecipeInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FDMRecipeInfoRow()
	{
		Item1 = FName(TEXT("Item1"));
		Item2 = FName(TEXT("Item2"));
		ItemNameResult = FName(TEXT("ItemNameResult"));
		TimeToCraft = 10.0f;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName Item1; // Item1's display name + Item2's display name

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName Item2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FName ItemNameResult;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		float TimeToCraft;
};

USTRUCT(BlueprintType)
struct FDMFullRecipeInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FDMFullRecipeInfoRow()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FDMItemInfoRow Item1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FDMItemInfoRow Item2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
		FDMItemInfoRow ItemNameResult;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONMERCHANT_API UDMRecipeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDMRecipeComponent();

	UFUNCTION(BlueprintCallable)
		UDMItemBase* GetItemFromRecipe(FName Item1, FName Item2, float &out);

	UFUNCTION(BlueprintCallable)
		UDMItemBase* CreateRandomItem();

	UFUNCTION(BlueprintCallable)
		FDMItemInfoRow GetRandomItemInfo(bool includeLegendary);

	UFUNCTION(BlueprintCallable)
		TArray<FDMFullRecipeInfoRow> GetAllRecipes() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (RowType = "RowStructure=DMRecipeInfoRow"))
		UDataTable* RecipeTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (RowType = "RowStructure=DMItemInfoRow"))
		UDataTable* ItemTable;
};
