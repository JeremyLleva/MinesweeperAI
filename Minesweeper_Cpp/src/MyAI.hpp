// ======================================================================
// FILE:        MyAI.hpp
//
// AUTHOR:      Jian Li
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#ifndef MINE_SWEEPER_CPP_SHELL_MYAI_HPP
#define MINE_SWEEPER_CPP_SHELL_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class MyAI : public Agent
{
public:
	
    MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY );

    Action getAction ( int number ) override;


    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
	
		bool checkDone();
		void pAllMine();
		void checkZeros();
		void checkOneOne();
		void checkOneTwo();
		void checkOneTwoOne();
		void checkOneTwoTwoOne();
		void guess();
		
		void allMinesFlagged();
		
		vector<vector<int>> map;
		vector<vector<int>> mapPattern;
		vector<vector<int>> iMap;
		
		bool patOneTwoTwoOne = false;
		int ottoXa;
		int ottoXb;
		int ottoYa;
		int ottoYb;
		
		bool zeroClear = false;
		int zeroX;
		int zeroY;
			
		int guessX;
		int guessY;
		
		bool flaggedClear = false;
		int flagX;
		int flagY;
		
		bool patOneTwoOne = false;
		int otoXa;
		int otoXb;
		
		int otoYa;
		int otoYb;

		void updateMap();
		
		bool patOneOne = false;
		int oneoneX;
		int oneoneY;
		
		int onetwoX;
		int onetwoY;
		bool patOneTwo = false;

		
		bool surroundMine = false;
		int surroundX;
		int surroundY;
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

#endif //MINE_SWEEPER_CPP_SHELL_MYAI_HPP
