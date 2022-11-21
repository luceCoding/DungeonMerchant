// Fill out your copyright notice in the Description page of Project Settings.


#include "DMNPCBase.h"

// Sets default values
ADMNPCBase::ADMNPCBase()
{
	InteractDelay = 0.1f;
}

void ADMNPCBase::InteractStarted_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Interacted Started."));
	TimerDel.BindUFunction(this, FName("InteractDelayed_Implementation"), InstigatorPawn);
	//GetWorldTimerManager().SetTimer(TimerHandle_InteractDelayed, this, &ADMInteractableBase::InteractDelayed_Implementation, InteractDelay);
	GetWorldTimerManager().SetTimer(TimerHandle_InteractDelayed, TimerDel, InteractDelay, false);
}

void ADMNPCBase::InteractDelayed_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Interact Delayed."));
	Interact_Implementation(InstigatorPawn);
}

void ADMNPCBase::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Interacted."));
}

// Called when the game starts or when spawned
void ADMNPCBase::BeginPlay()
{
	Super::BeginPlay();
	ensure(InteractDelay != 0.0f); //Interact won't start if 0.0f
}

// Called to bind functionality to input
void ADMNPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

