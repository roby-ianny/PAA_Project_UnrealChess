// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Direction.h"
#include "Chess_Tile.h"
#include "GameFramework/Actor.h"
// This includes all the pieces and the associated includes
#include "Chess_Pawn.h" 
#include "Chess_Rook.h"
#include "Chess_Bishop.h"
#include "Chess_Knight.h"
#include "Chess_Queen.h"
#include "Chess_King.h"
#include "Chess_GameField.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset); // Servirà quando ci sarà l'evento di reset

UCLASS()
class PAA_UNREALCHESS_API AChess_GameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Array delle tiles
	UPROPERTY(Transient)
	TArray<AChess_Tile*> TileArray;

	// Data una posizione mi restituisce il puntatore ad una tile
	UPROPERTY(Transient)
	TMap<FVector2D, AChess_Tile*> TileMap;

	static const int32 NOT_ASSIGNED = -1;

	// Setting OnResetEvent call 
	UPROPERTY(BlueprintAssignable)
	FOnReset OnResetEvent;

	// Dimensionni della scacchiera
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_Tile> TileClass;

	// Also type safety is needed for the pieces
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_Pawn> PawnClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_Rook> RookClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_Bishop> BishopClass;
		
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_Knight> KnightClass;
		
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_Queen> QueenClass;
		
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChess_King> KingClass;

	//tile size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	// Sets default values for this actor's properties
	AChess_GameField();

	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Remove all pieces from the field
	UFUNCTION(BlueprintCallable)
	void ResetField();

	// Generate an empty game field
	void GenerateField();

	// spawn a single piece (useful also for pawn promotion)
	void SpawnPiece(TSubclassOf<AChess_Piece> PieceClass, int32 XPosition, int32 YPosition, bool black);

	// spawn the pieces (useful also when resetting)
	void SpawnPieces();

	//Return a (x,y) position after clicking on a field tile
	FVector2D GetPosition(const FHitResult& Hit);

	//Return the array of tile pointers
	TArray<AChess_Tile*>& GetTileArray();

	// return a relative position given (x,y) position
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	// return (x,y) given a relative position
	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;

	// return tile position from actual position and direction
	AChess_Tile* GetTileByPositionAndDirection(const FVector2D Position, const Chess_Direction Direction) const;

	// Checks if the position is inside the board
	bool IsInside(FVector2D position);

	// Checks if the tile il empty
	bool IsEmpty(FVector2D position);
	// Executes a Move?

	// Function to get all pieces of a color
	TArray<AChess_Tile*> GetTilesWithPlayerPieces(int32 color);

	void HighlightTiles(TArray<TSharedPtr<Chess_Move>> Moves, bool ToHighlight);

	void DeHighlightAll();

	bool IsInCheck(int32 playercolor);

	// virtual void ExecuteMove(Chess_Move Move);

	// virtual void ExecuteVirtualMove(AChess_Piece* PieceToMove, Chess_Move Move, AChess_Piece*& CapturedPiece, bool& oldhasmoved, bool undo = false);

/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
};

