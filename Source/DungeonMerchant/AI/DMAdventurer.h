// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMNPCBase.h"
#include "DungeonMerchant/Crafting/DMRecipeComponent.h"
#include "DungeonMerchant/Item/DMItemBase.h"
#include "Engine/DataTable.h"
#include "DMAdventurer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAdventurerEntering);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAdventurerWaiting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAdventurerAnnoyed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAdventurerExiting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdventurerExited, ADMAdventurer*, Adventurer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLegendaryFound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOrderFilled);

USTRUCT(BlueprintType)
struct FDMAdventurerInfoRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	FDMAdventurerInfoRow()
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Adventurer")
		FText AdventurerDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Adventurer")
		FName LegendaryItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Adventurer", meta = (MultiLine = true))
		FText Dialog1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Adventurer", meta = (MultiLine = true))
		FText Dialog2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Adventurer", meta = (MultiLine = true))
		FText Dialog3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Adventurer", meta = (MultiLine = true))
		FText ThankYouDialog;
};

UENUM()
enum class AdventureState : uint8
{
	Entering UMETA(DisplayName = "Entering"),
	Waiting UMETA(DisplayName = "Waiting"),
	Annoyed UMETA(DisplayName = "Annoyed"),
	Exiting UMETA(DisplayName = "Exiting"),
	InActive UMETA(DisplayName = "InActive"),
};

/**
 * 
 */
UCLASS()
class DUNGEONMERCHANT_API ADMAdventurer : public ADMNPCBase
{
	GENERATED_BODY()
	
public:

	ADMAdventurer();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void Interact_Implementation(APawn* InstigatorPawn) override;

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void MoveToShop();

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void MoveToExit();

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void ExitShopState();

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void WaitingState();

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void AnnoyedState();

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		void Roam();

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		FText GetAdventurerName() const;

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		TArray<FText> GetDialog() const;

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		bool TryTurnInLegendary(UDMItemBase* LegendaryItem, FText &outDialog);

	UFUNCTION(BlueprintCallable, Category = "Adventurer")
		bool TryTurnInOrder(UDMItemBase* OrderedItem, FText& outDialog);

	UPROPERTY(BlueprintReadOnly, Category = "Adventurer")
		int32 nInteractions = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
		float DefaultWaitTime;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
		float DefaultAnnoyedTime;

	UPROPERTY(BlueprintReadOnly, Category = "Adventurer")
		FDMItemInfoRow Order;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnAdventurerEntering OnAdventurerEntering;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnAdventurerWaiting OnAdventurerWaiting;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnAdventurerAnnoyed OnAdventurerAnnoyed;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnAdventurerExiting OnAdventurerExiting;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnAdventurerExited OnAdventurerExited;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnLegendaryFound OnLegendaryFound;

	UPROPERTY(BlueprintAssignable, Category = "Adventurer")
		FOnLegendaryFound OnOrderFilled;

	UPROPERTY(BlueprintReadOnly, Category = "Adventurer")
		AdventureState AdventureStateEnum;
	
protected:

	UPROPERTY(BlueprintReadOnly)
		TArray<AActor*> Points;

	UPROPERTY(BlueprintReadOnly, Category = "Time")
		FTimerHandle TimerHandle_ShopTimer;

	UPROPERTY(BlueprintReadOnly, Category = "Time")
		FTimerHandle TimerHandle_RoamTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		UDMRecipeComponent* RecipeComp;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		FDataTableRowHandle AdventurerRowHandle;
};
