#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution{
public:
	bool isValidSudoku(vector<vector<char>>& board){
		unordered_map<char,int> s_map = {{'1',0},{'2',0},{'3',0},
                                        	 {'4',0},{'5',0},{'6',0},
                                        	 {'7',0},{'8',0},{'9',0}};
		vector<unordered_map<char,int>> row_map(9,s_map);
		vector<unordered_map<char,int>> col_map(9,s_map);
		vector<unordered_map<char,int>> square_map(9,s_map);
		
		//validating rows
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(board[i][j] == '.')
					continue;
				row_map[i][board[i][j]]++;
			}
		}
		for(int i=0;i<9;i++){
			for(const auto& r: row_map[i]){
				if(r.second > 1)
					return false;
			}
		}
		
	        cout << "Rows are valid"<< endl;
		//validating columns
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(board[j][i] == '.')
					continue;
				col_map[i][board[j][i]]++;
			}
		}
		for(int i=0;i<9;i++){
			for(const auto& r: col_map[i]){
				if(r.second > 1)
					return false;
			}
		}

	        cout << "Rows and columns are valid"<< endl;
		//validating sqares
		for(int k=0;k<9;k++){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					int row = ((k/3)*3)+i;
					int col = ((k%3)*3)+j;
					if(board[row][col] == '.')
						continue;
					square_map[k][board[row][col]]++;
				}
			}
		}
		for(int i=0;i<9;i++){
			for(const auto& r : square_map[i]){
				if(r.second >1)
					return false;
			}
		}
	        cout << "Rows, columns and squares are valid"<< endl;

		return true;
		
	}
};

int main(){
	Solution s;
	vector<vector<char>> board   = {{'1','2','.','.','3','.','.','.','.'},
					{'4','.','.','5','.','.','.','.','.'},
					{'.','9','8','.','.','.','.','.','3'},
					{'5','.','.','.','6','.','.','.','4'},
					{'.','.','.','8','.','3','.','.','5'},
					{'7','.','.','.','2','.','.','.','6'},
					{'.','.','.','.','.','.','2','.','.'},
					{'.','.','.','4','1','9','.','.','8'},
					{'.','.','.','.','8','.','.','7','9'}};
	cout << (s.isValidSudoku(board)?"yes, its valid":"no, its invalid" )<< endl;
	return 0;
}
