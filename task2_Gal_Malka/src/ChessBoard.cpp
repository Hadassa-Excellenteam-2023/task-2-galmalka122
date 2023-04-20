#include "ChessBoard.h"

ChessBoard::ChessBoard(string boardString) : m_blackKingPosition(nullptr), m_whiteKingPosition(nullptr)
{
	// Initialize the board vector
	vector<ChessPiece*> curLine;

	for (auto character : boardString)
	{
		// Determine the position by the vector size
		string position = string() + char('a' + m_board.size()) + char('1' + curLine.size());
		Position p(position);
		
		if (character == '#')
		{
			curLine.push_back(nullptr);
		}

		// Determine the color of the piece by the representing charecter
		else {
			Color color = character > 96 && character < 123 ? Color::Black : Color::White;

			// Initialize the piece
			switch (character)
			{
			case 'p': case 'P':
			{
				curLine.push_back(new Pawn(color, character, p));
				break;
			}
			case 'k': case 'K':
			{
				King* k = new King(color, character, p);
				curLine.push_back(k);
				color == White ? m_whiteKingPosition = &k->getPosition() : m_blackKingPosition = &k->getPosition();
				break;
			}
			case 'r': case 'R':
			{
				curLine.push_back(new Rook(color, character, p));
				break;
			}
			case 'q': case 'Q':
			{
				curLine.push_back(new Queen(color, character, p));
				break;
			}
			case 'n': case 'N':
			{
				curLine.push_back(new Knight(color, character, p));
				break;
			}
			case 'b': case 'B':
			{
				curLine.push_back(new Bishop(color, character, p));
				break;
			}
			}
		}

		if (curLine.size() == BOARD_SIZE) {
			m_board.push_back(curLine);
			curLine.clear();
		}
	}

}

int ChessBoard::getCodeResponse(const string& move)
{
	Position sourcePosition(move.substr(0, 2));
	ChessPiece* sourcePiece = m_board[sourcePosition.row][sourcePosition.col];

	// Check if there is no piece in source
	if (!sourcePiece) {
		return EmptyPieceInSource;
	}

	// Check if the source piece belongs to the current player
	if (sourcePiece->getColor() != m_turn) {
		return SourcePieceWrongColor;
	}

	Position destinationPosition(move.substr(2, 2));
	ChessPiece* destinationPiece = m_board[destinationPosition.row][destinationPosition.col];

	// check if the destination has a same color piece
	if (destinationPiece && sourcePiece->getColor() == destinationPiece->getColor())
			return DestinationPieceWrongColor;
	

	int distance = sourcePosition.getDistance(destinationPosition);
	Direction direction = sourcePosition.getDirection(destinationPosition);

	// check if the piece can move to the destination
	if (!sourcePiece->isValidMove(direction, distance) || !sourcePiece->canColide(*destinationPiece, direction, true)) {
		return IllegalMovement;
	}

	// Check the path
	if (sourcePiece && !checkPath(sourcePiece, destinationPosition,direction)) {
			return IllegalMovement;
	}

	// Perform the move
	m_board[destinationPosition.row][destinationPosition.col] = sourcePiece;
	m_board[sourcePosition.row][sourcePosition.col] = nullptr;
	sourcePiece->move(destinationPosition);

	// Check if the move caused the current player to be in check
	if (canCauseCheck((m_turn == White ? *m_whiteKingPosition : *m_blackKingPosition))) {

		// Undo the move
		m_board[sourcePosition.row][sourcePosition.col] = sourcePiece;
		sourcePiece->move(sourcePosition);
		m_board[destinationPosition.row][destinationPosition.col] = destinationPiece;
		return CauseCheckmate;
	}

	// Switch turn
	m_turn = m_turn == White ? Black : White;

	// Check if the move caused the opponent player to be in check
	if (canCauseCheck(m_turn == White ? *m_whiteKingPosition : *m_blackKingPosition)) {
		return LegalAndCheck;
	}

	return Legal;
}

// Check if a piece can move through pass to destination
bool ChessBoard::checkPath(ChessPiece* piece, Position& destination, Direction& direction) const{

	Position currentPosition = piece->getPosition();
	ChessPiece* currentPiece;

	// Iterate through every square in the pass and check if the piece can move towards it
	while ((currentPosition + direction) != destination) {
		currentPiece = m_board[currentPosition.row][currentPosition.col];
		if (!piece->canColide(*currentPiece, direction, false))
			return false;
	}
	return true;
}

// Check if a move is causing a check
bool ChessBoard::canCauseCheck(Position kingPosition) const {

	ChessPiece* king = m_board[kingPosition.row][kingPosition.col];

	// Iterate through every piece and id it is the opponent piece check if it can move towards the king
	for (auto line : m_board) {
		for (auto piece : line) {
			if (piece && piece != king && piece->getColor() != king->getColor()) {
				int distance = piece->getPosition().getDistance(kingPosition);
				Direction direction = piece->getPosition().getDirection(kingPosition);
				if (piece->isValidMove(direction, distance) && checkPath(piece, kingPosition, direction))
					return true;
			}
		}
	}
	return false;
}

// Create a string representing the current board
const string ChessBoard::toString() const
{
	string board = "";
	for (auto line : m_board) {
		for (auto piece : line) {
			if (piece)
				board.push_back(piece->getRep());
			else board.push_back('#');
		}
	}
	return board;
}

ChessBoard::~ChessBoard() {
	for (auto line : m_board) {
		for (auto piece : line) {
			if (piece)
				delete piece;
		}
	};
};

