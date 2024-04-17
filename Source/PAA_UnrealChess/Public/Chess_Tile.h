// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chess_Piece.h" 
#include "Chess_Tile.generated.h"

/* Come posso cambiare colore alla cella ?
/ https://forums.unrealengine.com/t/how-to-change-material-for-a-mesh-in-cpp/613186
*/

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

	void SetOccupyingPiece(AChess_Piece* Piece);

	ETileStatus GetTileStatus();

	AChess_Piece* GetOccupyingPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstance* DarkVariant;

	// (x,y) position
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D TileGridPosition;

	// indica lo stato della tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETileStatus TileStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AChess_Piece* OccupyingPiece = nullptr; // indica quale pezzo occupa la tile, lo faccio in maniera generale, se ho nullptr allora la tile è vuota

	// A differenza del TTT, ho eliminaot lo status e il playerowner, perchè si può fare tutto tramite occupying piece, il colore indica il proprietario e il nullptr indica se la tile è vuota

// public:	// Le tiles non devono tickare
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

};
