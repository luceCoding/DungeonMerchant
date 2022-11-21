// Fill out your copyright notice in the Description page of Project Settings.


#include "DMAdventurer.h"

#include "DMAIController.h"
#include "DMTargetPoint.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

ADMAdventurer::ADMAdventurer()
{
	DefaultWaitTime = 120.0f;
	DefaultAnnoyedTime = 15.0f;
	RecipeComp = CreateDefaultSubobject<UDMRecipeComponent>("RecipeComp");
}

void ADMAdventurer::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADMTargetPoint::StaticClass(), Points);
	ensure(!AdventurerRowHandle.IsNull());
}

void ADMAdventurer::Interact_Implementation(APawn* InstigatorPawn)
{
	//TODO: Open dialog
	UE_LOG(LogTemp, Log, TEXT("====Adventurer Interacted."));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *this->GetDialog().ToString());
}

void ADMAdventurer::MoveToShop()
{
	ADMAIController* AIController = Cast<ADMAIController>(GetController());
	if (AIController)
	{
		for (AActor* point : Points)
		{
			if (point)
			{
				ADMTargetPoint* pointToMoveTo = Cast<ADMTargetPoint>(point);
				if (pointToMoveTo && pointToMoveTo->PointName == "Shop")
				{
					UE_LOG(LogTemp, Log, TEXT("====Adventurer moving to shop."));
					AdventureStateEnum = AdventureState::Entering;
					UDMRecipeComponent* FoundRecipeComp = FindComponentByClass<UDMRecipeComponent>();
					if (FoundRecipeComp)
					{
						Order = FoundRecipeComp->GetRandomItemInfo(false); // new order
					}
					AIController->MoveToActor(point, 5.0f);
					OnAdventurerEntering.Broadcast();
				}
			}
		}
	}
	GetWorldTimerManager().SetTimer(TimerHandle_ShopTimer, this, &ADMAdventurer::AnnoyedState, DefaultWaitTime);
}

void ADMAdventurer::WaitingState()
{
	UE_LOG(LogTemp, Log, TEXT("====Adventurer waiting for order."));
	AdventureStateEnum = AdventureState::Waiting;
	OnAdventurerWaiting.Broadcast();
	GetWorldTimerManager().SetTimer(TimerHandle_RoamTimer, this, &ADMAdventurer::Roam, 7.0f);
}

void ADMAdventurer::AnnoyedState()
{
	UE_LOG(LogTemp, Log, TEXT("====Adventurer annoyed."));
	AdventureStateEnum = AdventureState::Annoyed;
	GetWorldTimerManager().SetTimer(TimerHandle_ShopTimer, this, &ADMAdventurer::MoveToExit, DefaultAnnoyedTime);
	OnAdventurerAnnoyed.Broadcast();
}

void ADMAdventurer::Roam()
{
	if (AdventureStateEnum == AdventureState::Waiting)
	{
		FNavLocation resultRdmLocation;
		UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (navSystem->GetRandomReachablePointInRadius(this->GetActorLocation(), 1000, resultRdmLocation, nullptr, nullptr))
		{
			ADMAIController* AIController = Cast<ADMAIController>(GetController());
			if (AIController)
			{
				UE_LOG(LogTemp, Log, TEXT("====Adventurer roams."));
				AIController->MoveToLocation(resultRdmLocation);
				GetWorldTimerManager().SetTimer(TimerHandle_RoamTimer, this, &ADMAdventurer::Roam, 7.0f);
			}
		}
	}
}

FText ADMAdventurer::GetAdventurerName() const
{
	FName RowName = AdventurerRowHandle.RowName;
	FDMAdventurerInfoRow* FoundAdventurerInfoRow = AdventurerRowHandle.DataTable->FindRow<FDMAdventurerInfoRow>(RowName, "");
	if (FoundAdventurerInfoRow)
	{
		return FoundAdventurerInfoRow->AdventurerDisplayName;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Adventurer Name Found"));
	}
	return FText::FromString(TEXT("Adventurer Name Here"));
}

TArray<FText> ADMAdventurer::GetDialog() const
{
	FName RowName = AdventurerRowHandle.RowName;
	FDMAdventurerInfoRow* FoundAdventurerInfoRow = AdventurerRowHandle.DataTable->FindRow<FDMAdventurerInfoRow>(RowName, "");
	TArray<FText> result;

	if (FoundAdventurerInfoRow)
	{
		result.Add(FoundAdventurerInfoRow->Dialog1);
		if (nInteractions >= 1)
		{
			result.Add(FoundAdventurerInfoRow->Dialog2);
		}
		if (nInteractions >= 2)
		{
			result.Add(FoundAdventurerInfoRow->Dialog3);
		}
	}

	return result;
}

bool ADMAdventurer::TryTurnInLegendary(UDMItemBase* LegendaryItem, OUT FText &outDialog)
{
	FName RowName = AdventurerRowHandle.RowName;
	FDMAdventurerInfoRow* FoundAdventurerInfoRow = AdventurerRowHandle.DataTable->FindRow<FDMAdventurerInfoRow>(RowName, "");
	if (LegendaryItem->ItemDisplayName == FoundAdventurerInfoRow->LegendaryItemName)
	{
		if (LegendaryItem->OwningInventory)
		{
			LegendaryItem->OwningInventory->RemoveItem(LegendaryItem);
		}
		outDialog = FoundAdventurerInfoRow->ThankYouDialog;
		OnLegendaryFound.Broadcast();
		nInteractions += 10;
		MoveToExit();
		return true;
	}
	outDialog = FText::FromString(TEXT("That's not the item I'm looking for."));
	return false;
}

bool ADMAdventurer::TryTurnInOrder(UDMItemBase* OrderedItem, OUT FText& outDialog)
{
	if (OrderedItem->ItemDisplayName == Order.ItemDisplayName)
	{
		if (OrderedItem->OwningInventory)
		{
			OrderedItem->OwningInventory->RemoveItem(OrderedItem);
		}
		outDialog = FText::FromString(TEXT("Thank you!"));
		nInteractions += 1;
		OnOrderFilled.Broadcast();
		MoveToExit();
		return true;
	}
	outDialog = FText::FromString(TEXT("That is not my order."));
	return false;
}


void ADMAdventurer::MoveToExit()
{
	ADMAIController* AIController = Cast<ADMAIController>(GetController());
	if (AIController)
	{
		for (AActor* point : Points)
		{
			if (point)
			{
				ADMTargetPoint* pointToMoveTo = Cast<ADMTargetPoint>(point);
				if (pointToMoveTo && pointToMoveTo->PointName == "Exit")
				{
					UE_LOG(LogTemp, Log, TEXT("====Adventurer exiting."));
					AdventureStateEnum = AdventureState::Exiting;
					AIController->MoveToActor(point, 5.0f);
					OnAdventurerExiting.Broadcast();
					GetWorldTimerManager().ClearTimer(TimerHandle_ShopTimer);
					GetWorldTimerManager().ClearTimer(TimerHandle_RoamTimer);
				}
			}
		}
	}
}

void ADMAdventurer::ExitShopState()
{
	for (AActor* point : Points)
	{
		if (point)
		{
			ADMTargetPoint* pointToMoveTo = Cast<ADMTargetPoint>(point);
			if (pointToMoveTo && pointToMoveTo->PointName == "Holding")
			{
				UE_LOG(LogTemp, Log, TEXT("====Adventurer left shop."));
				AdventureStateEnum = AdventureState::InActive;
				//this->SetActorLocation(pointToMoveTo->GetActorLocation());
				OnAdventurerExited.Broadcast(this);
			}
		}
	}
}
