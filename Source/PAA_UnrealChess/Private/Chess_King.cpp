// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_King.h"
#include "Chess_GameField.h"


TArray<TSharedPtr<Chess_Move>> AChess_King::MovePositions(FVector2D frompos, AChess_GameField* GF)
{
	ETileStatus CheckOpponent;

	TArray<TSharedPtr<Chess_Move>> Moves;

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
			Moves.Add(MakeShared<Chess_NormalMove>(frompos, pos));
		}
	}

	return Moves;
}

TArray<TSharedPtr<Chess_Move>> AChess_King::ComputeMoves(FVector2D frompos, AChess_GameField* GF){
	return MovePositions(frompos, GF);
}

bool AChess_King::CanCaptureOpponentKing(FVector2D frompos, AChess_GameField* GameField)
{
	// Needed in case you want to add castling moves
	for (TSharedPtr<Chess_Move>& Move : ComputeMoves(frompos, GameField)) {
		FVector2D topos = Move->ToPosition;
		//checks if the tile is empty, it's more efficent to do this because it skips all the empty tiles (idk if it's a short circuit evaluation so i do it this way)
		if (GameField->TileMap[topos]->GetTileStatus() != ETileStatus::EMPTY) {
			//checks if the piece on the tile is a king
			if (GameField->TileMap[topos]->GetOccupyingPiece()->GetType() == EPieceType::KING)
				return true;
		}
	}
	return false;
}
