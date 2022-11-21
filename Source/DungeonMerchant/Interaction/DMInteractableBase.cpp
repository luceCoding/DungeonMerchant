// Fill out your copyright notice in the Description page of Project Settings.


#include "DMInteractableBase.h"

// Sets default values
ADMInteractableBase::ADMInteractableBase()
{
	InteractDelay = 0.1f;
}

void ADMInteractableBase::InteractStarted_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Interacted Started."));
	TimerDel.BindUFunction(this, FName("InteractDelayed_Implementation"), InstigatorPawn);
	//GetWorldTimerManager().SetTimer(TimerHandle_InteractDelayed, this, &ADMInteractableBase::InteractDelayed_Implementation, InteractDelay);
	GetWorldTimerManager().SetTimer(TimerHandle_InteractDelayed, TimerDel, InteractDelay, false);
}


void ADMInteractableBase::InteractDelayed_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Interact Delayed."));
	Interact_Implementation(InstigatorPawn);
}

void ADMInteractableBase::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Interacted."));
}

// Called when the game starts or when spawned
void ADMInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	ensure(InteractDelay != 0.0f); //Interact won't start if 0.0f
}

