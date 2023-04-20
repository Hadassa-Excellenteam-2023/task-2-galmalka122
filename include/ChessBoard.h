#pragma once
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

const int BOARD_SIZE = 8;

enum GameCode {
	EmptyPieceInSource = 11,
	SourcePieceWrongColor,
	DestinationPieceWrongColor,
	IllegalMovement = 21,
	CauseCheckmate = 31,
	LegalAndCheck = 41,
	Legal
};

class ChessBoard {

private:

	inline static Color m_turn = Color::White;
	vector<vector<ChessPiece*>> m_board;
	const Position* m_whiteKingPosition;
	const Position* m_blackKingPosition;

	bool canCauseCheck(Position kingPosition) const;
	bool checkPath(ChessPiece*, Position&, Direction&) const;

public:
	
	ChessBoard(string boardString);
	int getCodeResponse(const string& move);
	const string toString() const;
	~ChessBoard();
};