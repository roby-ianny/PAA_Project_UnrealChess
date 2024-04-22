// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class PAA_UNREALCHESS_API Chess_Direction
{
public:

	FVector2D DirectionVector;

	Chess_Direction();
	Chess_Direction(double deltax, double deltay);
	Chess_Direction operator+(const Chess_Direction& other) const;
	Chess_Direction operator*(int32 scale) const;
	~Chess_Direction();

};

// Direzioni predefinite per il movimento nella board
const static Chess_Direction Up = Chess_Direction(0, 1);
const static Chess_Direction Down = Chess_Direction(0, -1);
const static Chess_Direction Left = Chess_Direction(-1, 0);
const static Chess_Direction Right = Chess_Direction(1, 0);
// Direzioni per il movimento in diagonale
const static Chess_Direction UpRight = Up + Right;
const static Chess_Direction UpLeft = Up + Left;
const static Chess_Direction DownRight = Down + Right;
const static Chess_Direction DownLeft = Down + Left;