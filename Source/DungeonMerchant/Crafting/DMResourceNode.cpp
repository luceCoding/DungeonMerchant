// Fill out your copyright notice in the Description page of Project Settings.


#include "DMResourceNode.h"

// Sets default values
ADMResourceNode::ADMResourceNode()
{
	InteractDelay = 1.0f;
}

// Called when the game starts or when spawned
void ADMResourceNode::BeginPlay()
{
	Super::BeginPlay();
	ensure(DefaultResource);
}

void ADMResourceNode::Interact_Implementation(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("====Resource Node Interacted."));
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); //TODO: Get owning player instead
	UDMInventoryComponent* InvComp = Cast<UDMInventoryComponent>(PlayerPawn->GetComponentByClass(UDMInventoryComponent::StaticClass()));
	if (InvComp)
	{
		UDMItemBase* NewResource = DuplicateObject(DefaultResource, GetWorld());
		InvComp->AddItem(NewResource);
	}
}