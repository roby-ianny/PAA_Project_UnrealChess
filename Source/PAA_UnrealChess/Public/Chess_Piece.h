// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chess_Move.h"
#include "Chess_NormalMove.h"
#include "Chess_Direction.h"
#include "GameFramework/Actor.h"
#include "Chess_Piece.generated.h"

// Forward Declarations per evitare problemi di dipendenze cicliche
class AChess_GameField;
class Chess_Direction;

UCLASS()
class PAA_UNREALCHESS_API AChess_Piece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChess_Piece();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//self destroy/piece eaten
	UFUNCTION()
	void SelfDestroy();

	UFUNCTION()
	virtual void SetDarkMaterial();

	UFUNCTION()
	int32 GetColor() const;

	// Array che mostra le posizioni che può raggiungere il pezzo
	virtual TArray<Chess_Move> ComputeMoves(FVector2D frompos, AChess_GameField* GF);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<FVector2D> MovePositionsInDir(FVector2D frompos, Chess_Direction direction, AChess_GameField* GF); // returns the possible moves in a given di

	TArray<FVector2D> MovePositionInDirs(FVector2D frompos, TArray<Chess_Direction> dirs, AChess_GameField* GF);

	// 0 = white, 1 = black
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	int32 color; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstance* DarkVariant;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	bool HasMoved = false;
};
