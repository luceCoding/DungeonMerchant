// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "DungeonMerchant/Interaction/DMInteractionComponent.h"
#include "DungeonMerchant/Inventory/DMInventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DMMerchant.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONMERCHANT_API ADMMerchant : public ADMCharacterBase
{
	GENERATED_BODY()

public:

	ADMMerchant();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
		UDMInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UDMInventoryComponent* InventoryComp;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void Interact();
};
