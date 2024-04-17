// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Move.h"

Chess_Move::Chess_Move()
{
}

Chess_NormalMove::Chess_NormalMove(FVector2D From, FVector2D To)
{
	Type = EMoveType::Normal;
	FromPosition = From;
	ToPosition = To;
}
