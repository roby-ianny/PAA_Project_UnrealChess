// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chess_Piece.h" 
#include "Chess_Tile.generated.h"

UENUM()
enum class ETileStatus : uint8
{
	EMPTY UMETA(DisplayName = "Empty"),
	OCCUPIEDBLACK UMETA(DisplayName = "Occupied by Black Piece"),
	OCCUPIEDWHITE UMETA(DisplayName = "Occupied by White Piece")
};

UCLASS()
class PAA_UNREALCHESS_API AChess_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChess_Tile();

	// Set the (x,y) position
	void SetGridPosition(const double InX, const double InY);

	// get the (x,y) position
	FVector2D GetGridPosition();

	void SetDarkMaterial();

	void SetEmptyTile();

	void SetOccupyingPiece(AChess_Piece* Piece/*, bool destroypiece*/);

	ETileStatus GetTileStatus();

	AChess_Piece* GetOccupyingPiece();

	void Highlight(bool highlight);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstance* DarkVariant;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInterface* HighlightOverlay;

	// (x,y) position
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D TileGridPosition;

	// indica lo stato della tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETileStatus TileStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AChess_Piece* OccupyingPiece = nullptr; // indica quale pezzo occupa la tile, lo faccio in maniera generale, se ho nullptr allora la tile � vuota

	// A differenza del TTT, ho eliminaot lo status e il playerowner, perch� si pu� fare tutto tramite occupying piece, il colore indica il proprietario e il nullptr indica se la tile � vuota

// public:	// Le tiles non devono tickare
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

};
