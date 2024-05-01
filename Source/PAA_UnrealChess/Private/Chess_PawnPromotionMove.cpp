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

FPiecesOfMove Chess_PawnPromotion::Execute(AChess_GameField* GF)
{
	AChess_Piece* PieceToMove;
	AChess_Piece* CapturedPiece = nullptr;

	//picks the color of the piece
	int32 color = GF->TileMap[FromPosition]->GetOccupyingPiece()->GetColor();

	PieceToMove = GF->TileMap[FromPosition]->GetOccupyingPiece();
	PieceToMove->Captured(); // hides the old piece
	// destroy the old piece
	// GF->TileMap[FromPosition]->GetOccupyingPiece()->Captured();
	//set the tile as empyìty
	GF->TileMap[FromPosition]->SetEmptyTile();

	// Check if the tile is occupied (becase a pawn promotion can also have a capture)
	if (GF->TileMap[ToPosition]->GetTileStatus() != ETileStatus::EMPTY) {
		CapturedPiece = GF->TileMap[ToPosition]->GetOccupyingPiece();
		GF->TileMap[ToPosition]->GetOccupyingPiece()->Captured();		// if the tile is occupied it's a capure move
		GF->TileMap[ToPosition]->SetEmptyTile();							// to have a consistent state
	}
	
	this->CreatePromotionPiece(GF, color); // create the new piec
	GF->TileMap[ToPosition]->GetOccupyingPiece()->SetHasMoved(true);

	FPiecesOfMove Pieces = { PieceToMove, CapturedPiece };
	return Pieces;
}

void Chess_PawnPromotion::SimulateMove(AChess_GameField* GF, AChess_Piece* PieceToMove, AChess_Piece*& CapturedPiece, bool& oldhasmoved, bool undo)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "No simulation for pawn promotion");
	
	
	if (!undo) {
		//picks the color of the piece
		int32 color = GF->TileMap[FromPosition]->GetOccupyingPiece()->GetColor();

		PieceToMove = GF->TileMap[FromPosition]->GetOccupyingPiece();
		// PieceToMove->Captured();
		GF->TileMap[FromPosition]->SetEmptyTile();

		// Check if the tile is occupied (becase a pawn promotion can also have a capture)
		if (GF->TileMap[ToPosition]->GetTileStatus() != ETileStatus::EMPTY) {
			CapturedPiece = GF->TileMap[ToPosition]->GetOccupyingPiece();	// if the tile is occupied it's a capure move
			GF->TileMap[ToPosition]->SetEmptyTile();							// simulates the capture setting the tile as empty
		}

		this->CreatePromotionPiece(GF, color, true);						// executes the promotion but hides the new piece
		GF->TileMap[ToPosition]->GetOccupyingPiece()->SetHasMoved(true);	// Sets the new occupying piece
	}
	else {
		//put back the pawn
		GF->TileMap[FromPosition]->SetOccupyingPiece(PieceToMove);
		// Destroy the promoted piece
		GF->TileMap[ToPosition]->GetOccupyingPiece()->SelfDestroy();
		// put back the captured piece in case of capture
		if (CapturedPiece != nullptr)
			GF->TileMap[ToPosition]->SetOccupyingPiece(CapturedPiece);
		else
			GF->TileMap[ToPosition]->SetEmptyTile();

		PieceToMove->SetHasMoved(oldhasmoved); // set the old hasmoved value
	}
}

EPieceType Chess_PawnPromotion::GetPromotionPiece()
{
	return PromotionPiece;
}

void Chess_PawnPromotion::Undo(AChess_GameField* GF, AChess_Piece* MovedPiece, AChess_Piece* CapturedPiece)
{
	// Destroy the promotion piece
	GF->TileMap[ToPosition]->GetOccupyingPiece()->SelfDestroy();

	// Put back the moved piece
	GF->TileMap[FromPosition]->SetOccupyingPiece(MovedPiece);
	FVector OldPosition = GF->GetRelativeLocationByXYPosition(FromPosition.X, FromPosition.Y);
	OldPosition.Z += 1;	//vertical offset to avoid collisions
	MovedPiece->SetActorLocationAndRotation(OldPosition, FRotator::ZeroRotator);
	
	//Puts back the captured piece
	if (CapturedPiece != nullptr) {
		GF->TileMap[ToPosition]->SetOccupyingPiece(CapturedPiece);
		OldPosition = GF->GetRelativeLocationByXYPosition(ToPosition.X, ToPosition.Y);
		OldPosition.Z += 1;
		CapturedPiece->SetActorLocationAndRotation(OldPosition, FRotator::ZeroRotator);
	}
	else
		GF->TileMap[ToPosition]->SetEmptyTile();
}

void Chess_PawnPromotion::CreatePromotionPiece(AChess_GameField* GF, int32 color, bool hidden)
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

	if (hidden)
		GF->TileMap[ToPosition]->GetOccupyingPiece()->Captured();
}
