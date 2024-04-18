// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Piece.h"
#include "Chess_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class PAA_UNREALCHESS_API AChess_Pawn : public AChess_Piece
{
	GENERATED_BODY()
protected:
	Chess_Direction forward = Up;

	static bool CanMoveTo(FVector2D pos, AChess_GameField* GF);

	bool CanCaptureAt(FVector2D pos, AChess_GameField* GF);

	TArray<Chess_Move> ForwardMoves(FVector2D frompos, AChess_GameField* GF);

	TArray<Chess_Move> CaptureMoves(FVector2D frompos, AChess_GameField* GF);

public:
	virtual TArray<Chess_Move> ComputeMoves(FVector2D frompos, AChess_GameField* GF) override;

	virtual void SetDarkMaterial() override;
};
