// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Piece.h"
#include "Chess_King.generated.h"

/**
 * 
 */
UCLASS()
class PAA_UNREALCHESS_API AChess_King : public AChess_Piece
{
	GENERATED_BODY()

protected:

	inline static const TArray<Chess_Direction> Dirs = {
		Up, Down, Left,	Right,
		UpRight, UpLeft, DownLeft, DownRight };

	TArray<TSharedPtr<Chess_Move>> MovePositions(FVector2D frompos, AChess_GameField* GF);

public:
	virtual TArray<TSharedPtr<Chess_Move>> ComputeMoves(FVector2D frompos, AChess_GameField* GF) override;

	virtual bool CanCaptureOpponentKing(FVector2D frompos, AChess_GameField* GameField) override;

	AChess_King() { Type = EPieceType::KING; }
};
