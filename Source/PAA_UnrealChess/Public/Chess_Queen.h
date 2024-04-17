// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Piece.h"
#include "Chess_Queen.generated.h"

/**
 * 
 */
UCLASS()
class PAA_UNREALCHESS_API AChess_Queen : public AChess_Piece
{
	GENERATED_BODY()
public:
	virtual TArray<Chess_Move> ComputeMoves(FVector2D frompos, AChess_GameField* GF) override;
};
