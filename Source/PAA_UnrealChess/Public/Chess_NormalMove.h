// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Move.h"
/**
 * 
 */

class PAA_UNREALCHESS_API Chess_NormalMove : public Chess_Move {
public:
	Chess_NormalMove(FVector2D FromPosition, FVector2D ToPosition);
	~Chess_NormalMove() = default;
};