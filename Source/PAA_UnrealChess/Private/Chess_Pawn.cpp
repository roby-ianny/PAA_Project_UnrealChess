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

bool AChess_Pawn::CanCaptureOpponentKing(FVector2D frompos, AChess_GameField* GameField)
{
    for (TSharedPtr<Chess_Move>& Move : CaptureMoves(frompos, GameField)) {
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

TArray<TSharedPtr<Chess_Move>> AChess_Pawn::ForwardMoves(FVector2D frompos, AChess_GameField* GF)
{
    FVector2D oneMovePos = frompos + forward.DirectionVector;
    TArray<TSharedPtr<Chess_Move>> Moves;

    if (CanMoveTo(oneMovePos, GF)) {

        if (oneMovePos.Y == 0 || oneMovePos.Y == 7) {
            Moves.Append(PromotionMoves(frompos, oneMovePos));
        }
        else
            Moves.Add(MakeShared<Chess_NormalMove>(frompos, oneMovePos));

        FVector2D twoMovePos = oneMovePos + forward.DirectionVector;

        if(!HasMoved && CanMoveTo(twoMovePos, GF)) {
            Moves.Add(MakeShared<Chess_NormalMove>(frompos, twoMovePos));
		}
    }

    return Moves;
}

TArray<TSharedPtr<Chess_Move>> AChess_Pawn::CaptureMoves(FVector2D frompos, AChess_GameField* GF)
{
    TArray<TSharedPtr<Chess_Move>> Moves;

    FVector2D toposright = frompos + forward.DirectionVector + Right.DirectionVector;
    FVector2D toposleft = frompos + forward.DirectionVector + Left.DirectionVector;

    if (CanCaptureAt(toposright, GF)) {
        if (toposright.Y == 0 || toposright.Y == 7) {
            Moves.Append(PromotionMoves(frompos, toposright));
            // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You can promote a pawn! "));
        }
        else
            Moves.Add(MakeShared<Chess_NormalMove>(frompos, toposright));
    }

    if (CanCaptureAt(toposleft, GF)) {
        if (toposleft.Y == 0 || toposleft.Y == 7) {
            // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You can promote a pawn! "));
            Moves.Append(PromotionMoves(frompos, toposleft));
        } else
            Moves.Add(MakeShared<Chess_NormalMove>(frompos, toposleft));
    }

    return Moves;
}

TArray<TSharedPtr<Chess_Move>> AChess_Pawn::PromotionMoves(FVector2D frompos, FVector2D topos)
{
    TArray<TSharedPtr<Chess_Move>> Moves;
    Moves.Add(MakeShared<Chess_PawnPromotion>(frompos, topos, EPieceType::KNIGHT));
    Moves.Add(MakeShared<Chess_PawnPromotion>(frompos, topos, EPieceType::ROOK));
    Moves.Add(MakeShared<Chess_PawnPromotion>(frompos, topos, EPieceType::BISHOP));
    Moves.Add(MakeShared<Chess_PawnPromotion>(frompos, topos, EPieceType::QUEEN));
    // GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GeneratedPromotionMoves"));
    return Moves;
}

TArray<TSharedPtr<Chess_Move>> AChess_Pawn::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
    TArray<TSharedPtr<Chess_Move>> Moves;

    Moves.Append(ForwardMoves(frompos, GF));
    Moves.Append(CaptureMoves(frompos, GF));

    return Moves;
}