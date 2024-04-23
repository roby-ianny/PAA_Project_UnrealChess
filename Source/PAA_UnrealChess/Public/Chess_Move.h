// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "Chess_GameField.h"

class AChess_GameField;

/**
 * 
 */

UENUM()
enum class EMoveType : uint8
{
	None,
	Normal,
	PawnPromotion,
	DowblePawn,
	/* not required for the minimum specifications, may be used in future
	CatleKS,
	CastleQS,
	EnPassant,
	*/
};

class PAA_UNREALCHESS_API Chess_Move
{
public:
	EMoveType Type;
	FVector2D FromPosition;
	FVector2D ToPosition;

	// virtual void Execute(AChess_GameField* GF); meglio farlo fare direttamente la gamefield

	Chess_Move();
	~Chess_Move() = default; //provo ad appoggiarmi al distruttore di default

	virtual bool IsLegal(AChess_GameField* GF);
};


