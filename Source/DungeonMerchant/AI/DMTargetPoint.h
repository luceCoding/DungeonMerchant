// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "DMTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONMERCHANT_API ADMTargetPoint : public ATargetPoint
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FString PointName;
};
