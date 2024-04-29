// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Pawn.h"
#include "Blueprint/UserWidget.h"
#include "PPWidget.generated.h"

class AChess_GameMode;
/**
 * 
 */
UCLASS()
class PAA_UNREALCHESS_API UChess_PPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	EPieceType GetSelectedPiece() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectedPiece(EPieceType Piece);

	void SetFromTo(const FVector2D FromPos, const FVector2D ToPos);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	EPieceType PieceSelected = EPieceType::NONE;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FVector2D From;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FVector2D To;

	
};
