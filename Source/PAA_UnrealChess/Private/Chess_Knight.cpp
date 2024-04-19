// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Knight.h"
#include "Chess_GameField.h"

TArray<FVector2D> AChess_Knight::PotentialPositions(FVector2D frompos)
{
	TArray <FVector2D> positions;
	// first loop for up and down directions
	for (Chess_Direction verDir : TArray<Chess_Direction> {Up, Down})
	{
		for (Chess_Direction orDir : TArray<Chess_Direction> {Left, Right})
		{
			 positions.Emplace(frompos + 2 * verDir.DirectionVector + orDir.DirectionVector);
			 positions.Emplace(frompos + verDir.DirectionVector + 2 * orDir.DirectionVector);
		}
	}

	return positions;
}

TArray<FVector2D> AChess_Knight::MovePositions(FVector2D frompos, AChess_GameField* GF)
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

	TArray<FVector2D> legalpositions;

	for (FVector2D pos : PotentialPositions(frompos))
	{

		if (GF->IsInside(pos) && // If I am in the gamefield
			(GF->IsEmpty(pos) || GF->TileMap[pos]->GetTileStatus() == CheckOpponent)) //If the position is free or if i can catch
		{
			legalpositions.Emplace(pos); // so it's a legal position
		}
	}

	return legalpositions;
}

TArray<Chess_Move> AChess_Knight::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
	TArray<Chess_Move> Moves;

	for (FVector2D pos : MovePositions(frompos, GF)) // for each position in collection_to_loop)
	{
		Moves.Emplace(Chess_NormalMove(frompos, pos));
	}

	return Moves;
}
