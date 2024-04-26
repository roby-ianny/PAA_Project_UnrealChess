// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Queen.h"

TArray<TSharedPtr<Chess_Move>> AChess_Queen::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
	TArray<TSharedPtr<Chess_Move>> Moves;
	for (FVector2D pos : MovePositionInDirs(frompos, Directions, GF))
		Moves.Add(MakeShared<Chess_NormalMove>(frompos, pos));
	return Moves;
}
