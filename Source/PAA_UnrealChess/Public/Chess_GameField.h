// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Tile.h"
#include "GameFramework/Actor.h"
#include "Chess_Pawn.h"
#include "Chess_Rook.h"
#include "Chess_Bishop.h"
#include "Chess_Knight.h"
#include "Chess_Queen.h"
#include "Chess_King.h"
#include "Chess_GameField.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset); // Servir� quando ci sar� l'evento di reset

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

	/* Visto nel progetto del tris, a me non interessa il padding, lo metto nel caso volessi inserirlo in futuro
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NormalizedCellPadding;
	*/

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
	FVector2D getPosition(const FHitResult& Hit);

	//Return the array of tile pointers
	TArray<AChess_Tile*>& getTileArray();

	// return a relative position given (x,y) position
	FVector getRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	// return (x,y) given a relative position
	FVector2D getXYPositionByRelativeLocation(const FVector& Location) const;

	// check if a position is a win position
	// bool IsWinPosition(const FVector2D Position) const; //Not needed now

	// checking if is a valid field position
	// inline bool IsValidPosition(const FVector2D Position) const; //Not needed now

	// get a line given a begin and end positions
	// TArray<int32> GetLine(const FVector2D Begin, const FVector2D End) const; maybe needed for rook and bishop

/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
};
