// Fill out your copyright notice in the Description page of Project Settings.


#include "DMAIController.h"

#include "DMAdventurer.h"

void ADMAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	ADMAdventurer* Adventurer = Cast<ADMAdventurer>(GetPawn());
	if (Adventurer)
	{
		switch (Adventurer->AdventureStateEnum)
		{
			case AdventureState::Entering:
				Adventurer->WaitingState();
				break;
			case AdventureState::Exiting:
				Adventurer->ExitShopState();
				break;
			default: break;
		}
	}
}
