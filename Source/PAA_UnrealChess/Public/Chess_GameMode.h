// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Chess_PlayerInterface.h"
#include "Chess_GameField.h"
#include "GameFramework/GameMode.h"
#include "PPWidget.h"

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


USTRUCT()
struct FRegisteredMove
{
	GENERATED_BODY()
	TSharedPtr<Chess_Move> Move;
	FPiecesOfMove Pieces;
	char CheckState = ' ';
};

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
	void ExecuteMove(TSharedPtr<Chess_Move>& Move);

	UFUNCTION(BlueprintCallable)
	void ExecutePawnPromotion(FVector2D FromPost, FVector2D ToPos, EPieceType PromotionType);
	// get the next player index
	int32 GetNextPlayer(int32 Player);

	// called at the end of the game turn
	void TurnNextPlayer(); //switcha tra un giocatore e un altro

	// filters all the illegal moves
	void FilterLegalMoves(TArray<TSharedPtr<Chess_Move>>& Moves);

	TArray <TSharedPtr<Chess_Move>> GetAllPlayerMoves(int32 player);

	void CheckForGameOver();

	void PawnPromotionSelection(TSharedPtr<Chess_Move> MoveToExecute);

	FString MoveToChessNotation(int32 MoveIndex);
	
	UFUNCTION(BlueprintCallable)
	FString LatestMoveToChessNotation();

	TArray<FString> LatestMovesToChessNotation(int32 NumMoves);

	UFUNCTION(BlueprintNativeEvent)
	void AddToMoveHistory();

	UFUNCTION(BlueprintCallable)
	int32 GetLastMoveIndex();

	void AddToMoveHistory_Implementation();

	UFUNCTION(BlueprintCallable)
	void GoToOldState(int32 index);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UChess_PPWidget> PPWidget;

	TArray<FRegisteredMove> MoveHistory;

	void UndoLastMove();

	UFUNCTION()
	FString FromGridPositionToChessNotation(FVector2D GridPosition);

	UFUNCTION()
	FString FromChessPieceToChessNotation(AChess_Piece* Piece);
};
