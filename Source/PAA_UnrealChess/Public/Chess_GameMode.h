// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Chess_PlayerInterface.h"
#include "Chess_GameField.h"
#include "GameFramework/GameMode.h"
#include "Chess_GameMode.generated.h"

class AActor;
struct FPosition;

/**
 * 
 */

/*
UENUM()
enum class EEndReason : uint8
{
	CHECKMATE UMETA(DisplayName = "Checkmate"),
	STALEMATE UMETA(DisplayName = "Stalemate")
};
*/

UCLASS()

class PAA_UNREALCHESS_API AChess_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	//tracks if the game is over
	bool IsGameOver;

	//array of player interfaces
	TArray<IChess_PlayerInterface*> Players;

	//Index of the active player
	int32 CurrentPlayer;

	// endreason of the game (checkmate, stalemate, etc)
	// EEndReason EndReason;

	// tracks the number of moves in order to signal a drawn game
	// int32 MoveCounter; //Maybe an array is better

	// Type safety for spawning the gamefield
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_GameField> GameFieldClass;

	// Reference to GameField object
	UPROPERTY(VisibleAnywhere)
	AChess_GameField* GField;

	AChess_GameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// called at the start of the game
	void ChoosePlayerAndStartGame();

	// executes a move, abstract = true, does not fisically move the piece, if doMove is false = it does the inverse move
	void ExecuteMove(Chess_Move*& Move);

	// get the next player index
	int32 GetNextPlayer(int32 Player);

	// called at the end of the game turn
	void TurnNextPlayer(); //switcha tra un giocatore e un altro

	// filters all the illegal moves
	void FilterLegalMoves(TArray<Chess_Move*> Moves);

	TArray <Chess_Move*> GetAllPlayerMoves(int32 player);

	void CheckForGameOver();
};
