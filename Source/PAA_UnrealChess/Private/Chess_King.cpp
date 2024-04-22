// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_King.h"
#include "Chess_GameField.h"


TArray<Chess_Move> AChess_King::MovePositions(FVector2D frompos, AChess_GameField* GF)
{
	ETileStatus CheckOpponent;

	TArray<Chess_Move> moves;

	switch (this->GetColor()) {
	case 0:
		CheckOpponent = ETileStatus::OCCUPIEDBLACK;
		break;
	case 1:
		CheckOpponent = ETileStatus::OCCUPIEDWHITE;
		break;
	default:
		CheckOpponent = ETileStatus::EMPTY;
		break;
	}

	for (Chess_Direction dir : Dirs) {
		
		FVector2D pos = frompos + dir.DirectionVector;

		if (!GF->IsInside(pos)) {
			continue;
		}

		if (GF->IsEmpty(pos) || (GF->TileMap[pos]->GetTileStatus() == CheckOpponent))
		{
			moves.Add(Chess_NormalMove(frompos, pos));
		}
	}

	return moves;
}

TArray<Chess_Move> AChess_King::ComputeMoves(FVector2D frompos, AChess_GameField* GF){
	return MovePositions(frompos, GF);
}
