// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Piece.h"
#include "Chess_Knight.generated.h"

/**
 * 
 */

UCLASS()
class PAA_UNREALCHESS_API AChess_Knight : public AChess_Piece
{
	GENERATED_BODY()

protected:
	static TArray<FVector2D> PotentialPositions(FVector2D frompos);

	TArray<Chess_Move> MovePositions(FVector2D frompos, AChess_GameField* GF);

public:

	virtual TArray<Chess_Move> ComputeMoves(FVector2D frompos, AChess_GameField* GF) override;
};
