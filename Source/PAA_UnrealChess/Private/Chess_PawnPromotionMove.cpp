// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_PawnPromotionMove.h"
#include "Chess_GameField.h"

Chess_PawnPromotion::Chess_PawnPromotion(FVector2D from, FVector2D to, EPieceType type)
{
	Type = EMoveType::PawnPromotion;
	FromPosition = from;
	ToPosition = to;
	PromotionPiece = type;
};

void Chess_PawnPromotion::Execute(AChess_GameField* GF)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Executing Pawn Promotion");
	return;
	//picks the color of the piece
	// int32 color = GF->TileMap[FromPosition]->GetOccupyingPiece()->GetColor();
	// destroy the old piece
	// GF->TileMap[FromPosition]->GetOccupyingPiece()->SelfDestroy();
	//set the tile as empyìty
	// GF->TileMap[FromPosition]->SetEmptyTile();

	// Check if the tile is occupied (just need it because there is also pawn promotion and the move is set to be legal)
	/*
	if (GF->TileMap[ToPosition]->GetTileStatus() != ETileStatus::EMPTY) {
		GF->TileMap[ToPosition]->GetOccupyingPiece()->SelfDestroy();		// if the tile is occupied it's a capure move
		GF->TileMap[ToPosition]->SetEmptyTile();							// to have a consistent state
	}

	this->CreatePromotionPiece(GF, color); // create the new piec
	GF->TileMap[ToPosition]->GetOccupyingPiece()->SetHasMoved(true);
	*/
}

void Chess_PawnPromotion::SimulateMove(AChess_GameField* GameField, AChess_Piece* PieceToMove, AChess_Piece*& CapturedPiece, bool& oldhasmoved, bool undo)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "No simulation for pawn promotion");
	return;
	/* Do not simulate this move atm
	if (!undo) {
		// Remove the old tile reference to that piece and edit the tile status to empty
		GF->TileMap[FromPosition]->SetEmptyTile();
		// Handling the capture in case of capture
		// Check if the tile is occupied (just need it because there is also pawn promotion and the move is set to be legal)
		if (GF->TileMap[ToPosition]->GetTileStatus() != ETileStatus::EMPTY) {
			CapturedPiece = GF->TileMap[ToPosition]->GetOccupyingPiece();		// if the tile is occupied it's a capure move
			GF->TileMap[ToPosition]->SetEmptyTile();
		}
		else
			CapturedPiece = nullptr; //the tile is empty, no capture
		// get the old hasmoved value
		oldhasmoved = PieceToMove->GetHasMoved(); // get the old hasmoved value to set it back later

		GF->TileMap[ToPosition]->SetOccupyingPiece(PieceToMove);						// Sets the new occupying piece
	}
	else {
		// Sets the old tile reference 
		GF->TileMap[FromPosition]->SetOccupyingPiece(PieceToMove);
		// Puts back the captured piece in case of capture
		if (CapturedPiece != nullptr)
			GF->TileMap[ToPosition]->SetOccupyingPiece(CapturedPiece);
		else
			GF->TileMap[ToPosition]->SetEmptyTile();

		PieceToMove->SetHasMoved(oldhasmoved); // set the old hasmoved value
	}
	*/
}

void Chess_PawnPromotion::CreatePromotionPiece(AChess_GameField* GF, int32 color)
{
	bool isblack = (color == 1);
	
	switch (PromotionPiece)
	{
	case EPieceType::BISHOP:
		GF->SpawnPiece(GF->BishopClass, ToPosition.X, ToPosition.Y, isblack); 
		break;
	case EPieceType::ROOK:
		GF->SpawnPiece(GF->RookClass, ToPosition.X, ToPosition.Y, isblack);
		break;
	case EPieceType::KNIGHT:
		GF->SpawnPiece(GF->KnightClass, ToPosition.X, ToPosition.Y, isblack);
		break;
	default:
		GF->SpawnPiece(GF->QueenClass, ToPosition.X, ToPosition.Y, isblack);
		break;
	}
}
