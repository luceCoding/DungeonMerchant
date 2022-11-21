// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMInteractInterface.h"
#include "GameFramework/Actor.h"
#include "DMInteractableBase.generated.h"

UCLASS()
class DUNGEONMERCHANT_API ADMInteractableBase : public AActor, public IDMInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMInteractableBase();

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
};
