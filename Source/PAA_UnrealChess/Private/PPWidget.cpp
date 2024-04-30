// Fill out your copyright notice in the Description page of Project Settings.

#include "PPWidget.h"
#include "Chess_GameMode.h"



EPieceType UChess_PPWidget::GetSelectedPiece() const
{
	return PieceSelected;
}

void UChess_PPWidget::SetSelectedPiece(EPieceType Piece)
{
	PieceSelected = Piece;
}

void UChess_PPWidget::SetFromTo(const FVector2D FromPos, const FVector2D ToPos)
{
	From = FromPos;
	To = ToPos;
}

