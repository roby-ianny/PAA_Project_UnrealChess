// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameMode.h"
#include "Chess_PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "Chess_CPURandom.h"
#include "EngineUtils.h"


// Keep the default constructor just for now
AChess_GameMode::AChess_GameMode()
{
	PlayerControllerClass = AChess_PlayerController::StaticClass();
	DefaultPawnClass = AChess_HumanPlayer::StaticClass();
}


void AChess_GameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));
	//spawns the gamefield
	if (GameFieldClass != nullptr) {
		GField = GetWorld()->SpawnActor<AChess_GameField>(GameFieldClass);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	//camera things
	/*
	float CameraPosX = ((GField->TileSize * (FieldSize + ((FieldSize - 1) * GField->NormalizedCellPadding) - (FieldSize - 1))) / 2) - (GField->TileSize / 2);
	FVector CameraPos(CameraPosX, CameraPosX, 1000.0f);	// Prendo due volte cameraposx perché tanto il campo è quadrato
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());	//Setto come attore la telecamera e la associo allo humanplayer
	*/

	float CameraPosX = (GField->TileSize * (4));
	FVector CameraPos(CameraPosX, - CameraPosX, 1000.0f);	// Prendo due volte cameraposx

	// Ottieni la rotazione dalla matrice
	FRotator NewRotation = FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator();
	NewRotation.Pitch = -90.0f;	// Imposta il pitch a -90° per guardare in basso
	NewRotation.Yaw = -90.0f;   // Imposta lo Yaw a -90°
	HumanPlayer->SetActorLocationAndRotation(CameraPos, NewRotation);	//Setto come attore la telecamera e la associo allo humanplayer
	// Human player is the player 0, that also indicates the white color
	HumanPlayer->PlayerNumber = 0;
	Players.Add(HumanPlayer);
	//Random Player is the player 1, that also indicates the black color
	AChess_CPURandom* CPU = GetWorld()->SpawnActor<AChess_CPURandom>(FVector(), FRotator());
	CPU->PlayerNumber = 1;

	// CPU player = 1
	Players.Add(CPU);

	this->ChoosePlayerAndStartGame();

	HumanPlayer->GameField = GField;
	CPU->GameField = GField;
}

void AChess_GameMode::ChoosePlayerAndStartGame()
{
	Players[0]->OnTurn(); //a differenza di quanto fatto per il TTT, qui inizia il bianco, che è l'umano
}

void AChess_GameMode::ExecuteMove(TSharedPtr<Chess_Move>& Move)
{
	FPiecesOfMove Pieces =  Move->Execute(GField);
	char checkstate = ' ';
	if (GField->IsInCheck(GetNextPlayer(CurrentPlayer)))
		checkstate = '+'; 

	MoveHistory.Add(FRegisteredMove{ Move, Pieces,checkstate});
	AddToMoveHistory();
	TurnNextPlayer();
}

void AChess_GameMode::ExecutePawnPromotion(FVector2D FromPos, FVector2D ToPos, EPieceType PromotionType)
{
	TSharedPtr<Chess_Move> MoveToExecute = MakeShared<Chess_PawnPromotion>(FromPos, ToPos, PromotionType);
	ExecuteMove(MoveToExecute);
}


int32 AChess_GameMode::GetNextPlayer(int32 Player)
{
	Player++;
	if (!Players.IsValidIndex(Player))
	{
		Player = 0;
	}
	return Player;
}

void AChess_GameMode::TurnNextPlayer()
{
	// MoveCounter +=1;
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	CheckForGameOver(); //ChecksForGameOver before player turn
	if (!IsGameOver)
		Players[CurrentPlayer]->OnTurn();
}

void AChess_GameMode::FilterLegalMoves(TArray<TSharedPtr<Chess_Move>>& Moves)
{
	//I have to go backwards on the array to avoid problems with the remove method
	for (auto i = Moves.Num() - 1; i >= 0; i--) {
		if (!(Moves[i]->IsLegal(GField)))
			// the problem is here because of the remove
			Moves.RemoveAt(i); //the smart pointer will manage the memory
	}
}

TArray<TSharedPtr<Chess_Move>> AChess_GameMode::GetAllPlayerMoves(int32 player)
{
	TArray<AChess_Tile*> PlayerTiles = GField->GetTilesWithPlayerPieces(player);
	TArray <TSharedPtr<Chess_Move>> moveCandidates;

	for (AChess_Tile* Tile : PlayerTiles)
		moveCandidates.Append(Tile->GetOccupyingPiece()->ComputeMoves(Tile->GetGridPosition(), GField));
		
	FilterLegalMoves(moveCandidates);

	return moveCandidates;
}

void AChess_GameMode::CheckForGameOver()
{
	if (GetAllPlayerMoves(CurrentPlayer).Num() == 0) {
		IsGameOver = true; //the game is over
		if (GField->IsInCheck(CurrentPlayer))
			Players[GetNextPlayer(CurrentPlayer)]->OnWin();
		else
			// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Stalemmate!"));
			Players[GetNextPlayer(CurrentPlayer)]->OnDraw();
	}

	// if there are only two kings it's a stalemate!
	if (GField->GetTilesWithPlayerPieces(0).Num() == 1 && GField->GetTilesWithPlayerPieces(1).Num() == 1) {
		IsGameOver = true; //the game is over
		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Stalemmate!"));
		Players[GetNextPlayer(CurrentPlayer)]->OnDraw();
	}
}

void AChess_GameMode::PawnPromotionSelection(TSharedPtr<Chess_Move> MoveToExecute)
{
	if (!PPWidget)
		return;

	// Crea un'istanza del widget
	UChess_PPWidget* WidgetInstance = CreateWidget<UChess_PPWidget>(GetWorld(), PPWidget);
	WidgetInstance->SetFromTo(MoveToExecute->FromPosition, MoveToExecute->ToPosition);

	// Controlla se l'istanza del widget è valida
	if (WidgetInstance)
	{
		WidgetInstance->AddToViewport();
	}
	else
		return ;
	
}

FString AChess_GameMode::MoveToChessNotation(int32 MoveIndex)
{
	// empty string in case of invalid index
	if (!(MoveIndex < MoveHistory.Num()))
		return "";

	FString Notation = ""; //starting from empty string
	FRegisteredMove RegisteredMove = MoveHistory[MoveIndex]; //get the registered move
	Notation += FromChessPieceToChessNotation(RegisteredMove.Pieces.MovedPiece); //get the moved piece
	Notation += FromGridPositionToChessNotation(RegisteredMove.Move->FromPosition);
	if (RegisteredMove.Pieces.CapturedPiece != nullptr)
		Notation += "x";
	Notation += FromGridPositionToChessNotation(RegisteredMove.Move->ToPosition);
	// in case of pawn promotion we have to return the promotion piece
	switch (RegisteredMove.Move->GetPromotionPiece()) {
		case EPieceType::QUEEN:
			Notation += "Q";
			break;	
		case EPieceType::ROOK:
			Notation += "R";
			break;
		case EPieceType::BISHOP:
			Notation += "B";
			break;
		case EPieceType::KNIGHT:
			Notation += "N";
			break;
		default:
			break;
	}

	Notation += RegisteredMove.CheckState; //get the check state, space if there's no check
	return Notation;
}

FString AChess_GameMode::LatestMoveToChessNotation()
{
	return MoveToChessNotation(MoveHistory.Num()  - 1);
}

TArray<FString> AChess_GameMode::LatestMovesToChessNotation(int32 NumMoves)
{
	TArray<FString> Notations;
	if (NumMoves >= MoveHistory.Num())
		return Notations;

	for (int32 i = (MoveHistory.Num() - 1); i >= (MoveHistory.Num() - NumMoves); i--)
		Notations.Add(MoveToChessNotation(i));

	return Notations;
}

int32 AChess_GameMode::GetLastMoveIndex()
{
	return (MoveHistory.Num()-1);
}

void AChess_GameMode::AddToMoveHistory_Implementation()
{
	FString MoveNotation = LatestMoveToChessNotation();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, MoveNotation);
}

void AChess_GameMode::GoToOldState(int32 index)
{
	if (index > GetLastMoveIndex())
		return;

	for (auto i = GetLastMoveIndex(); i > index; i--) {
		UndoLastMove();
	}

	if ((MoveHistory.Num() - 1) % 2 == 0) // state where the latest move was done by the humanplayer
		CurrentPlayer = 0;
	else
		CurrentPlayer = 1;				// state where the latest move was done by the CPU
	
	TurnNextPlayer();
}

void AChess_GameMode::UndoLastMove()
{
	FRegisteredMove LatestMove = MoveHistory.Last();
	LatestMove.Move->Undo(GField,LatestMove.Pieces.MovedPiece, LatestMove.Pieces.CapturedPiece);
	MoveHistory.Pop();
}

FString AChess_GameMode::FromGridPositionToChessNotation(FVector2D GridPosition)
{
	FString Location = ""; //empty string

	// Letters for every column
	const char Letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

	// From column number to letter
	Location += Letters[int(GridPosition.X)];
	
	Location.AppendInt(int(GridPosition.Y + 1));

	return Location;
}

FString AChess_GameMode::FromChessPieceToChessNotation(AChess_Piece* Piece)
{
	FString Notation = "";

	// checks for the piece color
	if (Piece->GetColor() == 1)
		Notation.AppendChar('b');
	else
		Notation.AppendChar('w');

	switch (Piece->GetType())
	{
	case EPieceType::ROOK:		
		Notation.AppendChar('R'); 
		break;
		case EPieceType::KNIGHT:	
			Notation.AppendChar('N');
			break;
		case EPieceType::BISHOP:	
			Notation.AppendChar('B');
			break;
		case EPieceType::QUEEN:		
			Notation.AppendChar('Q');
			break;
		case EPieceType::KING:		
			Notation.AppendChar('K');
			break;
		case EPieceType::PAWN:
		default:					
			break;
	}

	return Notation;
}

 
