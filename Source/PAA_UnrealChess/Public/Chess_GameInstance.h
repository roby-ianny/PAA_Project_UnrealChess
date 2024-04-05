// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Chess_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PAA_UNREALCHESS_API UChess_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere)
		FString CurrentTurnMessage = "Current Player";


		UFUNCTION(BlueprintCallable)
		FString SetTurnMessage();
};
