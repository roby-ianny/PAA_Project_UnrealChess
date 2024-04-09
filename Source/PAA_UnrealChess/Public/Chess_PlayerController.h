// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Chess_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PAA_UNREALCHESS_API AChess_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
		AChess_PlayerController();

		//Input Mapping Context association
		UPROPERTY(EditAnywhere, Category = Input)
		UInputMappingContext* ChessContext;


		UPROPERTY(EditAnywhere, Category = Input)
		UInputAction* ClickAction;

		// void ClickOnGrid(); is correct for chess?

protected:
	// Overriding delle funzioni dell'engine
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
