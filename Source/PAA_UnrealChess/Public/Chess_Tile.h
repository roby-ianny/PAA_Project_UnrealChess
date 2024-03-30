// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chess_Tile.generated.h"

UENUM()
enum class ETileStatus : uint8 {
	EMPTY		UMETA(DisplayName = "Empty"),
	OCCUPIED	UMETA(DisplayName = "Occupied"),
};

/* Come posso cambiare colore alla cella ?
/ https://forums.unrealengine.com/t/how-to-change-material-for-a-mesh-in-cpp/613186
*/
UCLASS()
class PAA_UNREALCHESS_API AChess_Tile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChess_Tile();

	//Set the player owner and the Tile Status
	void setTileStatus(const int32 TileOwner, const ETileStatus TileStatus); //per ora mettiamo player owner, anche se forse sarebbe meglio mettere direttamente il pezzo

	//get the tile status
	ETileStatus getTileStatus();

	// Get the tile owner
	int32 getTileOwner(); //Anche qui vedremo cosa mettere, forse sarebbe più opportuno mettere il pezzo e il colore (per esempio wN (Cavallo Bianco))

	// Set the (x,y) position
	void setGridPosition(const double InX, const double InY);

	// get the (x,y) position
	FVector2D getGridPosition();

	void SetDarkMaterial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstance* DarkVariant;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETileStatus Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerOwner;

	// (x,y) position
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D TileGridPosition;

// public:	// Le tiles non devono tickare
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

};
