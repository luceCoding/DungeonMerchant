// Fill out your copyright notice in the Description page of Project Settings.


#include "DMInteractionComponent.h"

#include "DMInteractInterface.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

// Sets default values for this component's properties
UDMInteractionComponent::UDMInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDMInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDMInteractionComponent::FindBestInteractable()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;

	//MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	MyOwner->GetInstigatorController()->GetPlayerViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);
	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	FocusedActor = nullptr; // Clear ref before refill

	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 0.0f);

		}
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<UDMInteractInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}
	//DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}


// Called every frame
void UDMInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());

	if (MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}

void UDMInteractionComponent::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("====Interact Fired."));
	if (FocusedActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No Focus Actor to interact.");
		return;
	}
	APawn* MyPawn = Cast<APawn>(GetOwner());
	IDMInteractInterface::Execute_InteractStarted(FocusedActor, MyPawn);
}