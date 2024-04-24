// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "Chess_GameField.h"

class AChess_GameField;
class AChess_Piece;

/**
 * 
 */

UENUM()
enum class EMoveType : uint8
{
	None,		
	Normal,
	PawnPromotion,
	DowblePawn,
	/* not required for the minimum specifications, may be used in future
	CatleKS,
	CastleQS,
	EnPassant,
	*/
};

class PAA_UNREALCHESS_API Chess_Move
{
public:
	EMoveType Type;
	FVector2D FromPosition;
	FVector2D ToPosition;

	// virtual void Execute(AChess_GameField* GF); meglio farlo fare direttamente la gamefield

	Chess_Move();
	~Chess_Move() = default; //provo ad appoggiarmi al distruttore di default

	virtual bool IsLegal(AChess_GameField* GF);

	// in this way the move is made by the gamefield but this method can be overriden for specific moves like castling, pawn promotion etc.
	virtual void Execute(AChess_GameField* GF);

	/*
	  PieceToMove is the piece to effectively move
	  Move is the move to do/undo
	  undo = true -> undo the move, undo = false -> do the move
	  CapturedPiece in case of do is needed to save the captured piece for later, in case of undo it places back the captured piece
	*/
	virtual void SimulateMove(AChess_GameField* GameField, AChess_Piece* PieceToMove, AChess_Piece*& CapturedPiece, bool& oldhasmoved, bool undo = false);
};


