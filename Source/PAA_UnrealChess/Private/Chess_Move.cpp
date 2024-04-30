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
	SimulateMove(GF, MovingPiece, CapturedPiece, firstmove);
	if (GF->IsInCheck(MovingPiece->GetColor()))
		legal = false;
	else
		legal = true;

	SimulateMove(GF,MovingPiece, CapturedPiece, firstmove, true);
	return legal;
}

FPiecesOfMove Chess_Move::Execute(AChess_GameField* GF)
{
	AChess_Piece* Piece = GF->TileMap[FromPosition]->GetOccupyingPiece();
	AChess_Piece* CapturedPiece = nullptr;
	// Set that the piece has moved in case it's false
	if (!Piece->GetHasMoved())
		Piece->SetHasMoved(true);
	// Remove the old tile reference to that piece and edit the tile status to empty
	GF->TileMap[FromPosition]->SetEmptyTile();
	// Handling the capture in case of capture
	// Check if the tile is occupied (just need it because there is also pawn promotion and the move is set to be legal)
	if (GF->TileMap[ToPosition]->GetTileStatus() != ETileStatus::EMPTY) {
		CapturedPiece = GF->TileMap[ToPosition]->GetOccupyingPiece();		// if the tile is occupied it's a capure move
		GF->TileMap[ToPosition]->GetOccupyingPiece()->Captured();		
		GF->TileMap[ToPosition]->SetEmptyTile();							// to have a consistent state
	}

	// Set the actor location of the piece
	FVector NewPosition = GF->GetRelativeLocationByXYPosition(ToPosition.X, ToPosition.Y);
	NewPosition.Z += 1;	//vertical offset to avoid collisions
	// I have to add vertical offset to avoid collisions

	Piece->SetActorLocationAndRotation(NewPosition, FRotator::ZeroRotator);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Piece Moved!"));
	// Edit the tile status to occupied by the new piece and add the reference
	GF->TileMap[ToPosition]->SetOccupyingPiece(Piece);			// Sets the new occupying piece

	FPiecesOfMove Pieces = { Piece, CapturedPiece };
	return Pieces;
}

EPieceType Chess_Move::GetPromotionPiece()
{
	return EPieceType::NONE;
}

void Chess_Move::SimulateMove(AChess_GameField* GF, AChess_Piece* PieceToMove, AChess_Piece*& CapturedPiece, bool& oldhasmoved, bool undo)
{
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
}

bool Chess_Move::operator==(const Chess_Move& other) const
{
	if ((this->FromPosition == other.FromPosition) && (this->ToPosition == other.ToPosition) && (this->Type == other.Type)) {
		return true;
	}
	else
		return false;
}
