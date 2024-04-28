// Fill out your copyright notice in the Description page of Project Settings.

#include "Chess_HumanPlayer.h"
#include "Chess_GameField.h"
#include "Chess_GameMode.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AChess_HumanPlayer::AChess_HumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the pawn to be controller from player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Camera as root component
	SetRootComponent(Camera);

	// Game instance reference
	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

}

// Called when the game starts or when spawned
void AChess_HumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AChess_HumanPlayer::IsInMoveCache(FVector2D TilePosition)
{
	for (TSharedPtr<Chess_Move>& Move: MoveCache) {
		if (TilePosition == Move->ToPosition)
			return true;
	}
	return false;
}

TSharedPtr<Chess_Move> AChess_HumanPlayer::GetMoveFromSelectedPosition(FVector2D TilePosition)
{
	for (TSharedPtr<Chess_Move>& Move : MoveCache) {
		if (TilePosition == Move->ToPosition)
			return Move;
	}
	// maybe an error report should be displayed
	return nullptr;
}

// Called every frame
void AChess_HumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_HumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChess_HumanPlayer::OnTurn()
{
	IsMyTurn = true;
	PieceSelected = false; // just to be sure
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn"));
	GameInstance->SetTurnMessage(TEXT("Your Turn"));
	MoveCache.Empty(); //deletes the previous turn movecache
}

void AChess_HumanPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins!"));
	// GameInstance->IncrementScoreHumanPlayer();
}

void AChess_HumanPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Lose!"));
	GameInstance->SetTurnMessage(TEXT("Computer Wins!"));
}


void AChess_HumanPlayer::OnClick()
{
	AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode->IsGameOver)
		return; // if the game is over, don't do anything

	//I can optimize the algorithm instead of computing the possible moves everytime that the player clicks

	//Structure containing information about one hit of a trace, such as point of impact and surface normal at that point
	FHitResult Hit = FHitResult(ForceInit);
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	//if we hit something and it's our turn
	if (Hit.bBlockingHit && IsMyTurn) {
		// check if i hit a tile 
		if (AChess_Tile* Tile = Cast<AChess_Tile>(Hit.GetActor())) {
			// Checks if the tile is occupied
			if (Tile->GetTileStatus() == ETileStatus::OCCUPIEDWHITE) {

				// If a piece was already selected it de-highlights the tiles
				if (PieceSelected == true)
					GameField->HighlightTiles(MoveCache, false);
				else
					PieceSelected = true;

				// Compute moves of the selected piece
				MoveCache = Tile->GetOccupyingPiece()->ComputeMoves(Tile->GetGridPosition(), GameField);
				GameMode->FilterLegalMoves(MoveCache);
				if (MoveCache.Num() == 0) {
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You can't move this piece!"));
				}
				GameField->HighlightTiles(MoveCache, true);
			} else if (PieceSelected == true && IsInMoveCache(Tile->GetGridPosition())) {
				// ATTT_GameMode* GameMode = Cast<ATTT_GameMode>(GetWorld()->GetAuthGameMode()); //Faccio il casting, in teoria avrei dovuto utilizzare "isvalid" 
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Executing a move!"));
				TSharedPtr<Chess_Move> MoveToExecute = GetMoveFromSelectedPosition(Tile->GetGridPosition());
				GameField->HighlightTiles(MoveCache, false);
				MoveCache.Empty();
				IsMyTurn = false;
				if (MoveToExecute->Type == EMoveType::PawnPromotion) {
					EPieceType PromotionPiece = GameMode->PawnPromotionSelection();
				}
				GameMode->ExecuteMove(MoveToExecute);
			} else //if I click on a non-highlited tile
				GameField->HighlightTiles(MoveCache, false);
		}
	}
}


