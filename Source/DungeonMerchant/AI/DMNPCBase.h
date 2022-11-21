// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonMerchant/Interaction/DMInteractInterface.h"
#include "GameFramework/Character.h"
#include "DMNPCBase.generated.h"

UCLASS()
class DUNGEONMERCHANT_API ADMNPCBase : public ACharacter, public IDMInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADMNPCBase();

	UFUNCTION(BlueprintCallable)
		void InteractStarted_Implementation(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable)
		void InteractDelayed_Implementation(APawn* InstigatorPawn);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Interact(APawn* InstigatorPawn); // Interweave your code here.

	UPROPERTY(BlueprintReadWrite, Category = "Time")
		FTimerHandle TimerHandle_InteractDelayed;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
		float InteractDelay;

	DECLARE_DELEGATE(FTimerDelegate)
		FTimerDelegate TimerDel;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
