// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Direction.h"

Chess_Direction::Chess_Direction()
{
}

Chess_Direction::Chess_Direction(double deltax, double deltay)
{
	DirectionVector = FVector2D(deltax, deltay);
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
