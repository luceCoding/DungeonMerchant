// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMAdventurer.h"
#include "GameFramework/Actor.h"
#include "DMAdventurerManager.generated.h"

class USoundCue;
UCLASS()
class DUNGEONMERCHANT_API ADMAdventurerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADMAdventurerManager();

	UPROPERTY(EditDefaultsOnly, Category = "Nav")
		FVector WaitingLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Time")
		float DefaultSpawnTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Adventurer")
		TArray<TSubclassOf<ADMAdventurer>> AdventurersToSpawn;

	UFUNCTION(BlueprintCallable)
		void SpawnAdventurers();

	UFUNCTION(BlueprintCallable)
		void MoveAdventurerToSpawner();

	UPROPERTY(BlueprintReadOnly, Category = "Adventurer")
		TArray<ADMAdventurer*> InActiveAdventurers;

	UPROPERTY(BlueprintReadOnly, Category = "Adventurer")
		TArray<ADMAdventurer*> ActiveAdventurers;

	UFUNCTION()
	void OnAdventurerExited(ADMAdventurer* Adventurer);

	void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Time")
		FTimerHandle TimerHandle_SpawnTimer;

	DECLARE_DELEGATE(FTimerDelegate)
		FTimerDelegate TimerDel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
		USoundCue* EnterSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound)
		USoundCue* ExitSoundCue;

	UPROPERTY(BlueprintReadOnly)
		float Counter;
};
