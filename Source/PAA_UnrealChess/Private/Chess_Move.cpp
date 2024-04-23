// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Move.h"
#include "Chess_GameField.h"

Chess_Move::Chess_Move()
{
	Type = EMoveType::None;
}

bool Chess_Move::IsLegal(AChess_GameField* GF)
{
	// pick all the necessary information
	AChess_Piece* MovingPiece = GF->TileMap[FromPosition]->GetOccupyingPiece();
	AChess_Piece* CapturedPiece = nullptr;
	bool firstmove;

	bool legal;
	// make the move (virtually)
	GF->ExecuteVirtualMove(MovingPiece, *this, CapturedPiece, firstmove);
	if (GF->IsInCheck(MovingPiece->GetColor()))
		legal = false;
	else
		legal = true;

	GF->ExecuteVirtualMove(MovingPiece, *this, CapturedPiece, firstmove, true);
	return legal;
}