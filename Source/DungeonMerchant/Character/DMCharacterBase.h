// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DMCharacterBase.generated.h"

UCLASS()
class DUNGEONMERCHANT_API ADMCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADMCharacterBase();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Items")
		void DropItem(class UDMItemBase* ItemToDrop);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
