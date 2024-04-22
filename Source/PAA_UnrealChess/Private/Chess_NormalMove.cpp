// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_NormalMove.h"

Chess_NormalMove::Chess_NormalMove(FVector2D From, FVector2D To)
{
	FromPosition = From;
	ToPosition = To;
	Type = EMoveType::Normal;
};
