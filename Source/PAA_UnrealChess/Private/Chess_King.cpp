// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_King.h"
#include "Chess_GameField.h"

TArray<FVector2D> AChess_King::MovePositions(FVector2D frompos, AChess_GameField* GF)
{
	ETileStatus CheckOpponent;

	switch (color)
	{
	case 0:
		CheckOpponent = ETileStatus::OCCUPIEDBLACK;
		break;
	case 1:
		CheckOpponent = ETileStatus::OCCUPIEDWHITE;
		break;
	default: // if we get here there is an error
		CheckOpponent = ETileStatus::EMPTY;
		break;
	}

    TArray<FVector2D> positions;

    for (Chess_Direction dir : Directions) {
		FVector2D pos = frompos + dir.DirectionVector;

		if(!GF->IsInside(pos))
			continue;

		if (GF->IsEmpty(pos) || GF->TileMap[pos]->GetTileStatus() == CheckOpponent)
		{
			positions.Emplace(pos);
		}
    }

    return positions;
}

TArray<Chess_Move> AChess_King::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
	TArray<Chess_Move> Moves;
	for (FVector2D topos : MovePositions(frompos, GF)) {
		Moves.Emplace(Chess_NormalMove(frompos, topos));
	}

	return Moves;
}
