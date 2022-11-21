// Fill out your copyright notice in the Description page of Project Settings.


#include "DMCharacterBase.h"

#include "DungeonMerchant/Item/DMItemBase.h"

// Sets default values
ADMCharacterBase::ADMCharacterBase()
{
}

// Called when the game starts or when spawned
void ADMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ADMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADMCharacterBase::DropItem(UDMItemBase* ItemToDrop)
{
	if (ItemToDrop)
	{
		ItemToDrop->DropItem(this);
		ItemToDrop->OnDropItem(this); // BP event
	}
}

