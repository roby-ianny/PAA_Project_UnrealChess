// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Move.h"

//forward declaration for piece type needed for pawn promotion
enum class EPieceType : uint8;

/**
 * 
 */
class PAA_UNREALCHESS_API Chess_PawnPromotion : public Chess_Move
{
public:
	EPieceType PromotionPiece;

	Chess_PawnPromotion(FVector2D from, FVector2D to, EPieceType type);

	~Chess_PawnPromotion() = default;

	virtual void Execute(AChess_GameField* GF) override;

	virtual void SimulateMove(AChess_GameField* GameField, AChess_Piece* PieceToMove, AChess_Piece*& CapturedPiece, bool& oldhasmoved, bool undo = false) override;
private:
	void CreatePromotionPiece(AChess_GameField* GF, int32 color);
};
