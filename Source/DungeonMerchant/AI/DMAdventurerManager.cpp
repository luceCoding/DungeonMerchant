// Fill out your copyright notice in the Description page of Project Settings.


#include "DMAdventurerManager.h"

#include "DungeonMerchant/Crafting/DMCraftingStationBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ADMAdventurerManager::ADMAdventurerManager()
{
	DefaultSpawnTimer = 30.0f;
	Counter = 0.0f;
}

void ADMAdventurerManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ADMAdventurerManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnAdventurers();
	MoveAdventurerToSpawner();
}

void ADMAdventurerManager::SpawnAdventurers()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform transform = GetTransform();
	transform.SetLocation(WaitingLocation);
	for (TSubclassOf<ADMAdventurer> adv : AdventurersToSpawn)
	{
		ADMAdventurer* ActorRef = GetWorld()->SpawnActor<ADMAdventurer>(adv, transform, SpawnParams);
		if (ActorRef)
		{
			UE_LOG(LogTemp, Log, TEXT("====Adventurer spawned."));
			//ActorRef->SetActorEnableCollision(false);
			InActiveAdventurers.Add(ActorRef);
			ActorRef->OnAdventurerExited.AddUniqueDynamic(this, &ADMAdventurerManager::OnAdventurerExited);
		}
	}
}

void ADMAdventurerManager::MoveAdventurerToSpawner()
{
	auto idx = FMath::RandRange(0, InActiveAdventurers.Num()-1);
	if (InActiveAdventurers.Num())
	{
		// Play enter sound cue
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EnterSoundCue,
			GetActorLocation()
		);
		
		ADMAdventurer* adv = InActiveAdventurers[idx];
		adv->SetActorLocation(this->GetActorLocation());
		adv->MoveToShop();
		//adv->SetActorEnableCollision(true);
		InActiveAdventurers.Remove(adv);
		ActiveAdventurers.Add(adv);
	}
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnTimer, this, &ADMAdventurerManager::MoveAdventurerToSpawner, FMath::Clamp(DefaultSpawnTimer - Counter, 10.0f, 45.0f));
}

void ADMAdventurerManager::OnAdventurerExited(ADMAdventurer* Adventurer)
{
	if (Adventurer)
	{
		// Play exit sound cue
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ExitSoundCue,
			GetActorLocation()
		);

		ActiveAdventurers.Remove(Adventurer);

		if (ActiveAdventurers.Num() == 0)
		{
			MoveAdventurerToSpawner();
		}

		UE_LOG(LogTemp, Log, TEXT("====Moving adventurer to holding."));
		Adventurer->SetActorLocation(WaitingLocation);
		Counter += 1;
		if (Adventurer->nInteractions < 10)
		{
			InActiveAdventurers.Add(Adventurer);
		}
	}
}