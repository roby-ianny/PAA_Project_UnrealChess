// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Piece.h"
#include "Chess_Bishop.generated.h"

/**
 * 
 */

UCLASS()
class PAA_UNREALCHESS_API AChess_Bishop : public AChess_Piece
{
	GENERATED_BODY()

protected:
	inline static const TArray<Chess_Direction> Directions = { 
		UpRight, 
		UpLeft,
		DownLeft, 
		DownRight };

public:
	virtual TArray<Chess_Move*> ComputeMoves(FVector2D frompos, AChess_GameField* GF) override;

	AChess_Bishop(){Type = EPieceType::BISHOP;}
	
};
