// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chess_Piece.generated.h"

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

	// UFUNCTION()
	// virtual void DiplayPossibleMoves();

	void SetDarkMaterial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	int32 color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UMaterialInstance* DarkVariant;

	/*
	// (x,y) position
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D Position; //Needed?
	*/

};
