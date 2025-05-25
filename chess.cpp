#include "splashkit.h"
using namespace std;

//defining the size of chess board and size of each tile
const int SIZE_BOARD = 8;
const int SIZE_TILE = 60; 

//these variables will be used in the timer for the game/user
//each user will have 10 minutes to play the game
const int TOTAL_TIME = 600;
int time_left_white = TOTAL_TIME; //time left for the white player
int time_left_black = TOTAL_TIME; //time left for the black player
bool is_white_turn = true; //to check if it is white's turn
bool is_black_turn = false; //to check if it is black's turn

//array of quotes to display
const string QUOTES[] = {
    "Even the laziest King flees wildly in the face of a double check!",
   "A pawn is not a piece, it is a soldier.",
   "Chess is a fairy tale of 1001 blunders.",
   "The Queen is the most powerful piece on the board.",
    "The winner of the game is the player who makes the next-to-last mistake.",
    "Its just you and your opponent at the board, and the rest of the world is gone.",
    "Chess is a game of strategy and tactics.",
    "The King is the most important piece on the board.",
    "Chess is played with the mind and not with the hands!",
    "What would Chess be without silly mistakes?",
    "Life is like a game of chess. You should always think one move ahead of your opponent."
};

//calculating the number of quotes
//the total size in bytes of the whole array / the size in bytes of one element
const int NUM_OF_QUOTES = sizeof(QUOTES) / sizeof(QUOTES[0]);

//defining colors of chess pieces
enum piece_color{
    NO_COLOR,
    WHITE, 
    BLACK
};

//defining types of chess pieces
enum chess_piece{
    NO_PIECE, 
    PAWN, 
    ROOK, 
    KNIGHT, 
    BISHOP, 
    QUEEN, 
    KING
};

//defining a struct to define the type and clr of the piece
struct chess_piece_info{
    chess_piece type;
    piece_color color;
};

typedef chess_piece_info piece;


//2D array to define a chess board of 8x8 size
piece chess_board[SIZE_BOARD][SIZE_BOARD]; 
//there are 64 squares in total in chess board

//declaring bitmaps for chess pieces
bitmap white_king, white_pawn, white_knight, white_queen, white_rook, white_bishop;
bitmap black_king, black_pawn, black_knight, black_queen, black_rook, black_bishop;

//loading chess piece images with a name  
void chess_pieces_images(){
    white_pawn = load_bitmap("white_pawn", "images/white-pawn.png");
    black_pawn = load_bitmap("black_pawn", "images/brown-pawn.png");
    white_rook = load_bitmap("white_rook", "images/white-castle.png");
    black_rook = load_bitmap("black_rook", "images/brown-castle.png");
    white_knight = load_bitmap("white_knight", "images/white-elephant.png");
    black_knight = load_bitmap("black_knight", "images/brown-elephant.png");
    white_bishop = load_bitmap("white_bishop", "images/white-bishop.png");
    black_bishop = load_bitmap("black_bishop", "images/bishop-brown.png");
    white_queen = load_bitmap("white_queen", "images/white-queen.png");
    black_queen = load_bitmap("black_queen", "images/brown-queen.png");
    white_king = load_bitmap("white_king", "images/white-king.png");
    black_king = load_bitmap("black_king", "images/brown-king.png");
}

//making chess board and defining position of the pieces
void making_chess_board(){

    //a for loop for rows
    for(int row = 0; row < SIZE_BOARD; row++){
        //a for loop for columns
        for(int col = 0; col < SIZE_BOARD; col++){

            //the second row [from the top] (row = 1) is alone for black pawns
            if(row == 1){
                chess_board[row][col] = {
                    chess_piece(PAWN), 
                    piece_color(BLACK)
                };
            }
            
            //in first row (row = 0), we have to align black chess pieces
            else if(row == 0){
                //there is only one queen among black pieces, so we assign only one position to it
                if(col == 3){
                    chess_board[row][col] = {
                        chess_piece(QUEEN),
                        piece_color(BLACK)
                    };
                }

                //there is only one king among black pieces, so we assign only one position to it
                if(col == 4){
                    chess_board[row][col] = {
                        chess_piece(KING),
                        piece_color(BLACK)
                    };
                }
                
                //there are 2 black rooks, one at the start and one at the end of the row
                //so we assign one rook at col == 0 and the other at col == 7
                if(col == 0 || col == 7){
                    chess_board[row][col] = {
                        chess_piece(ROOK),
                        piece_color(BLACK)
                    };
                }

                //there are 2 black knights, each piece 1 block closer to the middle from the either end
                //assigned one at col = 1 and col = 6
                if(col == 1 || col == 6){
                    chess_board[row][col] = {
                        chess_piece(KNIGHT),
                        piece_color(BLACK)
                    };
                }

                //there are 2 black bishops, each piece 2 blocks closer to the middle from either end
                //assigned one at col = 2 and col = 5
                if(col == 2 || col == 5){
                    chess_board[row][col] = {
                        chess_piece(BISHOP),
                        piece_color(BLACK)
                    };
                }
                
            }

            //row 6 (second last row from other side) is solely white pawns 
            else if(row == 6){
                chess_board[row][col] = {
                    chess_piece(PAWN),
                    piece_color(WHITE)
                };
            }

            //in the last row (row = 7) we have to align white chess pieces
            else if(row == 7){

                //there is only one white queen, so assigned appropriate position to it
                if(col == 3){
                    chess_board[row][col] = {
                        chess_piece(QUEEN),
                        piece_color(WHITE)
                    };
                }

                //there is only one white king, so assigned appropriate position to it
                if(col == 4){
                    chess_board[row][col] = {
                        chess_piece(KING),
                        piece_color(WHITE)
                    };
                }

                //there are 2 white rooks, one at the start and one at the very end of the row
                //assigned one rook to col 0 and one to col 7 (in row 7)
                if(col == 0 || col == 7){
                    chess_board[row][col] = {
                        chess_piece(ROOK),
                        piece_color(WHITE)
                    };
                }

                //there are 2 white knights, each piece 1 block closer to the middle from either ends
                //assigned one knight at col 1 and other at col 6 (in row 7)
                if(col == 1 || col == 6){
                    chess_board[row][col] = {
                        chess_piece(KNIGHT),
                        piece_color(WHITE)
                    };
                }

                //there are 2 white bishops, each piece 2 blocks closer to the middle from either ends
                //assigned one knight at col 2 and other at col 5 (in row 7)
                if(col == 2 || col == 5){
                    chess_board[row][col] = {
                        chess_piece(BISHOP),
                        piece_color(WHITE)
                    };
                }
                
            }

            //if the row is not 0, 1, 6 or 7, then it is empty
            else{
                chess_board[row][col] = {
                    chess_piece(NO_PIECE),
                    piece_color(WHITE)
                };
            }
        }
    }
}

//passing the array of quotes, number of quotes and the index of the quote to be displayed
//quote_index = -1 as no quote is selected by default
//setting quote_index to a random number if no quote is selected
void display_quote(const string *quotes, const int num, int quote_index){
    // Use provided quote_index or generate random one if not provided
    int index = quote_index;

    //calculate position for quote display (to the right of chess board)
    int quote_x = (SIZE_BOARD * SIZE_TILE) + 20; //+ 20 to shift it a bit to the right
    int quote_y = 100; //y position of the quote
    int max_width = 360; //max width of one line of text
    
    //drawing a background for the quote
    fill_rectangle(COLOR_WHITE, quote_x - 10, (SIZE_BOARD * SIZE_TILE)/ 3, 380, 150);
    //border for the background
    draw_rectangle(COLOR_BLACK, quote_x - 10, (SIZE_BOARD * SIZE_TILE)/ 3, 380, 150);
    
    //displaying a title
    draw_text("Chess Wisdom:", COLOR_BLACK, quote_x, (SIZE_BOARD * SIZE_TILE)/ 2.6);
    
    //getting the selected quote
    string quote = quotes[index];

    //positioning the quote
    int line_y =  (SIZE_BOARD * SIZE_TILE)/ 2.2;
    int start_pos = 0; //start position of the quote
    int current_pos = 0; //last position of the quote
    int line_count = 0; //number of lines drawn
    
    //processing the quote for line wrapping
    while (current_pos < quote.length() && line_count < 5) {
        //finding next space or end of string
        int next_space = quote.find(' ', current_pos + 1);
        if (next_space >= quote.length()) { //checking if next_space is beyond the string length
            next_space = quote.length();
        }
        
        //check if adding the next word would exceed max width
        string test_line = quote.substr(start_pos, next_space - start_pos);
        if (text_width(test_line, "Arial", 20) > max_width) {
            //draw the current line up to current_pos
            draw_text(quote.substr(start_pos, current_pos - start_pos), 
                     COLOR_BLACK, quote_x, line_y);
            
            //move to next line
            line_y += 20;
            line_count++;
            start_pos = current_pos + 1;
        }
        
        current_pos = next_space;
    }
    
    //draw the final line if there's text remaining
    if(start_pos < quote.length() && line_count < 5){
        draw_text(quote.substr(start_pos), COLOR_BLACK, quote_x, line_y);
    }
}
//checking if the pawn moves is valid
bool checking_pawn_moves(int initial_row, int initial_col, int new_row, int new_col, piece_color clr){
    
    //pawn moves one square forward
    
    //if the color is white, it moves up (row - 1 as row decreases)
    if(clr == piece_color(WHITE)){
        //if the column is same and final row is one less than the initial row, then it is a valid move and it means the pawn is moving upwards
        if(initial_col == new_col && initial_row - 1 == new_row && chess_board[new_row][new_col].type == chess_piece(NO_PIECE)){
            return true;
        }
        //pawn captures diagonally
        //to move diagonally, the column and the row are changed by 1 
        //here the color is white, so the row is decreased by 1 and the column is increased/decreased by 1, depending on the direction
        if(abs(initial_col - new_col) == 1 && initial_row - 1 == new_row && chess_board[new_row][new_col].type != chess_piece(NO_PIECE) && chess_board[new_row][new_col].color == piece_color(BLACK)){
            return true; //valid capture move
        } 
    }
    //if the color is black, it moves down (row + 1 as row increases)
    else if(clr == piece_color(BLACK)){

        //abs(initial_col - new_col) checks if the pawn is moving diagonally
        //the pawn will move diagonally if an opponent's piece is present diagnally
        //checks if an opponent's piece is present diagonally, and the row is increased by 1
        if(abs(initial_col - new_col) == 1 && initial_row + 1 == new_row && chess_board[new_row][new_col].type != chess_piece(NO_PIECE) && chess_board[new_row][new_col].color == piece_color(WHITE)){
            return true; //valid capture move
        }
        //if the column is same and final row is one more than the initial row, then it is a valid move and it means the pawn is moving downwards
        if(initial_col == new_col && initial_row + 1 == new_row && chess_board[new_row][new_col].type == chess_piece(NO_PIECE)){
            return true;
        }
    }

    //return false if the move is not valid
    return false;
}

bool checking_rook_moves(int initial_row, int initial_col, int new_row, int new_col){

    //rook moves in a straight line, either horizontally or vertically
    //if both columns and rows change, that means its a diagonal move, so return false then
    if(initial_row != new_row && initial_col != new_col){
        return false; //not a straight line
    }

    //if the row is same, it means the rook is moving horizontally
    if(initial_row == new_row){

        //horizontal move means columns are changing but rows remain static
        int start_col = initial_col;
        int end_col = new_col;

        //ensuring we loop from left to right
        if(start_col > end_col){

            //swap the start and end columns
            //this is done to ensure we loop from left to right
            int temp = start_col;
            start_col = end_col;
            end_col = temp;
        }

        //checking if the path is clear
        //we loop from start_col + 1 to end_col - 1
        //we do this to check if there is any piece in between the start and end column
        //if there is a piece, return false
        for(int c = start_col + 1; c < end_col; c++){
            if(chess_board[initial_row][c].type != chess_piece(NO_PIECE)){
                return false; //blocked by another piece
            }
        }
    }

    else if(initial_col == new_col){
        //moving vertically
        int start_row = initial_row;
        int end_row = new_row;

        //ensuring we loop from top to bottom
        if(start_row > end_row){
            int temp = start_row;
            start_row = end_row;
            end_row = temp;
        }
        
        //checking if the path is clear for vertical move
        //just like the horizontal move, we loop from start_row + 1 to end_row - 1
        //we do this to check if there is any piece in between the start and end row
        //if there is a piece, return false
        for(int r = start_row + 1; r < end_row; r++){
            if(chess_board[r][initial_col].type != chess_piece(NO_PIECE)){
                return false; //blocked by another piece
            }
        }
    }
    return true; //valid rook move with clear path
}


bool checking_knight_moves(int initial_row, int initial_col, int new_row, int new_col){
   
   //knight moves in an L shape
   //to check if the move is valid, we check the difference in rows and columns
   int row_diff = abs(initial_row - new_row);
   int col_diff = abs(initial_col - new_col);

    //knight moves in L shape
    //if the difference is 2 in one direction and 1 in the other direction, it is a valid move
    if((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)){
        return true; //valid knight move
    }
    return false; //invalid knight move
}


bool checking_bishop_moves(int initial_row, int initial_col, int new_row, int new_col){

    //bishop moves diagonally
    //to check if the move is valid, we check the difference in rows and columns
    //if the difference is not the same, it is not a valid move
    //lets say the bishop is at (5, 0) and it moves to (1, 4)
    //the (absolute) difference b/w the rows is 4 and the (absolute) difference b/w the columns is also 4
    if(abs(initial_row - new_row) != abs(initial_col - new_col)){
        return false; //not diagonal
    }

    //defining the direction of movement
    int row_moved;
    int col_moved;

    //if the new row is greater than the initial row, it means the bishop is moving down
    if(new_row > initial_row){
        row_moved = 1;
    }
    //if the new row is less than the initial row, it means the bishop is moving up
    else if(new_row < initial_row){
        row_moved = -1;
    }

    //if the new column is greater than the initial column, it means the bishop is moving right
    if(new_col > initial_col){
        col_moved = 1;
    }
    //if the new column is less than the initial column, it means the bishop is moving left
    else if(new_col < initial_col){
        col_moved = -1;
    }

    //setting the current row and column to the initial row and column + the rows/columns moved
    int current_row = initial_row + row_moved;
    int current_col = initial_col + col_moved;

    //looping through the path of the bishop until it reaches the new row and column
    while(current_row != new_row && current_col != new_col){
        //checking if there is any piece in between the start and end row/column
        //if there is a piece, return false
        if(chess_board[current_row][current_col].type != chess_piece(NO_PIECE)){
            return false; //blocked by another piece
        }

        //moving the current row and column by the rows and columns moved
        current_row += row_moved;
        current_col += col_moved;
    }
    return true;
    
}

bool checking_queen_moves(int initial_row, int initial_col, int new_row, int new_col){

    //queen moves like a rook or a bishop
    //either horizontally, vertically or diagonally
    //if the move is not valid for rook or bishop, return false
    return checking_rook_moves(initial_row, initial_col, new_row, new_col) || checking_bishop_moves(initial_row, initial_col, new_row, new_col);
}

bool checking_king_moves(int initial_row, int initial_col, int new_row, int new_col){

    //king moves one square in any direction
    //if the difference in rows and columns is not more than 1, it is a valid move
    //the king can move in any direction, so we check if the difference in rows and columns is less than or equal to 1
    //either 0 or 1
    if(abs(initial_row - new_row) <= 1 && abs(initial_col - new_col) <= 1){
        return true; //valid king move
    }
    //if the difference is more than 1, it is not a valid move
    return false; //invalid king move
}

//function to draw the chess board
void draw_chess_board(){

    //a for loop to draw the chess board
    //the chess board is 8x8, so we loop through 8 rows and 8 columns
    //the size of each tile is 60x60
    //the size of the board is 8 * 60 = 480
    for(int r = 0; r < SIZE_BOARD; r++){
        for(int c = 0; c < SIZE_BOARD; c++){
            //calculating the x and y position of the tile
            //the x position is the column number * size of tile
            //the y position is the row number * size of tile
            //this is done to position the tile at the correct position on the board
            int x = c * SIZE_TILE;
            int y = r * SIZE_TILE;

            
            //if the sum is even, that means the tile is white
            if((r+c) % 2 == 0){
                fill_rectangle(COLOR_WHITE, x, y, SIZE_TILE, SIZE_TILE);
            }
            //if the sum is odd, that means the tile is black
            else{
                fill_rectangle(COLOR_BLACK, x, y, SIZE_TILE, SIZE_TILE);
            }
        }
    }

    //placing the chess pieces on the board
    //a for loop to place the chess pieces
    //the chess board is 8x8, so we loop through 8 rows and 8 columns
    for(int r = 0; r < SIZE_BOARD; r++){
        for(int c = 0; c < SIZE_BOARD; c++){
            int x = c * SIZE_TILE; 
            int y = r * SIZE_TILE;

            //getting the piece at the current position
            //using the chess_board array to get the piece at the current position from the piece struct
            piece piece = chess_board[r][c];

            //nullptr is used to check if the piece is empty or not
            //if the piece is empty, we do not need to place anything
            bitmap bitmap = nullptr;

            //checking the type of piece and color of piece
            //and assigning the bitmap to the appropriate piece
            if(piece.type == chess_piece(PAWN)){
                
                if(piece.color == piece_color(WHITE)){
                    bitmap = white_pawn;
                } 
                else if(piece.color == piece_color(BLACK)){
                    bitmap = black_pawn;
                }
            } 
            else if(piece.type == chess_piece(ROOK)){
                if(piece.color == piece_color(WHITE)){
                    bitmap = white_rook;
                }
                else if(piece.color == piece_color(BLACK)){
                    bitmap = black_rook;
                }
            } 
            else if(piece.type == chess_piece(KNIGHT)){
                if(piece.color == piece_color(WHITE)){
                    bitmap = white_knight;
                } 
                else if(piece.color == piece_color(BLACK)){
                    bitmap = black_knight;
                }
            } 
            else if(piece.type == chess_piece(BISHOP)){
                if(piece.color == piece_color(WHITE)){
                    bitmap = white_bishop;
                } 
                else if(piece.color == piece_color(BLACK)){
                    bitmap = black_bishop;
                }
            } 
            else if(piece.type == chess_piece(QUEEN)){
                if(piece.color == piece_color(WHITE)){
                    bitmap = white_queen;
                } 
                else if(piece.color == piece_color(BLACK)){
                    bitmap = black_queen;
                }
            } 
            else if(piece.type == chess_piece(KING)){
                if(piece.color == piece_color(WHITE)){
                    bitmap = white_king;
                } 
                else if(piece.color == piece_color(BLACK)){
                    bitmap = black_king;
                }
            }

            //if the bitmap is not null, it means the piece is not empty
            if(bitmap != nullptr){
                //calculating the offsets to center the piece within the tile
                float bmp_width = bitmap_width(bitmap);
                float bmp_height = bitmap_height(bitmap);
                float offset_x = (SIZE_TILE - bmp_width) / 2;
                float offset_y = (SIZE_TILE - bmp_height) / 2;

                //setting the drawing options
                //scaling the bitmap to fit the tile
                //the size of the tile is 60x60, so we scale the bitmap to fit the tile
                //the size of the bitmap is the size of the tile divided by the size of the bitmap

                //option_scale_bmp is used to scale the bitmap to fit the tile
                //this will maintain the aspect ratio of the bitmap, keeping it centered and intact
                drawing_options opts = option_scale_bmp(
                    SIZE_TILE / static_cast<float>(bmp_width),
                    SIZE_TILE / static_cast<float>(bmp_height));

                //drawing the bitmap at the centered position
                draw_bitmap(bitmap, (x + offset_x), (y + offset_y), opts);
            }
        }
    }
}

//passing king's color to check if the king is in danger
bool is_king_in_danger(piece_color king_color){
    //setting the kings position to -1 as default
    //if the king is not found, it will remain -1
    //means the king is not found
    //if the king is found, it will be set to the position of the king
    int king_row = -1, king_col = -1;

    //finding the king's position
    //looping through the chess board to find the king
    //looping through the rows
    for(int row = 0; row < 8 && king_row == -1; row++){
        //looping through the columns
        for(int col = 0; col < 8; col++){
            //checking if the piece is a king and its color is the same as the king's color
            //setting the row and column to the position of the king
            if(chess_board[row][col].type == KING && chess_board[row][col].color == king_color){
                king_row = row;
                king_col = col;
                break; //exiting the loop as we found the king
            }
        }
    }

    //if the king row is still -1, it means the king is not found
    if(king_row == -1){
        return false; //means the king is not found
    } 

    //this loop is to find the piece attacking the king
    //first we will loop through the chess board to find the piece attacking the king
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            //assigning the piece at the current position to the attacking_piece
            piece& attacking_piece = chess_board[r][c];

            //if the piece is not empty and its color is not the same as the king's color
            if(attacking_piece.color != NO_COLOR && attacking_piece.color != king_color){ 
                bool able_to_attack = false; //first assume the piece is not able to attack
            
                //switch case to check the type of piece
                switch(attacking_piece.type){
                    //checking the type of piece
                    case NO_PIECE:
                        able_to_attack = false;
                        break;
                    case PAWN:
                        able_to_attack = checking_pawn_moves(r, c, king_row, king_col, attacking_piece.color);
                        break;
                    case ROOK:
                        able_to_attack = checking_rook_moves(r, c, king_row, king_col);
                        break;
                    case KNIGHT:
                        able_to_attack = checking_knight_moves(r, c, king_row, king_col);
                        break;
                    case BISHOP:
                        able_to_attack = checking_bishop_moves(r, c, king_row, king_col);
                        break;
                    case QUEEN:
                        able_to_attack = checking_queen_moves(r, c, king_row, king_col);
                        break;
                    case KING:
                        able_to_attack = checking_king_moves(r, c, king_row, king_col);
                        break;
                }

            //if the piece is able to attack the king, return true
            if (able_to_attack){
                return true;
            }
        }
    }
    }

    return false;
}


//make a checkmate checking function
bool is_checkmate(piece_color king_color){
    //setting the king's position to (-1, -1) as default
    int king_row = -1, king_col = -1;
    //loop through the chess board to find the king
    //loop through the rows until the king is found
    for(int r = 0; r < SIZE_BOARD && king_row == -1; r++){
        for(int c = 0; c < SIZE_BOARD; c++){
            //if the piece found is a king and the color is the same color as the king we are searching for
            //then assigning the row and column to the position of the king, then breaking the loop
            if(chess_board[r][c].type == KING && chess_board[r][c].color == king_color){
                king_row = r;
                king_col = c;
                break;
            }
        }
    }
    //if the king is not found, return false
    if(king_row == -1){ 
        return false;
    } 

    // if the king is not in danger, return false
    //no check(mate) if the king is not in danger
    if(!is_king_in_danger(king_color)){
        return false;
    }

    //check all possible moves for the king if it can escape
    //loop through all the possible moves for the king
    //initiate the loops from r = (-1 to 1) and c = (-1 to 1) to check all the possible moves
    /*
    (-1,-1)  (-1,0)   (-1,1)
     (0,-1)   KING    (0,1)   [KING'S POSITION = (0,0)]
     (1,-1)  (1,0)    (1,1)
    */
    //if we started with r = 0, then we will only check 
    for(int r = -1; r <= 1; r++){
        for(int c = -1; c <= 1; c++){

            //case when the king is not moving
            //if the row and column are same, it means the king is not moving
            //so we will not check this case and continue to the next iteration
            if(r == 0 && c == 0){
                continue;
            }

            //adding the row and column to the king's current position to get the new position
            int new_row = king_row + r;
            int new_col = king_col + c; 

            //if the new position is out of bounds, continue to the next iteration
            //if either the new row or new column is less than 0 or greater than or equal to the size of the board
            //that means the new position is out of bounds
            if (new_row < 0 || new_row >= SIZE_BOARD || new_col < 0 || new_col >= SIZE_BOARD){
                continue;
            }
            
            //passing the new position to check if the king can move to that position
            //if checking_king_moves returns true, it means the king can move to that position
            if(checking_king_moves(king_row, king_col, new_row, new_col)){
                
                //setting the original piece at the new position to a variable
                piece original = chess_board[new_row][new_col];

                //moving the king to the new position
                chess_board[new_row][new_col] = chess_board[king_row][king_col];

                //setting the original position of the king to empty 
                chess_board[king_row][king_col] = { 
                    NO_PIECE, 
                    NO_COLOR 
                };

                //checking if the king is still in danger after moving to the new position
                //if the king is not in danger, it means the king can escape
                bool still_in_check = is_king_in_danger(king_color);

                //setting the original piece back to its original position
                chess_board[king_row][king_col] = chess_board[new_row][new_col];

                //setting the new position to the original piece
                //this is done to restore the original position of the king
                chess_board[new_row][new_col] = original;

                //if the king is not in danger, it means the king can escape
                //so we return false
                if(!still_in_check){
                    return false;
                }
            }
        }
    }

    //if the king is in danger and there are no possible moves for the king to escape
    //it means the king is in checkmate, so return true
    return true;
}

//function to display the timer for the game
void timer_for_game(){

    //defining the x and y position for the white player's timer
    int x_pos_white = (SIZE_BOARD * SIZE_TILE) + 20; //x position for white timer
    int y_pos_white = 430; //y position for white timer

    //defining the x and y position for the black player's timer
    int x_pos_black = (SIZE_BOARD * SIZE_TILE) + 20; //x position for black timer
    int y_pos_black = 20; //y position for black timer

    
    //calculating the time
    //calculating minutes for white player
    int mins_for_white = (time_left_white/60);
    //calculating seconds for white player
    int secs_for_white = (time_left_white % 60);

    //calculating minutes for black player
    int mins_for_black = (time_left_black/60);
    //calculating seconds for black player
    int secs_for_black = (time_left_black % 60);


    string time_for_white, time_for_black;
    //if the seconds are less than 10, add a leading zero to the seconds
    //re formatting the time to display in the format of MM:SS
    
    //for white player
    if(secs_for_white < 10){
        time_for_white = "White: " + to_string(mins_for_white) + ":0" + to_string(secs_for_white);
    }
    else{
        time_for_white = "White: " + to_string(mins_for_white) + ":" + to_string(secs_for_white);
    }

    //for black player
    if(secs_for_black < 10){
        time_for_black = "Black: " + to_string(mins_for_black) + ":0" + to_string(secs_for_black);
    }
    else{
        time_for_black = "Black: " + to_string(mins_for_black) + ":" + to_string(secs_for_black);
    }

    //setting the color for the text
    color white_turn_textclr, black_turn_textclr;
    //if its white's turn, set the text color to BLUE to indicate its white's turn
    if(is_white_turn){
        white_turn_textclr = COLOR_BLUE;
        black_turn_textclr = COLOR_BLACK;
    }
    //if its black's turn, set the text color to BLUE to indicate its black's turn
    else{
        white_turn_textclr = COLOR_BLACK;
        black_turn_textclr = COLOR_BLUE;
    }
    //if either player is out of time, set their text color to red
    if(mins_for_white == 0){
        white_turn_textclr = COLOR_RED; 
    }
    if(mins_for_black == 0){
        black_turn_textclr = COLOR_RED;
    }

    //drawing the timer box for white player
    fill_rectangle(white_turn_textclr, x_pos_white - 10, y_pos_white - 10, 200, 50);
    draw_rectangle(COLOR_BLACK, x_pos_white - 10, y_pos_white - 10, 200, 50);

    //drawing the timer box for black player
    fill_rectangle(black_turn_textclr, x_pos_black - 10, y_pos_black - 10, 200, 50);
    draw_rectangle(COLOR_BLACK, x_pos_black - 10, y_pos_black - 10, 200, 50);

    //drawing/writing the time left for each player in respective boxes/positions
    draw_text(time_for_white, COLOR_WHITE, x_pos_white, y_pos_white + 15);
    draw_text(time_for_black, COLOR_WHITE, x_pos_black, y_pos_black + 15);
}

//defining variables globally
bool display_check_message = false; //to display the check message, initially false
string check_message = ""; //to define the check message, initially empty
double check_message_time = 0; //to check the time for displaying the message, initially 0

int main(){
    //opening the window named "SplashKit Chess" of the size 880x480
    //more width for the quote/message/timer to display
    open_window("SplashKit Chess", (SIZE_BOARD * SIZE_TILE) + 400, SIZE_BOARD * SIZE_TILE);

    //loading chess pieces' images 
    chess_pieces_images();

    //initializing the chess board
    making_chess_board();

    //setting the initially selected row and column to -1
    //initially, the user has not selected any piece
    //so the selected row and column are -1
    //if it was 0, it would mean the user has selected a piece at (0,0)
    //which will cause an error/bug
    int selected_row = -1;
    int selected_col = -1;
    bool piece_selected = false; //no piece is selected by default

    //timer for displaying quotes
    timer my_timer = create_timer("quote_timer");
    start_timer(my_timer); //starting the timer

    //last quote time to display
    //timer ticks returns the number of ticks since the timer was started
    //this will help us to keep track of the time
    double last_quote_time = timer_ticks(my_timer);

    //choosing a random quote out of the quotes array
    int current_quote_index = rnd(NUM_OF_QUOTES);

    //creating a timer for the chess game
    //this timer will be used to keep track of the time left for each player
    timer chess_timer = create_timer("chess_timer");
    start_timer(chess_timer); //starting the chess timer
    double last_chess_time = timer_ticks(chess_timer); //last chess time to display

    //setting the total time for each player
    //in chess, the white player always starts first, so is_white_turn is true
    //initially, the white and black players have 10 minutes each
    time_left_white = TOTAL_TIME;
    time_left_black = TOTAL_TIME;
    is_white_turn = true; //white's turn to play
    is_black_turn = false; //black's turn to play

    //while loop to keep the window open until the user closes it
    while(!window_close_requested("SplashKit Chess")){

        //process events to handle user input
        process_events();

        //initialising timers
        //defining current time and elapsed time to keep track of the game time
        double current_time = timer_ticks(chess_timer);
        //elapsed time is the subtraction of current time and last tick
        double elapsed_time = current_time - last_chess_time;
        //static cast to strictly keep it double
        elapsed_time = static_cast<double>(elapsed_time) / 1000.0; //converting to seconds

        //if the elapsed time crosses 1 second, decrease the time remaining by 1 as every second passe
        if(elapsed_time >= 1.0){
            //if its white's turn, then decrement the time left by 1 as every second passes
            if(is_white_turn){
                time_left_white -= 1.0;
                //if the time left for white is less than or equal to 0, then set it to 0
                //the game is over and black wins as white ran out of time
                if(time_left_white <= 0){
                    time_left_white = 0;
                    //setting the display check message to true
                    display_check_message = true;
                    //setting the check message to display as "Time's up! Black wins!"
                    check_message = "Time's up! Black wins!";
                    //setting the check message time to the current time
                    check_message_time = timer_ticks(my_timer);
                }
            }
            //if its black's turn
            else{
                //same method as above
                //decrement the time left for black by 1
                time_left_black -= 1.0;
                if(time_left_black <= 0){
                    time_left_black = 0;
                    display_check_message = true;
                    //setting the check message to display as "Time's up! White wins!"
                    check_message = "Time's up! White wins!";
                    check_message_time = timer_ticks(my_timer);
                }
            }

            //setting the last chess time as the current time
            last_chess_time = current_time;
        }


        //mouse input for user to select a piece
        //mouse_clicked checks if the left mouse button is clicked
        //mouse_x() and mouse_y() return the x and y position of the mouse
        if(mouse_clicked(LEFT_BUTTON)){

            //calculating the column and row of the tile clicked
            //the column is the x position of the mouse divided by the size of the tile
            //the row is the y position of the mouse divided by the size of the tile
            int col = int(mouse_x() / SIZE_TILE);
            int row = int(mouse_y() / SIZE_TILE);

            //if the user has selected a piece 
            if(!piece_selected){
                
                //if the piece is not empty, it means the user has selected a piece
                //piece selected is true
                //selected_row and selected_col are set to the row and column of the piece selected
                if(chess_board[row][col].type != chess_piece(NO_PIECE)){
                    piece_selected = true;
                    selected_row = row;
                    selected_col = col;
                }
            }

            //if the user has already selected a piece
            //and the user clicks on a tile means the user wants to move the piece
            else{

                //defining where the piece is moving from and where it is moving to
                //from_piece is the piece selected by the user
                //to_piece is the piece at the new position
                piece from_piece = chess_board[selected_row][selected_col];
                piece to_piece = chess_board[row][col];

                //if the destination square is empty or has a piece of the same color
                if(to_piece.type == chess_piece(NO_PIECE) || to_piece.color != from_piece.color){
                    bool is_valid_move = false; //initially, the move is not valid

                    //if the piece moving is a pawn, check if the move is valid
                    if(from_piece.type == chess_piece(PAWN)){
                        is_valid_move = checking_pawn_moves(selected_row, selected_col, row, col, from_piece.color);
                        //return true/false if the move is valid or not
                        }

                    //if the piece moving is a rook, check if the move is valid
                    else if(from_piece.type == chess_piece(ROOK)){
                        is_valid_move = checking_rook_moves(selected_row, selected_col, row, col);
                        //return true/false if the move is valid or not
                    }

                    //if the piece moving is a knight, check if the move is valid
                    else if(from_piece.type == chess_piece(KNIGHT)){
                        is_valid_move = checking_knight_moves(selected_row, selected_col, row, col);
                        //return true/false if the move is valid or not
                    }

                    //if the piece moving is a bishop, check if the move is valid
                    else if(from_piece.type == chess_piece(BISHOP)){
                        //return true/false if the move is valid or not
                        is_valid_move = checking_bishop_moves(selected_row, selected_col, row, col);
                    }

                    //if the piece moving is a queen, check if the move is valid
                    else if(from_piece.type == chess_piece(QUEEN)){
                        is_valid_move = checking_queen_moves(selected_row, selected_col, row, col);
                        //return true/false if the move is valid or not
                    }
                    //if the piece moving is a king, check if the move is valid
                    else if(from_piece.type == chess_piece(KING)){
                        //return true/false if the move is valid or not
                        is_valid_move = checking_king_moves(selected_row, selected_col, row, col);
                    }

                    //if a valid move is made, move the piece
                    if(is_valid_move){ 
                        //setting the piece at the new position to the piece selected by the user
                        chess_board[row][col] = from_piece;
                        //setting the piece at the old position to empty, removing the piece from the old position
                        chess_board[selected_row][selected_col] = { 
                            chess_piece(NO_PIECE), 
                            piece_color(NO_COLOR) 
                        };

                        //checking if the king is in checkmate position
                        //if the king in checkmate position is white, then display the message that black wins
                        if(is_checkmate(piece_color(WHITE))){
                            display_check_message = true;
                            check_message = "Checkmate! Black wins!";
                            check_message_time = timer_ticks(my_timer);
                        }
                        //if the king in checkmate position is black, then display the message that white wins
                        else if(is_checkmate(piece_color(BLACK))){
                            display_check_message = true;
                            check_message = "Checkmate! White wins!";  
                            check_message_time = timer_ticks(my_timer);
                        }

                        //checking if the king is in danger
                        //if the white king is in danger, display the message that white king is in check
                        else if(is_king_in_danger(piece_color(WHITE))){
                            display_check_message = true;
                            check_message = "White king is in check!";
                            check_message_time = timer_ticks(my_timer);
                        }
                        //if the black king is in danger, display the message that black king is in check
                        else if(is_king_in_danger(piece_color(BLACK))){
                            display_check_message = true;
                            check_message = "Black king is in check!";
                            check_message_time = timer_ticks(my_timer);
                        }

                    }
                    //the below code switches the turn of the player
                    //if the piece selected is white, then set it to black
                    //if the piece selected is black, then set it to white
                    //this is done to switch the turn of the player
                    if(is_white_turn){
                        is_white_turn = false; 
                        is_black_turn = true;
                    }
                    else{
                        is_white_turn = true;
                        is_black_turn = false;
                    }
                }
                //piece selected is set to false as the user has moved the piece
                //if the user clicks on the same piece again without moving it, it will be deselected 
                piece_selected = false;
            }
        }

        //setting the background color of the window
        clear_screen(COLOR_GRAY);
        //drawing the chess board
        //if i draw chess board before defining the pieces, the pieces will be drawn behind the board
        //so i have to define the pieces first and then draw the board
        //this is done to ensure that the pieces are drawn on top of the board
        draw_chess_board();

        //displaying the timer for the game
        timer_for_game();

        //checking if the timer has reached 4 seconds
        //if the elapsed time is greater than 4 seconds, then display a new quote
        if(timer_ticks(my_timer) - last_quote_time > 4000){
            //choosing a random quote out of the quotes array
            current_quote_index = rnd(NUM_OF_QUOTES);
            //resetting the timer
            //this will reset the timer to 0
            last_quote_time = timer_ticks(my_timer);
        }

        //displaying the quote using the display_quote function
        display_quote(QUOTES, NUM_OF_QUOTES, current_quote_index);
        
    

        //displaying the check message if it is true
        if(display_check_message){
            //the message will be displayed for 3 seconds
            //checking if the elapsed time has reached 3 seconds
            if(timer_ticks(my_timer) - check_message_time < 3000){
                
                //positioning the message box
                //the box will be displayed a bit below the quote-box to avoid overlapping
                int quote_x = (SIZE_BOARD * SIZE_TILE) + 20;
                int box_y = (SIZE_BOARD * SIZE_TILE) / 1.5;

                //drawing the message box
                //the box will be red in color to indicate an alert with black border
                fill_rectangle(COLOR_RED, quote_x - 10, box_y, 380, 80);
                draw_rectangle(COLOR_BLACK, quote_x - 10, box_y, 380, 80);
                
                //displaying the warning message
                draw_text("Hey User!:", COLOR_WHITE, quote_x, box_y + 10);
                draw_text(check_message, COLOR_WHITE, quote_x, box_y + 40);
            } 
            else{
                //else if the elapsed time is greater than 3 seconds, then hide the message
                //this is done to avoid the message being displayed again
                display_check_message = false;
            }
        }

        //refreshing the screen
        refresh_screen(60); 
    }

    return 0;

}