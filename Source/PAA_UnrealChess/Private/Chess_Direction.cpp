// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Direction.h"

Chess_Direction::Chess_Direction()
{
}

Chess_Direction::Chess_Direction(int32 row, int32 col)
{
	DirectionVector = FVector2D(row, col);
}

Chess_Direction Chess_Direction::operator+(const Chess_Direction& other) const{
	return Chess_Direction(DirectionVector.X + other.DirectionVector.X, DirectionVector.Y + other.DirectionVector.Y);
}

Chess_Direction Chess_Direction::operator*(int32 scale) const
{
	return Chess_Direction(scale * DirectionVector.X, scale * DirectionVector.Y);
}

Chess_Direction::~Chess_Direction()
{
}
