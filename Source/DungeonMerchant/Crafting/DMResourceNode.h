// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonMerchant/Interaction/DMInteractableBase.h"
#include "DungeonMerchant/Item/DMItemBase.h"
#include "DMResourceNode.generated.h"

UCLASS()
class DUNGEONMERCHANT_API ADMResourceNode : public ADMInteractableBase 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMResourceNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced, Category = "Item")
		UDMItemBase* DefaultResource;

	UFUNCTION(BlueprintCallable)
	void Interact_Implementation(APawn* InstigatorPawn) override;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
