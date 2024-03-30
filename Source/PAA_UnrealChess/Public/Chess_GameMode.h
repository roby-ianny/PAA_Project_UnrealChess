// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Chess_GameField.h"
#include "GameFramework/GameMode.h"
#include "Chess_GameMode.generated.h"

class AActor;

struct FPosition;

/**
 * 
 */

UCLASS()

class PAA_UNREALCHESS_API AChess_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	//tracks if the game is over
	bool IsGameOver;

	//array of player interfaces
	// TArray<Chess_PlayerInterface*> Players;
	// int32 CurrentPlayer
	
	// tracks the number of moves in order to signal a drawn game
	// int32 MoveCounter; //Maybe an array is better

	// Type safety for spawning the gamefield
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AChess_GameField> GameFieldClass;

	// field size, needed?

	// Reference to GameField object
	UPROPERTY(VisibleAnywhere)
		AChess_GameField* GField;

	// Casting of all the chess pieces, something like this
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> SignXActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> SignOActor;
	*/

	AChess_GameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// TODO
	/*
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// called at the start of the game
	void ChoosePlayerAndStartGame();

	// set the cell sign and the position 
	void SetCellSign(const int32 PlayerNumber, const FVector& SpawnPosition);

	// get the next player index
	int32 GetNextPlayer(int32 Player);

	// called at the end of the game turn
	void TurnNextPlayer(); //switcha tra un giocatore e un altro
	*/

};
