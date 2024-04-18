// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Pawn.h"
#include "Chess_GameField.h"

bool AChess_Pawn::CanMoveTo(FVector2D pos, AChess_GameField* GF)
{
    return GF->IsInside(pos) && GF->IsEmpty(pos);
}

bool AChess_Pawn::CanCaptureAt(FVector2D pos, AChess_GameField* GF)
{
    // se la posizione non è valida o se non ci sono pezzi avversari
    if (!GF->IsInside(pos) || GF->IsEmpty(pos)) { 
        return false;
    }

    ETileStatus CheckOpponent = ETileStatus::EMPTY;

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

    return GF->TileMap[pos]->GetTileStatus() == CheckOpponent; 
}

void AChess_Pawn::SetDarkMaterial()
{
    StaticMeshComponent->SetMaterial(0, DarkVariant);
    color = 1;
    forward = Down;
}

TArray<Chess_Move> AChess_Pawn::ForwardMoves(FVector2D frompos, AChess_GameField* GF)
{
    FVector2D oneMovePos = frompos + forward.DirectionVector;
    TArray<Chess_Move> Moves;

    if (CanMoveTo(oneMovePos, GF)) {
        Moves.Add(Chess_NormalMove(frompos, oneMovePos));

        FVector2D twoMovePos = oneMovePos + forward.DirectionVector;

        if(!HasMoved && CanMoveTo(twoMovePos, GF)) {
			Moves.Add(Chess_NormalMove(frompos, twoMovePos));
		}
    }

    return Moves;
}

TArray<Chess_Move> AChess_Pawn::CaptureMoves(FVector2D frompos, AChess_GameField* GF)
{
    TArray<Chess_Move> Moves;

    FVector2D toposright = frompos + forward.DirectionVector + Right.DirectionVector;
    FVector2D toposleft = frompos + forward.DirectionVector + Left.DirectionVector;

    if (CanCaptureAt(toposright, GF)) {
        Moves.Add(Chess_NormalMove(frompos, toposright));
    }

    if (CanCaptureAt(toposleft, GF)) {
        Moves.Add(Chess_NormalMove(frompos, toposleft));
    }

    return Moves;
}

TArray<Chess_Move> AChess_Pawn::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
    TArray<Chess_Move> Moves;

    Moves.Append(ForwardMoves(frompos, GF));
    Moves.Append(CaptureMoves(frompos, GF));

    return Moves;
}