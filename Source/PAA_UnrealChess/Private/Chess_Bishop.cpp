// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Bishop.h"

TArray<TSharedPtr<Chess_Move>> AChess_Bishop::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
    TArray<TSharedPtr<Chess_Move>> Moves;
	for (FVector2D pos : MovePositionInDirs(frompos, Directions, GF))
		Moves.Add(MakeShared<Chess_NormalMove>(frompos, pos)); // the problem is here because I allocate an object and not a pointer to the object
	return Moves;
	
}
