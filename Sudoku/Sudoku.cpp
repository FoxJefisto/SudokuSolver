#include <iostream>
#include <vector>
#include <optional>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


/*
    Write a program to solve a Sudoku puzzle by filling the empty cells.

    A sudoku solution must satisfy all of the following rules:

    Each of the digits 1-9 must occur exactly once in each row.
    Each of the digits 1-9 must occur exactly once in each column.
    Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
    The '.' character indicates empty cells.
*/

/*
    Input: board = [
        ["5","3",".",   ".","7",".",    ".",".","."],
        ["6",".",".",   "1","9","5",    ".",".","."],
        [".","9","8",   ".",".",".",    ".","6","."],

        ["8",".",".",   ".","6",".",    ".",".","3"],
        ["4",".",".",   "8",".","3",    ".",".","1"],
        ["7",".",".",   ".","2",".",    ".",".","6"],

        [".","6",".",   ".",".",".",    "2","8","."],
        [".",".",".",   "4","1","9",    ".",".","5"],
        [".",".",".",   ".","8",".",    ".","7","9"]
    ]
    Output: [
        ["5","3","4",   "6","7","8",    "9","1","2"],
        ["6","7","2",   "1","9","5",    "3","4","8"],
        ["1","9","8",   "3","4","2",    "5","6","7"],

        ["8","5","9",   "7","6","1",    "4","2","3"],
        ["4","2","6",   "8","5","3",    "7","9","1"],
        ["7","1","3",   "9","2","4",    "8","5","6"],

        ["9","6","1",   "5","3","7",    "2","8","4"],
        ["2","8","7",   "4","1","9",    "6","3","5"],
        ["3","4","5",   "2","8","6",    "1","7","9"]
    ]
*/
class Solution {
public:
    /// <summary>
    /// Проверка возможности подстановки цифры в ячейку
    /// </summary>
    /// <param name="board">текущее поле</param>
    /// <param name="row">номер строки</param>
    /// <param name="col">номер столбца</param>
    /// <param name="digit">цифра</param>
    /// <returns></returns>
    bool checkDigit(vector<vector<char>>& board, int row, int col, char digit) {
        int iSquare = row / 3 * 3;
        int jSquare = col / 3 * 3;
        for (int i = 0; i < board.size(); i++)
        {
            //Проверка строк
            if (board[i][col] == digit)
                return false;
            //Проверка столбцов
            if (board[row][i] == digit)
                return false;
            //Проверка квадрата
            if (board[iSquare + i % 3][jSquare + i / 3] == digit)
                return false;
        }
        return true;
    }
    /// <summary>
    /// Поиск ячейки с пустым полем (с точкой)
    /// </summary>
    /// <param name="board">текущее поле</param>
    /// <returns></returns>
    optional<pair<int, int>> findEmptyPos(vector<vector<char>>& board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    return make_pair(i, j);
                }
            }
        }
        return std::nullopt;
    }
    /// <summary>
    /// Рекурсивная функция поиска решения судоку
    /// </summary>
    /// <param name="board">текущее поле</param>
    /// <returns></returns>
    bool solve(vector<vector<char>>& board)
    {
        auto dotPos = findEmptyPos(board);
        if (!dotPos.has_value()) // Если пустых ячеек не осталось, значит решение найдено
            return true;
        auto [x, y] = dotPos.value();
        for (char currentDigit = '1'; currentDigit < '1' + board.size(); currentDigit++)
        {
            bool isValid = checkDigit(board, x, y, currentDigit);
            if (isValid) 
            {
                board[x][y] = currentDigit;
                if(solve(board)) // Рекурсивный вызов solve. solve вернет true, когда свободных ячеек не останется, а значит это и будет решением.
                {
                    return true;
                }
                //В ином случае текущая подстановка в ячейку неверна, нужно перебирать другие варианты. Возвращаем ячейку в исходное состояние
                board[x][y] = '.';
            }
        }
        return false;
    }
};

/// <summary>
/// класс для ввода и вывода поля
/// </summary>
class BoardManager
{
public:
    /// <summary>
    /// создание нового поля
    /// </summary>
    /// <param name="rows">кол-во строк</param>
    /// <param name="cols">кол-во столбцов</param>
    /// <returns></returns>
    vector<vector<char>> createBoard(int rows, int cols)
    {
        std::vector<std::vector<char>> board(rows, std::vector<char>(cols, '.'));
        return board;
    }
    /// <summary>
    /// ввод поля из файла
    /// </summary>
    /// <param name="fileName">путь к файлу</param>
    /// <returns></returns>
    vector<vector<char>> inputBoardFromFile(const string& fileName)
    {
        auto board = createBoard(9, 9);
        std::ifstream in(fileName);
        if (in.is_open())
        {
            for (auto& row : board)
            {
                for (auto& elem : row)
                {
                    in >> elem;
                }
            }
        }
        in.close();
        return board;
    }
    /// <summary>
    /// ввод поля из консоли
    /// </summary>
    /// <returns></returns>
    vector<vector<char>> inputBoardFromConsole()
    {
        auto board = createBoard(9, 9);
        for (auto& row : board)
        {
            for (auto& elem : row)
            {
                cin >> elem;
            }
        }
        return board;
    }
    /// <summary>
    /// вывод поля в консоль
    /// </summary>
    /// <param name="board">текущее поле</param>
    void printBoard(const vector<vector<char>>& board) {
        for(auto row : board)
        {
            for (auto elem : row)
            {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Solution solver;
    BoardManager boardMgr;
    vector<vector<char>> board =
    {
        {'5','3','.',   '.','7','.',    '.','.','.'},
        {'6','.','.',   '1','9','5',    '.','.','.'},
        {'.','9','8',   '.','.','.',    '.','6','.'},

        {'8','.','.',   '.','6','.',    '.','.','3'},
        {'4','.','.',   '8','.','3',    '.','.','1'},
        {'7','.','.',   '.','2','.',    '.','.','6'},

        {'.','6','.',   '.','.','.',    '2','8','.'},
        {'.','.','.',   '4','1','9',    '.','.','5'},
        {'.','.','.',   '.','8','.',    '.','7','9'}
    };
    //auto board = boardMgr.inputBoardFromFile("sudoku.txt");
    cout << "Original board\n";
    boardMgr.printBoard(board);
    solver.solve(board);
    cout << setw(18) << setfill('*') << "\n";
    cout << "Solved board\n";
    boardMgr.printBoard(board);

    return 0;
}