// ======================================================================
// FILE:        MyAI.cpp
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

#include "MyAI.hpp"

MyAI::MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ) : Agent()
{
    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================
	
	rowDimension = _rowDimension;
	colDimension = _colDimension;
	totalMines = _totalMines;
	agentX = _agentX;
	agentY = _agentY;
	
	vector<vector<int> > tempmap(rowDimension, vector<int>(colDimension, -1));
	
	map = tempmap;
	mapPattern = tempmap;
	iMap = tempmap;
	
    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================
};

Agent::Action MyAI::getAction( int number )
{
    // ======================================================================
    // YOUR CODE BEGIN
    // ======================================================================
	// 
	
	//-1 = covered
	//-2 = flag
	if(number != -1)
	{
		map[agentY][agentX] = number;
		iMap[agentY][agentX] = number;
	}

	if(iMap[agentY][agentX] == 0 && zeroClear == false)
	{
		zeroClear = true;
		zeroX = agentX;
		zeroY = agentY;
		mapPattern[agentY][agentX] = 1;
	}
	
	
	//clear everything around that number
	while(zeroClear == true)
	{
		//top left
		if((zeroY + 1 < rowDimension) && (zeroX - 1 >= 0) && (iMap[zeroY + 1][zeroX - 1] == -1))
		{
			agentY = zeroY + 1;
			agentX = zeroX - 1;
			return{UNCOVER, agentX, agentY};
		}
		//top middle
		if((zeroY + 1 < rowDimension) && (zeroX < colDimension) && (iMap[zeroY + 1][zeroX] == -1))
		{
			agentY = zeroY + 1;
			agentX = zeroX;
			return{UNCOVER, agentX, agentY};
		}
		//top right
		if((zeroY + 1 < rowDimension) && (zeroX + 1 < colDimension) && (iMap[zeroY + 1][zeroX + 1] == -1))
		{
			agentY = zeroY + 1;
			agentX = zeroX + 1;
			return{UNCOVER, agentX, agentY};
		}
		//middle left
		if((zeroY < rowDimension) && (zeroX - 1 >= 0) && (iMap[zeroY][zeroX - 1] == -1))
		{
			agentY = zeroY;
			agentX = zeroX - 1;
			return{UNCOVER, agentX, agentY};
		}
		//middle right
		if((zeroY < rowDimension) && (zeroX + 1 < colDimension) && (iMap[zeroY][zeroX + 1] == -1))
		{
			agentY = zeroY;
			agentX = zeroX + 1;
			return{UNCOVER, agentX, agentY};
		}
		// bottom left
		if((zeroY - 1 >= 0) && (zeroX - 1 >= 0) && (iMap[zeroY - 1][zeroX - 1] == -1))
		{
			agentY = zeroY - 1;
			agentX = zeroX - 1;
			return{UNCOVER, agentX, agentY};
		}
		//bottom middle
		if((zeroY - 1 >= 0) && (zeroX < colDimension) && (iMap[zeroY - 1][zeroX] == -1))
		{
			agentY = zeroY - 1;
			agentX = zeroX;
			return{UNCOVER, agentX, agentY};
		}
		//bottom right
		if((zeroY - 1 >= 0) && (zeroX + 1 < colDimension) && (iMap[zeroY - 1][zeroX + 1] == -1))
		{
			agentY = zeroY - 1;
			agentX = zeroX + 1;
			return{UNCOVER, agentX, agentY};
		}
		zeroClear = false;
		checkZeros();
	}
	
	//Checks if any tile is completely surrounded by uncovered mines
	if(surroundMine == false)
	{
		pAllMine();
	}
	
	//If there is loop through and flag all mines
	while(surroundMine == true)
	{
		//top left
		if((surroundY + 1 < rowDimension) && (surroundX - 1 >= 0) && (iMap[surroundY + 1][surroundX - 1] == -1))
		{
			agentY = surroundY + 1;
			agentX = surroundX - 1;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		//top middle
		if((surroundY + 1 < rowDimension) && (surroundX < colDimension) && (iMap[surroundY + 1][surroundX] == -1))
		{
			agentY = surroundY + 1;
			agentX = surroundX;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
			
		}
		//top right
		if((surroundY + 1 < rowDimension) && (surroundX + 1 < colDimension) && (iMap[surroundY + 1][surroundX + 1] == -1))
		{
			agentY = surroundY + 1;
			agentX = surroundX + 1;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		//middle left
		if((surroundY < rowDimension) && (surroundX - 1 >= 0) && (iMap[surroundY][surroundX - 1] == -1))
		{
			agentY = surroundY;
			agentX = surroundX - 1;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		//middle right
		if((surroundY < rowDimension) && (surroundX + 1 < colDimension) && (iMap[surroundY][surroundX + 1] == -1))
		{
			agentY = surroundY;
			agentX = surroundX + 1;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		// bottom left
		if((surroundY - 1 >= 0) && (surroundX - 1 >= 0) && (iMap[surroundY - 1][surroundX - 1] == -1))
		{
			agentY = surroundY - 1;
			agentX = surroundX - 1;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		//bottom middle
		if((surroundY - 1 >= 0) && (surroundX < colDimension) && (iMap[surroundY - 1][surroundX] == -1))
		{
			agentY = surroundY - 1;
			agentX = surroundX;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		//bottom right
		if((surroundY - 1 >= 0) && (surroundX + 1 < colDimension) && (iMap[surroundY - 1][surroundX + 1] == -1))  
		{
			agentY = surroundY - 1;
			agentX = surroundX + 1;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		surroundMine = false;
		pAllMine();
	}
	
	//Checks if any tile is completely surrounded by uncovered mines
	if(flaggedClear == false)
	{
		allMinesFlagged();
	}
	
	
	//Loops through tiles that have all mines flagged already and clears non flagged spots
	while(flaggedClear == true)
	{
		//top left
		if((flagY + 1 < rowDimension) && (flagX - 1 >= 0) && (iMap[flagY + 1][flagX - 1] == -1))
		{
			agentY = flagY + 1;
			agentX = flagX - 1;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		//top middle
		if((flagY + 1 < rowDimension) && (flagX < colDimension) && (iMap[flagY + 1][flagX] == -1))
		{
			agentY = flagY + 1;
			agentX = flagX;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
			
		}
		//top right
		if((flagY + 1 < rowDimension) && (flagX + 1 < colDimension) && (iMap[flagY + 1][flagX + 1] == -1))
		{
			agentY = flagY + 1;
			agentX = flagX + 1;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		//middle left
		if((flagY < rowDimension) && (flagX - 1 >= 0) && (iMap[flagY][flagX - 1] == -1))
		{
			agentY = flagY;
			agentX = flagX - 1;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		//middle right
		if((flagY < rowDimension) && (flagX + 1 < colDimension) && (iMap[flagY][flagX + 1] == -1))
		{
			agentY = flagY;
			agentX = flagX + 1;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		// bottom left
		if((flagY - 1 >= 0) && (flagX - 1 >= 0) && (iMap[flagY - 1][flagX - 1] == -1))
		{
			agentY = flagY - 1;
			agentX = flagX - 1;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		//bottom middle
		if((flagY - 1 >= 0) && (flagX < colDimension) && (iMap[flagY - 1][flagX] == -1))
		{
			agentY = flagY - 1;
			agentX = flagX;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		//bottom right
		if((flagY - 1 >= 0) && (flagX + 1 < colDimension) && (iMap[flagY - 1][flagX + 1] == -1))  
		{
			agentY = flagY - 1;
			agentX = flagX + 1;
			//map[agentY][agentX] = -2;
			//mapPattern[agentY][agentX] = -2;
			return{UNCOVER, agentX, agentY};
		}
		flaggedClear = false;
		allMinesFlagged();
	}

		
	updateMap();
	
	if(patOneTwoTwoOne == false)
	{
		checkOneTwoTwoOne();
	}
	if(patOneTwoTwoOne == true)
	{
		if(iMap[ottoYa][ottoXa] == -1)
		{
			agentX = ottoXa;
			agentY = ottoYa;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		
		if(iMap[ottoYb][ottoXb] == -1)
		{
			agentX = ottoXb;
			agentY = ottoYb;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			patOneTwoTwoOne = false;
			return{FLAG, agentX, agentY};
		}
		patOneTwoTwoOne = false;
	}
	if(patOneTwoOne == false)
	{
		checkOneTwoOne();
	}
	if(patOneTwoOne == true)
	{
		if(iMap[otoYa][otoXa] == -1)
		{
			agentX = otoXa;
			agentY = otoYa;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			return{FLAG, agentX, agentY};
		}
		if(iMap[otoYb][otoXb] == -1)
		{
			agentX = otoXb;
			agentY = otoYb;
			map[agentY][agentX] = -2;
			iMap[agentY][agentX] = -2;
			patOneTwoOne = false;
			return{FLAG, agentX, agentY};
		}
		patOneTwoOne = false;
	}
	
	if(patOneOne == false)
	{
		checkOneOne();
	}
	
	if(patOneOne == true)
	{
		patOneOne = false;
		agentY = oneoneY;
		agentX = oneoneX;
		return{UNCOVER, agentX, agentY};
	}
	if(patOneTwo == false)
	{
		checkOneTwo();
	}
	
	if(patOneTwo == true)
	{
		patOneTwo = false;
		agentY= onetwoY;
		agentX = onetwoX;
		map[agentY][agentX] = -2;
		iMap[agentY][agentX] = -2;
		return{FLAG, agentX, agentY};
	}

	if(checkDone())
	{
		return{LEAVE, -1, -1};
	}
	
	guess();
	

	agentX = guessX;
	agentY = guessY;
	
	return {UNCOVER, agentX, agentY};


    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

}

// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

//Checks if any uncovered tile is free
void MyAI::pAllMine()
{
	for (int aX = 0; aX < colDimension; aX++ )
	{
		for (int aY = 0; aY < rowDimension; aY++ )
		{
			if(iMap[aY][aX] != 0 && iMap[aY][aX] != -1 && mapPattern[aY][aX] != -2)
			{
				int sMines = iMap[aY][aX];
				int cCovered = 0;
				//top right
				if((aY + 1 < rowDimension) && (aX - 1 >= 0) && ((iMap[aY + 1][aX - 1] == -1) || (iMap[aY +1][aX - 1] == -2)))
				{
					cCovered++;
				}
				//top middle
				if((aY + 1 < rowDimension) && (aX < colDimension) && ((iMap[aY + 1][aX] == -1) || (iMap[aY + 1][aX] == -2)))
				{
					cCovered++;
				}
				//top right
				if((aY + 1 < rowDimension) && (aX + 1 < colDimension) && ((iMap[aY + 1][aX + 1] == -1) || (iMap[aY + 1][aX + 1] == -2)))
					{
					cCovered++;
				}
				//middle left
				if((aY < rowDimension) && (aX - 1 >= 0) && ((iMap[aY][aX - 1] == -1) || (iMap[aY][aX - 1] == -2)))
				{
					cCovered++;
				}
				//middle right
				if((aY < rowDimension) && (aX + 1 < colDimension) && ((iMap[aY][aX + 1] == -1) || (iMap[aY][aX + 1] == -2)))
				{
					cCovered++;
				}
				// bottom left
				if((aY - 1 >= 0) && (aX - 1 >= 0) && ((iMap[aY - 1][aX - 1] == -1) || (iMap[aY - 1][aX - 1] == -2)))
				{
					cCovered++;
				}
				//bottom middle
				if((aY - 1 >= 0) && (aX < colDimension) && ((iMap[aY - 1][aX] == -1) || (iMap[aY - 1][aX] == -2)))
				{
					cCovered++;
				}
				//bottom right
				if((aY - 1 >= 0) && (aX + 1 < colDimension) && ((iMap[aY - 1][aX + 1] == -1) || (iMap[aY - 1][aX + 1] == -2)))
				{	
					cCovered++;
				}
				if(cCovered == sMines)
				{
					surroundX = aX;
					surroundY = aY;
					surroundMine = true;
					mapPattern[aY][aX] = -2;
					return;
				}
			}
		}
	}

}

//Looks for any zero tiles and reveals all surrounding tiles
void MyAI::checkZeros()
{
	
	for ( int x = 0; x < colDimension; x++ )
    {
        for ( int y = 0; y < rowDimension; y++ )
		{
            if((iMap[y][x] == 0) && (mapPattern[y][x] == -1))
			{
				zeroX = x;
				zeroY = y;
				zeroClear = true;
				mapPattern[y][x] = 1;
				return;
			}
		}
    }
	
}	

//looks for any 1-1 pattern 
void MyAI::checkOneOne()
{
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			//check if theres a one and the next tile is not oob
			if(map[y][x] == 1 && x+1 < colDimension)
			{
				//now check if the next tile over is a 1
				if(map[y][x+1] == 1)
				{
					//first check corner cases
					//if 1-1 pattern is at top left. mine is on bottom right
					if(y + 1 >= rowDimension && x - 1 < 0 && map[y-1][x+2] == -1 && map[y][x+2] != -1)
					{
						oneoneX = x + 2;
						oneoneY = y - 1;
						patOneOne = true;
						return;
					}
					//if 1-1 is at top right, mine is on bottom left
					if( y + 1 >= rowDimension &&  x + 2 >= colDimension && map[y-1][x-1] == -1 && map[y][x-1] != -1)
					{
						oneoneX = x - 1;
						oneoneY = y - 1;
						patOneOne = true;
						return;
					}
					//if 1-1 is bottom left, mine top right
					if(y-1 < 0 && x - 1 < 0 && map[y+1][x+2] == -1 && map[y][x+2] != -1 )
					{
						oneoneX = x + 2;
						oneoneY = y + 1;
						patOneOne = true;
						return;
					}
					//if 1-1 is bottom right, mine top left
					if(y-1 < 0 && x + 2 >= colDimension && map[y+1][x-1] == -1 && map[y][x-1] != -1)
					{
						oneoneX = x-1;
						oneoneY = y+1;
						patOneOne = true;
						return;
					}
					//now check roof patterns
					//if roof above
					if(y + 1 >= rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if roof is above and opensquare to left
						if((map[y-1][x-1] != -1) && (map[y][x-1] != -1) && (map[y][x+2] != -1) && map[y-1][x+2] == -1)
						{
							oneoneX = x + 2;
							oneoneY = y - 1;
							patOneOne = true;
							return;
						}
						//if roof is above and opensquare to right
						if((map[y-1][x+2] != -1) && (map[y][x-1] != -1) && (map[y][x+2] != -1) && map[y-1][x-1] == -1)
						{
							oneoneX = x-1;
							oneoneY = y-1;
							patOneOne = true;
							return;
						}
					}
					//if roof below
					if(y - 1 < 0 && x - 1 >= 0 && x + 2 < colDimension)
					{
		
						//if roof is below and opensquare to left
						if((map[y+1][x-1] != -1) && (map[y][x-1] != -1) && (map[y][x+2] != -1) && map[y+1][x+2] == -1)
						{
							oneoneX = x + 2;
							oneoneY = y + 1;
							patOneOne = true;
							return;
						}
						//if roof is above and opensquare to right
						if((map[y+1][x+2] != -1) && (map[y][x+2] != -1) && (map[y][x-1] != -1) && map[y+1][x-1] == -1)
						{
							oneoneX = x-1;
							oneoneY = y+1;
							patOneOne = true;
							return;
						}
					}
					
					//now check inner patterns
					if(y - 1 >= 0 && y + 1 < rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if uncovered tiles are below
						if((map[y-1][x-1] != -1)  && (map[y-1][x] != -1) && (map[y-1][x+1] != -1) && (map[y-1][x+2] != -1) &&
						(map[y][x-1] != -1) && (map[y][x+2] !=-1))
						{
							//if uncovered tiles on left 
							if((map[y+1][x-1] != -1) && map[y+1][x+2] == -1)
							{
								oneoneX = x+2;
								oneoneY = y+1;
								patOneOne = true;
								return;
							}
							//uncovered right
							if((map[y+1][x+2] != -1) && map[y+1][x-1] == -1)
							{
								oneoneX = x -1;
								oneoneY = y+1;
								patOneOne = true;
								return;
							}
						}
					
					//if uncovered tiles are above
						if((map[y+1][x-1] != -1) && (map[y+1][x] != -1) && (map[y+1][x+1] != -1) && (map[y+1][x+2] != -1)&& map[y][x-1] != -1 
							 && (map[y][x+2] !=-1))
						{
							//if uncovered tiles on left 
							if((map[y-1][x-1] != -1) && map[y-1][x+2] == -1)
							{
								oneoneX = x+2;
								oneoneY = y-1;
								patOneOne = true;
								return;
							}
							if((map[y-1][x+2] != -1) && map[y-1][x-1] == -1)
							{
								oneoneX = x -1;
								oneoneY = y-1;
								patOneOne = true;
								return;
							}
						}
					}
					
				}
				//now check vertical
				if(map[y][x] == 1 && y - 1 > 0)
				{
					if(map[y-1][x] == 1)
					{
						//first corner situations
						
						//top left
						if(y+1 >= rowDimension && x-1 < 0 && map[y-2][x] != -1 && map[y-2][x+1] == -1)
						{ 
							oneoneX = x +1;
							oneoneY = y-2;
							patOneOne = true;
							return;
						}
						//top right
						if(y + 1 >= rowDimension&& x+1 >= colDimension && map[y-2][x] != -1 && map[y-2][x-1] == -1)
						{
							oneoneX = x -1;
							oneoneY = y - 2;
							patOneOne = true;
							return;
						}
						//bottom left
						if(y-2 < 0 && x-1 < 0 && map[y+2][x] != -1 && map[y+2][x+1] == -1)
						{
							oneoneX = x + 1;
							oneoneY = y + 2;
							patOneOne = true;
							return;
						}
						//bottom right
						if(y-2 < 0 && x + 1 >= colDimension && map[y+2][x] != -1 && map[y+2][x-1] ==-1)
						{
							oneoneX = x-1;
							oneoneY = y+2;
							patOneOne = true;
							return;
						}
						
						//roof patterns
						//if there is a roof above
						if(y+1 >= rowDimension && x-1 >= 0 && x+1 < colDimension)
						{
							//left side is uncovered
							if(map[y][x - 1] != -1 && map[y-1][x-1] != -1 && map[y-2][x-1] != -1 && map[y-2][x] != -1 &&  map[y-2][x+1] == -1)
							{							
								oneoneX = x+1;
								oneoneY = y-2;
								patOneOne = true;
								return;	
							}
							//right side is uncovered
							if(map[y][x + 1] != -1 && map[y-1][ x + 1] != -1 && map[y-2][x+1] != -1  && map[y-2][x] != -1 && map[y-2][x-1] == -1)
							{
								oneoneX = x-1;
								oneoneY = y-2;
								patOneOne = true;
								return;
							}	
						}
						//if there is a roof below
						if(y - 2 < 0 && x - 1 >= 0 && x + 1 < colDimension)
						{
							//left side is uncovered
							if(map[y][x - 1] != -1 && map[y-1][x-1] != -1 && map[y+1][x-1] != -1 && map[y+1][x+1] == -1)
							{		
								oneoneX = x+1;
								oneoneY = y+1;
								patOneOne = true;
								return;
							}
							//right side is uncovered
							if(map[y][x + 1] != -1 && map[y-1][ x + 1] != -1 && map[y+1][x+1] != -1  && map[y+1][x-1] == -1)
							{							
								oneoneX = x-1;
								oneoneY = y+1;
								patOneOne = true;
								return;	
							}	
						}
						
						//inner patterns
						if(y-2 >= 0 && y+1 < rowDimension && x + 1 < colDimension && x - 1 >= 0)
						{
							//if tiles aboved covered
							if(map[y+1][x - 1] != -1 && map[y+1][x] != -1 && map[y+1][x + 1] != -1)
							{
								//if tiles right are covered
								if(map[y][x + 1] != -1 && map[y-1][x + 1] != -1 && map[y-2][x + 1] != -1  && map[y-2][x] != -1 && map[y-2][x-1] == -1)
								{							
									oneoneX = x-1;
									oneoneY = y-2;
									patOneOne = true;
									return;	
								}
								//if tiles left are covered
								if(map[y][x - 1] != -1 && map[y-1][x - 1] != -1 && map[y-2][x - 1] != -1  && map[y-2][x] != -1 && map[y-2][x+1] == -1)
								{															
									oneoneX = x+1;
									oneoneY = y-2;
									patOneOne = true;
									return;		
								}
							}
							
							//if tiles below covered
							if(map[y-2][x - 1] != -1 && map[y-2][x] != -1 && map[y-2][x + 1] != -1)
							{
								//if tiles right are covered
								if(map[y][x + 1] != -1 && map[y-1][x + 1] != -1 && map[y-2][x + 1] != -1  && map[y+1][x] != -1 && map[y+1][x-1] == -1)
								{							
									oneoneX = x-1;
									oneoneY = y+1;
									patOneOne = true;
									return;	
								}
								//if tiles left are covered
								if(map[y][x - 1] != -1 && map[y-1][x - 1] != -1 && map[y+1][x - 1] != -1  && map[y+1][x] != -1 && map[y+1][x+1] == -1)
								{															
									oneoneX = x+1;
									oneoneY = y+1;
									patOneOne = true;
									return;		
								}
							}
						}
							
					}
				}
			}
		}
    }
	//if 1-1 horizontal on wall
	for(int y = 2; y < rowDimension - 2; y++)
	{
		//left wall check
		if(map[y][0] == 1 && map[y-1][0] == 1)
		{
			//check if top and bottom are covered
			if(map[y+1][0] != -1 && map[y-2][0] != -1)
			{
				//if top is covered bomb in bottom right
				if(map[y+1][1] != -1 & map[y-2][1] == -1)
				{
					oneoneX = 1;
					oneoneY = y - 2;
					patOneOne = true;
					return;
				}
				
				//if bottom is covered bomb in top left
				if(map[y-2][1] != -1  && map[y+1][1] == -1)
				{
					oneoneX = 1;
					oneoneY = y + 1;
					patOneOne = true;
					return;
				}
			}
		}
		//right wall check
		if(map[y][colDimension - 1] == 1 && map[y - 1][colDimension - 1] == 1)
		{
			//check if top and bottom are covered
			if(map[y+1][colDimension - 1] != -1 && map[y-2][colDimension - 1] != -1)
			{
				//if top is covered bomb in bottom right
				if(map[y+1][colDimension - 2] != -1 && map[y-2][colDimension - 2] == -1)
				{
					oneoneX = colDimension - 2;
					oneoneY = y - 2;
					patOneOne = true;
					return;
				}
				
				//if bottom is covered bomb in top left
				if(map[y-2][colDimension - 2] != -1 && map[y+1][colDimension - 2] == -1)
				{
					oneoneX = colDimension - 2;
					oneoneY = y + 1;
					patOneOne = true;
					return;
				}
			}
		}
	}
	for(int y = 1; y < rowDimension - 1; y++)
	{
		//checking sides
		//from 1 above floor to 1 below roof
		//if there is a 1-1 pattern on the left wall
		if(map[y][0] == 1 && map[y][1] == 1)
		{
			//if the uncovered tiles are under the 1-1
			if(y + 1 < rowDimension && y - 1 >= 0){
			if((map[y-1][0] != -1) && (map[y-1][1] != -1) && (map[y-1][2] != -1) && (map[y][2] != -1) && map[y+1][2] == -1)
			{
				oneoneX = 2;
				oneoneY = y + 1;
				patOneOne = true;
				return;
			}
			//if the uncovered tiles are above the 1-1
			if((map[y+1][0] != -1) && (map[y+1][1] != -1) && (map[y+1][2] != -1) && (map[y][2] != -1) && map[y-1][2] == -1)
			{
				oneoneX = 2;
				oneoneY = y - 1;
				patOneOne = true;
				return;
			}
			}
		}
		//if there is a 1-1 pattern on the right wall
		if(map[y][colDimension - 1] == 1 && map[y][colDimension - 2] == 1)
		{
			//if the uncovered tiles are under the 1-1
			if(y + 1 < rowDimension && y - 1 >= 0)
			{
			if((map[y-1][colDimension - 1] != -1) && (map[y-1][colDimension - 2] != -1) && (map[y-1][colDimension - 3] != -1) 
				&& (map[y][colDimension - 3] != -1) && map[y+1][colDimension-3] == -1)
			{
				oneoneX = colDimension - 3;
				oneoneY = y + 1;
				patOneOne = true;
				return;
			}
			//if the uncovered tiles are above the 1-1
			if((map[y+1][colDimension - 1] != -1) && (map[y+1][colDimension - 2] != -1) && (map[y+1][colDimension - 3] != -1 )
				&& (map[y][colDimension - 3] != -1) && map[y-1][colDimension-3] == -1)
			{
				oneoneX = colDimension - 3;
				oneoneY = y - 1;
				patOneOne = true;
				return;
			}
			}
		}
	}
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			//check if theres a one and the next tile is not oob
			if(iMap[y][x] == 1 && x+1 < colDimension)
			{
				//now check if the next tile over is a 1
				if(iMap[y][x+1] == 1)
				{
					//first check corner cases
					//if 1-1 pattern is at top left. mine is on bottom right
					if(y + 1 >= rowDimension && x - 1 < 0 && iMap[y-1][x+2] == -1 && iMap[y][x+2] != -1 && iMap[y][x+2] != -2)
					{
						oneoneX = x + 2;
						oneoneY = y - 1;
						patOneOne = true;
						return;
					}
					//if 1-1 is at top right, mine is on bottom left
					if( y + 1 >= rowDimension &&  x + 2 >= colDimension && iMap[y-1][x-1] == -1 && iMap[y][x-1] != -1 && iMap[y][x+2] != -2)
					{
						oneoneX = x - 1;
						oneoneY = y - 1;
						patOneOne = true;
						return;
					}
					//if 1-1 is bottom left, mine top right
					if(y-1 < 0 && x - 1 < 0 && iMap[y+1][x+2] == -1 && iMap[y][x+2] != -1 && iMap[y][x+2] != -2)
					{ 
						oneoneX = x + 2;
						oneoneY = y + 1;
						patOneOne = true;
						return;
					}
					//if 1-1 is bottom right, mine top left
					if(y-1 < 0 && x + 2 >= colDimension && iMap[y+1][x-1] == -1 && iMap[y][x-1] != -1 && iMap[y][x-1] != -2)
					{
						oneoneX = x-1;
						oneoneY = y+1;
						patOneOne = true;
						return;
					}
					//now check roof patterns
					//if roof above
					if(y + 1 >= rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if roof is above and opensquare to left
						if((iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2) && (iMap[y][x-1] != -1 && iMap[y][x-1] != -2) && (iMap[y][x+2] != -1 && iMap[y][x+2] != -2) && iMap[y-1][x+2] == -1)
						{
							oneoneX = x + 2;
							oneoneY = y - 1;
							patOneOne = true;
							return;
						}
						//if roof is above and opensquare to right
						if((iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) && (iMap[y][x-1] != -1 && iMap[y][x-1] != -2) && (iMap[y][x+2] != -1 && iMap[y][x+2] != -2) && iMap[y-1][x-1] == -1)
						{
							oneoneX = x-1;
							oneoneY = y-1;
							patOneOne = true;
							return;
						}
					}
					//if roof below
					if(y - 1 < 0 && x - 1 >= 0 && x + 2 < colDimension)
					{
		
						//if roof is below and opensquare to left
						if((iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2) && (iMap[y][x-1] != -1 && iMap[y][x-1] != -2) && (iMap[y][x+2] != -1 && iMap[y][x+2] != -2) && iMap[y+1][x+2] == -1)
						{
							oneoneX = x + 2;
							oneoneY = y + 1;
							patOneOne = true;
							return;
						}
						//if roof is above and opensquare to right
						if((iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2) && (iMap[y][x+2] != -1 && iMap[y][x+2] != -2) && (iMap[y][x-1] != -1 && iMap[y][x-1] != -2) && iMap[y+1][x-1] == -1)
						{
							oneoneX = x-1;
							oneoneY = y+1;
							patOneOne = true;
							return;
						}
					}
					
					//now check inner patterns
					if(y - 1 >= 0 && y + 1 < rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if uncovered tiles are below
						if((iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2)  && (iMap[y-1][x] != -1 && iMap[y-1][x] != -2) && (iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2) && (iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) &&
						(iMap[y][x-1] != -1 && iMap[y][x-1] != -2) && (iMap[y][x+2] !=-1 && iMap[y][x+2] != -2))
						{	
							//if uncovered tiles on left 
							if((iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2) && iMap[y+1][x+2] == -1)
							{
								oneoneX = x+2;
								oneoneY = y+1;
								patOneOne = true;
								return;
							}
							//uncovered right
							if((iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2) && iMap[y+1][x-1] == -1)
							{
								oneoneX = x -1;
								oneoneY = y+1;
								patOneOne = true;
								return;
							}
						}
					
					//if uncovered tiles are above
						if((iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2) && (iMap[y+1][x] != -1 && iMap[y+1][x] != -2) && (iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2) && (iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2 )&& (iMap[y][x-1] != -1 && 
							iMap[y][x-1] != -2) && (iMap[y][x+2] !=-1 && iMap[y][x+2] != -2))
						{
							//if uncovered tiles on left 
							if((iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2) && iMap[y-1][x+2] == -1)
							{
								oneoneX = x+2;
								oneoneY = y-1;
								patOneOne = true;
								return;
							}
							if((iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) && iMap[y-1][x-1] == -1)
							{
								oneoneX = x -1;
								oneoneY = y-1;
								patOneOne = true;
								return;
							}
						}
					}
					
				}
				//now check vertical
				if(iMap[y][x] == 1 && y - 1 > 0)
				{
					if(iMap[y-1][x] == 1)
					{
						//first corner situations
						
						//top left
						if(y+1 >= rowDimension && x-1 < 0 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x+1] == -1)
						{
							oneoneX = x +1;
							oneoneY = y-2;
							patOneOne = true;
							return;
						}
						//top right
						if(y + 1 >= rowDimension&& x+1 >= colDimension && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x-1] == -1)
						{
							oneoneX = x -1;
							oneoneY = y - 2;
							patOneOne = true;
							return;
						}
						//bottom left
						if(y-2 < 0 && x-1 < 0 && iMap[y+2][x] != -1 && iMap[y+2][x] != -2 && iMap[y+2][x+1] == -1)
						{
							oneoneX = x + 1;
							oneoneY = y + 2;
							patOneOne = true;
							return;
						}
						//bottom right
						if(y-2 < 0 && x + 1 >= colDimension && iMap[y+2][x] != -1 && iMap[y+2][x] != -2 && iMap[y+2][x-1] ==-1)
						{							
							oneoneX = x-1;
							oneoneY = y+2;
							patOneOne = true;
							return;
						}
						
						//roof patterns
						//if there is a roof above
						if(y+1 >= rowDimension && x-1 >= 0 && x+1 < colDimension)
						{
							//left side is uncovered
							if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2 && iMap[y-2][x-1] != -1 && iMap[y-2][x-1] != -2 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x+1] == -1)
							{							
								oneoneX = x+1;
								oneoneY = y-2;
								patOneOne = true;
								return;	
							}
							//right side is uncovered
							if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][ x + 1] != -1 && iMap[y-1][x+1] != -2 && iMap[y-2][x+1] != -1 && iMap[y-2][x+1] != -2 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x-1] == -1)
							{
											 
								oneoneX = x-1;
								oneoneY = y-2;
								patOneOne = true;
								return;
							}	
						}
						//if there is a roof below
						if(y - 2 < 0 && x - 1 >= 0 && x + 1 < colDimension)
						{
							//left side is uncovered
							if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2 && iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2 && iMap[y+1][x+1] == -1)
							{							
								oneoneX = x+1;
								oneoneY = y+1;
								patOneOne = true;
								return;
								
							}
							//right side is uncovered
							if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][ x + 1] != -1 && iMap[y-1][x+1] != -2 && iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y+1][x-1] == -1)
							{							
								oneoneX = x-1;
								oneoneY = y+1;
								patOneOne = true;
								return;	
							}	
						}
						
						//inner patterns
						if(y-2 >= 0 && y+1 < rowDimension && x + 1 < colDimension && x - 1 >= 0)
						{
							//if tiles aboved covered
							if(iMap[y+1][x - 1] != -1 && iMap[y+1][x - 1] != -2 && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x + 1] != -1 && iMap[y+1][x + 1] != -2)
							{
								//if tiles right are covered
								if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][x + 1] != -1 && iMap[y-1][x + 1] != -2 && iMap[y-2][x + 1] != -1 && iMap[y-2][x + 1] != -2  && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x-1] == -1)
								{							
									oneoneX = x-1;
									oneoneY = y-2;
									patOneOne = true;
									return;	
								}
								//if tiles left are covered
								if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x - 1] != -1 && iMap[y-1][x - 1] != -2 && iMap[y-2][x - 1] != -1 && iMap[y-2][x - 1] != -2  && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x+1] == -1)
								{															
									oneoneX = x+1;
									oneoneY = y-2;
									patOneOne = true;
									return;		
								}
							}
							
							//if tiles below covered
							if(iMap[y-2][x - 1] != -1 && iMap[y-2][x - 1] != -2 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x + 1] != -1 && iMap[y-2][x + 1] != -2 )
							{
								//if tiles right are covered
								if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][x + 1] != -1 && iMap[y-1][x + 1] != -2 && iMap[y-2][x + 1] != -1 && iMap[y-2][x + 1] != -2  && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x-1] == -1)
								{							
									oneoneX = x-1;
									oneoneY = y+1;
									patOneOne = true;
									return;	
								}
								//if tiles left are covered
								if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x - 1] != -1 && iMap[y-1][x - 1] != -2 && iMap[y+1][x - 1] != -1 && iMap[y+1][x - 1] != -2  && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x+1] == -1)
								{															
									oneoneX = x+1;
									oneoneY = y+1;
									patOneOne = true;
									return;		
								}
							}
						}
							
					}
				}
			}
		}
    }
	//if 1-1 horizontal on wall
	for(int y = 2; y < rowDimension - 2; y++)
	{
		//left wall check
		if(iMap[y][0] == 1 && iMap[y-1][0] == 1)
		{
			//check if top and bottom are covered
			if(iMap[y+1][0] != -1 && iMap[y+1][0] != -2 && iMap[y-2][0] != -1 && iMap[y-2][0] != -2)
			{
				//if top is covered bomb in bottom right
				if(iMap[y+1][1] != -1 && iMap[y+1][1] != -2 && iMap[y-2][1] == -1)
				{
					oneoneX = 1;
					oneoneY = y - 2;
					patOneOne = true;
					return;
				}
				
				//if bottom is covered bomb in top left
				if(iMap[y-2][1] != -1 && iMap[y-2][1] != -2 && iMap[y+1][1] == -1)
				{
					oneoneX = 1;
					oneoneY = y + 1;
					patOneOne = true;
					return;
				}
			}
		}
		//right wall check
		if(iMap[y][colDimension - 1] == 1 && iMap[y - 1][colDimension - 1] == 1)
		{
			//check if top and bottom are covered
			if(iMap[y+1][colDimension - 1] != -1 && iMap[y+1][colDimension - 1] != -2 && iMap[y-2][colDimension - 1] != -1 && iMap[y-2][colDimension - 1] != -2)
			{
				//if top is covered bomb in bottom right
				if(iMap[y+1][colDimension - 2] != -1 && iMap[y+1][colDimension - 2] != -2 && iMap[y-2][colDimension - 2] == -1)
				{
					oneoneX = colDimension - 2;
					oneoneY = y - 2;
					patOneOne = true;
					return;
				}
				
				//if bottom is covered bomb in top left
				if(iMap[y-2][colDimension - 2] != -1 && iMap[y-2][colDimension - 2] != -2 && iMap[y+1][colDimension - 2] == -1)
				{
					oneoneX = colDimension - 2;
					oneoneY = y + 1;
					patOneOne = true;
					return;
				}
			}
		}
	}
	for(int y = 1; y < rowDimension - 1; y++)
	{
		//checking sides
		//from 1 above floor to 1 below roof
		//if there is a 1-1 pattern on the left wall
		if(iMap[y][0] == 1 && iMap[y][1] == 1)
		{
			//if the uncovered tiles are under the 1-1
			if(y + 1 < rowDimension && y - 1 >= 0){
			if((iMap[y-1][0] != -1 && iMap[y-1][0] != -2) && (iMap[y-1][1] != -1 && iMap[y-1][1] != -2) && (iMap[y-1][2] != -1 && iMap[y-1][2] != -2) && (iMap[y][2] != -1 && iMap[y][2] != -2) && iMap[y+1][2] == -1)
			{
				oneoneX = 2;
				oneoneY = y + 1;
				patOneOne = true;
				return;
			}
			//if the uncovered tiles are above the 1-1
			if((iMap[y+1][0] != -1 && iMap[y+1][0] != -2) && (iMap[y+1][1] != -1 && iMap[y+1][1] != -2) && (iMap[y+1][2] != -1 && iMap[y+1][2] != -2) && (iMap[y][2] != -1 && iMap[y][2] != -2) && iMap[y-1][2] == -1)
			{
				oneoneX = 2;
				oneoneY = y - 1;
				patOneOne = true;
				return;
			}
			}
		}
		//if there is a 1-1 pattern on the right wall
		if(iMap[y][colDimension - 1] == 1 && iMap[y][colDimension - 2] == 1)
		{
			//if the uncovered tiles are under the 1-1
			if(y + 1 < rowDimension && y - 1 >= 0)
			{
			if((iMap[y-1][colDimension - 1] != -1 && iMap[y-1][colDimension - 1] != -2) && (iMap[y-1][colDimension - 2] != -1 && iMap[y-1][colDimension - 2] != -2) && (iMap[y-1][colDimension - 3] != -1 && iMap[y-1][colDimension - 3] != -2) 
				&& (iMap[y][colDimension - 3] != -1 && iMap[y][colDimension - 3] != -2) && iMap[y+1][colDimension-3] == -1)
			{
				oneoneX = colDimension - 3;
				oneoneY = y + 1;
				patOneOne = true;
				return;
			}
			//if the uncovered tiles are above the 1-1
			if((iMap[y+1][colDimension - 1] != -1 && iMap[y+1][colDimension - 1] != -2) && (iMap[y+1][colDimension - 2] != -1 && iMap[y+1][colDimension - 2] != -2) && (iMap[y+1][colDimension - 3] != -1 && iMap[y+1][colDimension - 3] != -2)
				&& (iMap[y][colDimension - 3] != -1 && iMap[y][colDimension - 3] != -2) && iMap[y-1][colDimension-3] == -1)
			{
				oneoneX = colDimension - 3;
				oneoneY = y - 1;
				patOneOne = true;
				return;
			}
			}
		}
	}
}
void MyAI::checkOneTwo()
{
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			// if its 2-1
			if(map[y][x] == 2 && x+1 < colDimension)
			{
				//now check if the next tile over is a 1
				if(map[y][x+1] == 1)
				{
					//if 2-1 is at top right, mine is on bottom left
					if( y + 1 >= rowDimension &&  x + 2 >= colDimension && map[y-1][x-1] == -1  && map[y][x-1] != -1)
					{
						onetwoX = x - 1;
						onetwoY = y;
						patOneTwo = true;
						return;
					}
					//if 2-1 is bottom right, mine top left
					if(y-1 < 0 && x + 2 >= colDimension && map[y+1][x-1] == -1 && map[y][x-1] != -1)
					{
						onetwoX = x-1;
						onetwoY = y+1;
						patOneTwo = true;
						return;
					}
					//If roof above
					if(y + 1 >= rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//check if both sides are clear
						if((map[y][x+2] != -1)&& map[y][x-1] != -1)
						{
							//if roof is above and uncovered to right
							if((map[y-1][x+2] != -1) && map[y-1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y-1;
								patOneTwo = true;
								return;
							}
						}
					}
					//if roof below
					if(y - 1 < 0 && x - 1 >= 0 && x + 2 < colDimension)
					{
						if((map[y][x+2] != -1)&& (map[y][x-1] != -1))
						{
							//if roof is above and uncovered to right
							if((map[y+1][x+2] != -1)&& map[y+1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y+1;
								patOneTwo = true;
								return;
							}
						}
					}
					
					//inner check
					if(y - 1 >= 0 && y + 1 < rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if both sides are clear
						if((map[y][x+2] != -1)&& (map[y][x-1] != -1))
						{
							//if tiles under and top right is clear mine to left
							if((map[y-1][x-1] != -1)  && (map[y-1][x] != -1) && (map[y-1][x+1] != -1) && (map[y-1][x+2] != -1) && 
							(map[y+1][x+2] != -1) && map[y+1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y+1;
								patOneTwo = true;
								return;
							}
							//if tiles above and top right is clear mine to left
							if((map[y+1][x-1] != -1)  && (map[y+1][x] != -1) && (map[y+1][x+1] != -1) && (map[y+1][x+2] != -1) && 
							(map[y-1][x+2] != -1) && map[y-1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y-1;
								patOneTwo = true;
								return;
							}
						}
					}	
				}
			}
			//if pattern is 1-2
			if(map[y][x] == 1 && x+1 < colDimension)
			{
				//now check if the next tile over is a 2
				if(map[y][x+1] == 2)
				{
					//first check corner cases
					//if 1-1 pattern is at top left. mine is on bottom right
					if(y + 1 >= rowDimension && x - 1 < 0 && map[y-1][x+2] == -1  && map[y][x+2] != -1)
					{
						onetwoX = x + 2;
						onetwoY = y - 1;
						patOneTwo = true;
						return;
					}
					//if 1-1 is bottom left, mine top right
					if(y-1 < 0 && x - 1 < 0 && map[y+1][x+2] == -1 && map[y][x+2] != -1)
					{
						onetwoX = x + 2;
						onetwoY = y + 1;
						patOneTwo = true;
						return;
					}
					//if roof above
					if(y + 1 >= rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						if((map[y][x+2] != -1)&& (map[y][x-1] != -1))
						{
							//if roof is above and uncovered to left
							if((map[y-1][x-1] != -1) && map[y-1][x+2] == -1)
							{
								onetwoX = x + 2;
								onetwoY = y - 1;
								patOneTwo = true;
								return;
							}
						}
					}
					//if roof below
					if(y - 1 < 0 && x - 1 >= 0 && x + 2 < colDimension)
					{
						if((map[y][x+2] != -1)&& (map[y][x-1] != -1))
						{
							//if roof is below and uncovered to left
							if((map[y+1][x-1] != -1) && map[y+1][x+2] == -1)
							{
								onetwoX = x + 2;
								onetwoY = y + 1;
								patOneTwo = true;
								return;
							}
						}
					}
					
					//inner check				
					if(y - 1 >= 0 && y + 1 < rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if both sides are clear
						if((map[y][x+2] != -1) && (map[y][x-1] != -1))
						{
							//if tiles under and top left is clear mine to right
							if((map[y-1][x-1] != -1)  && (map[y-1][x] != -1) && (map[y-1][x+1] != -1) && (map[y-1][x+2] != -1) && 
							(map[y+1][x-1] != -1) && map[y+1][x+2] == -1)
							{
								onetwoX = x+2;
								onetwoY = y+1;
								patOneTwo = true;
								return;
							}
							//if tiles above and bottom left is clear mine to right
							if((map[y+1][x-1] != -1)  && (map[y+1][x] != -1) && (map[y+1][x+1] != -1) && (map[y+1][x+2] != -1) && 
							(map[y-1][x-1] != -1) && map[y-1][x+2] == -1)
							{
								onetwoX = x+2;
								onetwoY = y-1;
								patOneTwo = true;
								return;
							}
						}
					}	
				}
					
			}
			if(map[y][x] == 1 && y-2 >=0)
			{
				//if there is a 1-2 horizontal pattern
				if(map[y-1][x] == 2)
				{
					//top right
					if(y+1 >= rowDimension && x - 1 < 0 && map[y-2][x] != -1 && map[y-2][x+1] == -1)
					{
						onetwoX = x+1;
						onetwoY = y-2;
						patOneTwo = true;
						return;
					}
					//top left
					if(y+1 >= rowDimension && x + 1 >= colDimension && map[y-2][x] != -1 && map[y-2][x-1] == -1)
					{
						onetwoX = x-1;
						onetwoY = y-2;
						patOneTwo = true;
						return;
					}
					
					//roof patterns
					//roof above
					if(y+1 >= rowDimension && x-1 >= 0 && x+1 < colDimension)
					{
						//if left side uncovered
						if(map[y][x - 1] != -1  && map[y-1][x-1] != -1 && map[y-2][x-1] != -1 && map[y-2][x] != -1 && map[y-2][x+1] == -1)
						{							
							onetwoX = x+1;
							onetwoY = y-2;
							patOneTwo = true;
							return;	
						}
						//if right side uncovered
						if(map[y][x + 1] != -1 && map[y-1][x+1] != -1 && map[y-2][x+1] != -1 && map[y-2][x] != -1 && map[y-2][x-1] == -1)
						{							
							onetwoX = x-1;
							onetwoY = y-2;
							patOneTwo = true;
							return;	
						}
					}
					//inner patterns
					if(y-2 >= 0 && y+1 < rowDimension && x + 1 < colDimension && x - 1 >= 0)
					{
						//check if both bottom and top of 2-1 is uncovered
						if(map[y+1][x] != -1 && map[y-2][x] != -1)
						{
							//if right tiles uncovered
							if(map[y][x + 1] != -1 && map[y-1][x + 1] != -1 && map[y-2][x + 1] != -1  && map[y+1][x+1] != -1 && map[y+1][x-1] != -1 && map[y-2][x-1] == -1)
							{								
								onetwoX = x-1;
								onetwoY = y-2;
								patOneTwo = true;
								return;	
							}
							//if left tiles uncovered
							if(map[y][x - 1] != -1&& map[y-1][x - 1] != -1 && map[y-2][x - 1] != -1  && map[y+1][x - 1] != -1 && map[y+1][x+1] != -1 && map[y-2][x+1] == -1)
							{								
								onetwoX = x+1;
								onetwoY = y-2;
								patOneTwo = true;
								return;	
							}
						}
					}
				}
			}
			
			if(map[y][x] == 2 && y-2 >=0)
			{
				//if there is a 2-1 horizontal pattern
				if(map[y-1][x] == 1)
				{
					//bottom right
					if(y - 2 > 0 && y + 1 < rowDimension && x - 1 < 0 && map[y+1][x] != -1 && map[y+1][x+1] == -1)
					{
						onetwoX = x+1;
						onetwoY = y+1;
						patOneTwo = true;
						return;
					}
					//top left
					if(y - 2 > 0 && x + 1 >= colDimension && map[y+1][x] != -1 && map[y+1][x-1] == -1)
					{
						onetwoX = x-1;
						onetwoY = y+1;
						patOneTwo = true;
						return;
					}
					
					//floor patterns
					if(y - 2 < 0 && y + 1 < rowDimension && x-1 >= 0 && x+1 < colDimension)
					{
						//if left side uncovered
						if(map[y][x - 1] != -1 && map[y+1][x-1] != -1 && map[y-1][x-1] != -1 && map[y+1][x] != -1 && map[y+1][x+1] == -1)
						{							
							onetwoX = x+1;
							onetwoY = y+1;
							patOneTwo = true;
							return;	
						}
						//if right side uncovered
						if(map[y][x + 1] != -1 && map[y-1][x+1] != -1 && map[y+1][x+1] != -1 && map[y+1][x] != -1 && map[y+1][x-1] == -1)
						{							
							onetwoX = x-1;
							onetwoY = y+1;
							patOneTwo = true;
							return;	
						}
					}
					//inner patterns
					if(y-2 >= 0 && y+1 < rowDimension && x + 1 < colDimension && x - 1 >= 0)
					{
						//check if both bottom and top of 2-1 is uncovered
						if(map[y+1][x] != -1 && map[y-2][x] != -1)
						{
							//if right tiles uncovered
							if(map[y][x + 1] != -1 && map[y-1][x + 1] != -1 && map[y-2][x + 1] != -1  && map[y+1][x+1] != -1 && map[y-2][x-1] != -1 && map[y+1][x-1] == -1)
							{								
								onetwoX = x-1;
								onetwoY = y+1;
								patOneTwo = true;
								return;	
							}
							//if left tiles uncovered
							if(map[y][x - 1] != -1 && map[y-1][x - 1] != -1 && map[y-2][x - 1] != -1  && map[y+1][x - 1] != -1 && map[y-2][x+1] != -1 && map[y+1][x+1] == -1)
							{								
								onetwoX = x+1;
								onetwoY = y+1;
								patOneTwo = true;
								return;	
							}
						}
					}
				}
			}
		}
	}
	for(int y = 2; y < rowDimension - 2; y++)
	{
		//left wall 
		//check if its 1-2 horizontal
		if(map[y][0] == 1 && map[y-1][0] == 2)
		{
			//check if top and bottom are covered
			if(map[y+1][0] != -1&& map[y-2][0] != -1)
			{
				//if top is covered bomb in bottom right
				if(map[y+1][1] != -1 && map[y-2][1] == -1)
				{
					onetwoX = 1;
					onetwoY = y - 2;
					patOneTwo = true;
					return;
				}
			}
		}
		//right wall check
		if(map[y][colDimension - 1] == 1 && map[y][colDimension - 2] == 2)
		{
			//check if top and bottom are covered
			if(map[y+1][colDimension - 1] != -1 && map[y-2][colDimension - 1] != -1)
			{
				//if top is covered bomb in bottom right
				if(map[y+1][colDimension - 2] != -1 && map[y-2][colDimension - 2] == -1)
				{
					onetwoX = colDimension - 2;
					onetwoY = y - 2;
					patOneTwo = true;
					return;
				}
			}
		}
		//check if 2-1 horizontal
		if(map[y][0] == 2 && map[y-1][0] == 1)
		{
			//check if top and bottom are covered
			if(map[y+1][0] != -1 && map[y-2][0] != -1)
			{	
				//if bottom is covered bomb in top left
				if(map[y-2][1] != -1&& map[y+1][1] == -1)
				{
					onetwoX = 1;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}
			}
		}
		//right wall check
		if(map[y][colDimension - 1] == 1 && map[y][colDimension - 2] == 1)
		{
			//check if top and bottom are covered
			if(map[y+1][colDimension - 1] != -1 && map[y-2][colDimension - 1] != -1)
			{
				//if bottom is covered bomb in top left
				if(map[y-2][colDimension - 2] != -1 && map[y+1][colDimension - 2] == -1)
				{
					onetwoX = colDimension - 2;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}
			}
		}
	}
	
	for(int y = 0; y < rowDimension; y++)
	{
		if(y + 1 < rowDimension && y - 1 >= 0)
		{
			//if there is a 1-2 pattern on the left wall
			if(map[y][0] == 1 && map[y][1] == 2)
			{
				//if top is uncovered;
				if(map[y][2] != -1&& map[y+1][2] != -1 && map[y+1][1] != -1 && map[y+1][0] != -1 && map[y-1][2] == -1)
				{
					onetwoX = 2;
					onetwoY = y - 1;
					patOneTwo = true;
					return;
				}
				//IF BOTTOM uncovered
				if(map[y][2] != -1 && map[y-1][2] != -1 && map[y-1][1] != -1 && map[y-1][0] != -1 && map[y+1][2] == -1)
				{
					onetwoX = 2;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}

			}
		}
		if(y + 1 < rowDimension && y - 1 >= 0)
		{
			//if there is a 2-1 pattern on the right wall
			if(map[y][colDimension - 1] == 1 && map[y][colDimension - 2] == 2 && map[y][colDimension - 3] != -1)
			{ 
				//if the uncovered tiles are under the 1-1
				if((map[y-1][colDimension - 1] != -1) && (map[y-1][colDimension - 2] != -1) && (map[y-1][colDimension - 3] != -1) && map[y+1][colDimension-3] == -1)
				{
					onetwoX = colDimension - 3;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}
				//if the uncovered tiles are above the 1-1
				if((map[y+1][colDimension - 1] != -1) && (map[y+1][colDimension - 2] != -1) && (map[y+1][colDimension - 3] != -1)&& map[y-1][colDimension-3] == -1)
				{
					onetwoX = colDimension - 3;
					onetwoY = y - 1;
					patOneTwo = true;
					return;
				}
			
			}
		}
	}
	
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			// if its 2-1
			if(iMap[y][x] == 2 && x+1 < colDimension)
			{
				//now check if the next tile over is a 1
				if(iMap[y][x+1] == 1)
				{
					//if 2-1 is at top right, mine is on bottom left
					if( y + 1 >= rowDimension &&  x + 2 >= colDimension && iMap[y-1][x-1] == -1  && iMap[y][x-1] != -1 && iMap[y][x-1] != -2)
					{
						onetwoX = x - 1;
						onetwoY = y;
						patOneTwo = true;
						return;
					}
					//if 2-1 is bottom right, mine top left
					if(y-1 < 0 && x + 2 >= colDimension && iMap[y+1][x-1] == -1 && iMap[y][x-1] != -1 && iMap[y][x-1] != -2)
					{
						onetwoX = x-1;
						onetwoY = y+1;
						patOneTwo = true;
						return;
					}
					//If roof above
					if(y + 1 >= rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//check if both sides are clear
						if((iMap[y][x+2] != -1 && iMap[y][x+2] != -2)&& (iMap[y][x-1] != -1 && iMap[y][x-1] != -2))
						{
							//if roof is above and uncovered to right
							if((iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) && iMap[y-1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y-1;
								patOneTwo = true;
								return;
							}
						}
					}
					//if roof below
					if(y - 1 < 0 && x - 1 >= 0 && x + 2 < colDimension)
					{
						if((iMap[y][x+2] != -1 && iMap[y][x+2] != -2)&& (iMap[y][x-1] != -1 && iMap[y][x-1] != -2))
						{
							//if roof is above and uncovered to right
							if((iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2)&& iMap[y+1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y+1;
								patOneTwo = true;
								return;
							}
						}
					}
					
					//inner check
					if(y - 1 >= 0 && y + 1 < rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if both sides are clear
						if((iMap[y][x+2] != -1 && iMap[y][x+2] != -2)&& (iMap[y][x-1] != -1 && iMap[y][x-1] != -2))
						{
							//if tiles under and top right is clear mine to left
							if((iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2)  && (iMap[y-1][x] != -1 && iMap[y-1][x] != -2) && (iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2) && (iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) && 
							(iMap[y+1][x+2] != -1 && iMap[y-1][x+2] != -2) && iMap[y+1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y+1;
								patOneTwo = true;
								return;
							}
							//if tiles above and top right is clear mine to left
							if((iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2)  && (iMap[y+1][x] != -1 && iMap[y+1][x] != -2) && (iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2) && (iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2) && 
							(iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) && iMap[y-1][x-1] == -1)
							{
								onetwoX = x-1;
								onetwoY = y-1;
								patOneTwo = true;
								return;
							}
						}
					}	
				}
			}
			//if pattern is 1-2
			if(iMap[y][x] == 1 && x+1 < colDimension)
			{
				//now check if the next tile over is a 2
				if(iMap[y][x+1] == 2)
				{
					//first check corner cases
					//if 1-1 pattern is at top left. mine is on bottom right
					if(y + 1 >= rowDimension && x - 1 < 0 && iMap[y-1][x+2] == -1  && iMap[y][x+2] != -1 && iMap[y][x+2] != -2)
					{
						onetwoX = x + 2;
						onetwoY = y - 1;
						patOneTwo = true;
						return;
					}
					//if 1-1 is bottom left, mine top right
					if(y-1 < 0 && x - 1 < 0 && iMap[y+1][x+2] == -1 && iMap[y][x+2] != -1 && iMap[y][x+2] != -2)
					{
						onetwoX = x + 2;
						onetwoY = y + 1;
						patOneTwo = true;
						return;
					}
					//if roof above
					if(y + 1 >= rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						if((iMap[y][x+2] != -1 && iMap[y][x+2] != -2)&& (iMap[y][x-1] != -1 && iMap[y][x-1] != -2))
						{
							//if roof is above and uncovered to left
							if((iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2) && iMap[y-1][x+2] == -1)
							{
								onetwoX = x + 2;
								onetwoY = y - 1;
								patOneTwo = true;
								return;
							}
						}
					}
					//if roof below
					if(y - 1 < 0 && x - 1 >= 0 && x + 2 < colDimension)
					{
						if((iMap[y][x+2] != -1 && iMap[y][x+2] != -2)&& (iMap[y][x-1] != -1 && iMap[y][x-1] != -2))
						{
							//if roof is below and uncovered to left
							if((iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2) && iMap[y+1][x+2] == -1)
							{
								onetwoX = x + 2;

								onetwoY = y + 1;
								patOneTwo = true;
								return;
							}
						}
					}
					
					//inner check				
					if(y - 1 >= 0 && y + 1 < rowDimension && x - 1 >= 0 && x + 2 < colDimension)
					{
						//if both sides are clear
						if((iMap[y][x+2] != -1 && iMap[y][x+2] != -2) && (iMap[y][x-1] != -1 && iMap[y][x-1] != -2))
						{
							//if tiles under and top left is clear mine to right
							if((iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2)  && (iMap[y-1][x] != -1 && iMap[y-1][x] != -2) && (iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2) && (iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2) && 
							(iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2) && iMap[y+1][x+2] == -1)
							{
								onetwoX = x+2;
								onetwoY = y+1;
								patOneTwo = true;
								return;
							}
							//if tiles above and bottom left is clear mine to right
							if((iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2)  && (iMap[y+1][x] != -1 && iMap[y+1][x] != -2) && (iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2) && (iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2) && 
							(iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2) && iMap[y-1][x+2] == -1)
							{
								onetwoX = x+2;
								onetwoY = y-1;
								patOneTwo = true;
								return;
							}
						}
					}	
				}
					
			}
			if(iMap[y][x] == 1 && y-2 >=0)
			{
				//if there is a 1-2 horizontal pattern
				if(iMap[y-1][x] == 2)
				{
					//top right
					if(y+1 >= rowDimension && x - 1 < 0 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x+1] == -1)
					{
						onetwoX = x+1;
						onetwoY = y-2;
						patOneTwo = true;
						return;
					}
					//top left
					if(y+1 >= rowDimension && x + 1 >= colDimension && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x-1] == -1)
					{
						onetwoX = x-1;
						onetwoY = y-2;
						patOneTwo = true;
						return;
					}
					
					//roof patterns
					//roof above
					if(y+1 >= rowDimension && x-1 >= 0 && x+1 < colDimension)
					{
						//if left side uncovered
						if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2 && iMap[y-2][x-1] != -1 && iMap[y-2][x-1] != -2 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x+1] == -1)
						{							
							onetwoX = x+1;
							onetwoY = y-2;
							patOneTwo = true;
							return;	
						}
						//if right side uncovered
						if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2 && iMap[y-2][x+1] != -1 && iMap[y-2][x+1] != -2 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2 && iMap[y-2][x-1] == -1)
						{							
							onetwoX = x-1;
							onetwoY = y-2;
							patOneTwo = true;
							return;	
						}
					}
					//inner patterns
					if(y-2 >= 0 && y+1 < rowDimension && x + 1 < colDimension && x - 1 >= 0)
					{
						//check if both bottom and top of 2-1 is uncovered
						if(iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y-2][x] != -1 && iMap[y-2][x] != -2)
						{
							//if right tiles uncovered
							if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][x + 1] != -1 && iMap[y-1][x + 1] != -2 && iMap[y-2][x + 1] != -1 && iMap[y-2][x + 1] != -2  && iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2 && iMap[y-2][x-1] == -1)
							{								
								onetwoX = x-1;
								onetwoY = y-2;
								patOneTwo = true;
								return;	
							}
							//if left tiles uncovered
							if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x - 1] != -1 && iMap[y-1][x - 1] != -2 && iMap[y-2][x - 1] != -1 && iMap[y-2][x - 1] != -2  && iMap[y+1][x - 1] != -1 && iMap[y+1][x - 1] != -2 && iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y-2][x+1] == -1)
							{								 
								onetwoX = x+1;
								onetwoY = y-2;
								patOneTwo = true;
								return;	
							}
						}
					}
				}
			}
			
			if(iMap[y][x] == 2 && y-2 >=0)
			{
				//if there is a 2-1 horizontal pattern
				if(iMap[y-1][x] == 1)
				{
					//bottom right
					if(y - 2 > 0 && y + 1 < rowDimension && x - 1 < 0 && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x+1] == -1)
					{
						onetwoX = x+1;
						onetwoY = y+1;
						patOneTwo = true;
						return;
					}
					//top left
					if(y - 2 > 0 && x + 1 >= colDimension && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x-1] == -1)
					{
						onetwoX = x-1;
						onetwoY = y+1;
						patOneTwo = true;
						return;
					}
					
					//floor patterns
					if(y - 2 < 0 && y + 1 < rowDimension && x-1 >= 0 && x+1 < colDimension)
					{
						//if left side uncovered
						if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2 && iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2 && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x+1] == -1)
						{							
							onetwoX = x+1;
							onetwoY = y+1;
							patOneTwo = true;
							return;	
						}
						//if right side uncovered
						if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2 && iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x-1] == -1)
						{							
							onetwoX = x-1;
							onetwoY = y+1;
							patOneTwo = true;
							return;	
						}
					}
					//inner patterns
					if(y-2 >= 0 && y+1 < rowDimension && x + 1 < colDimension && x - 1 >= 0)
					{
						//check if both bottom and top of 2-1 is uncovered
						if(iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y-2][x] != -1 && iMap[y+1][x] != -2)
						{
							//if right tiles uncovered
							if(iMap[y][x + 1] != -1 && iMap[y][x + 1] != -2 && iMap[y-1][x + 1] != -1 && iMap[y-1][x + 1] != -2 && iMap[y-2][x + 1] != -1 && iMap[y-2][x + 1] != -2  && iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y-2][x-1] != -1 && iMap[y-2][x-1] != -2 && iMap[y+1][x-1] == -1)
							{								
								onetwoX = x-1;
								onetwoY = y+1;
								patOneTwo = true;
								return;	
							}
							//if left tiles uncovered
							if(iMap[y][x - 1] != -1 && iMap[y][x - 1] != -2 && iMap[y-1][x - 1] != -1 && iMap[y-1][x - 1] != -2 && iMap[y-2][x - 1] != -1 && iMap[y-2][x - 1] != -2  && iMap[y+1][x - 1] != -1 && iMap[y+1][x - 1] != -2 && iMap[y-2][x+1] != -1 && iMap[y-2][x+1] != -2 && iMap[y+1][x+1] == -1)
							{								
								onetwoX = x+1;
								onetwoY = y+1;
								patOneTwo = true;
								return;	
							}
						}
					}
				}
			}
		}
	}
	for(int y = 2; y < rowDimension - 2; y++)
	{
		//left wall 
		//check if its 1-2 horizontal
		if(iMap[y][0] == 1 && iMap[y-1][0] == 2)
		{
			//check if top and bottom are covered
			if(iMap[y+1][0] != -1 && iMap[y+1][0] != -2 && iMap[y-2][0] != -1 && iMap[y-2][0] != -2)
			{
				//if top is covered bomb in bottom right
				if(iMap[y+1][1] != -1 && iMap[y+1][1] != -2 && iMap[y-2][1] == -1)
				{
					onetwoX = 1;
					onetwoY = y - 2;
					patOneTwo = true;
					return;
				}
			}
		}
		//right wall check
		if(iMap[y][colDimension - 1] == 1 && iMap[y][colDimension - 2] == 2)
		{
			//check if top and bottom are covered
			if(iMap[y+1][colDimension - 1] != -1 && iMap[y+1][colDimension - 1] != -2 && iMap[y-2][colDimension - 1] != -1 && iMap[y-2][colDimension - 1] != -2)
			{
				//if top is covered bomb in bottom right
				if(iMap[y+1][colDimension - 2] != -1 && iMap[y+1][colDimension - 2] != -2 && iMap[y-2][colDimension - 2] == -1)
				{
					onetwoX = colDimension - 2;
					onetwoY = y - 2;
					patOneTwo = true;
					return;
				}
			}
		}
		//check if 2-1 horizontal
		if(iMap[y][0] == 2 && iMap[y-1][0] == 1)
		{
			//check if top and bottom are covered
			if(iMap[y+1][0] != -1 && iMap[y+1][0] != -2 && iMap[y-2][0] != -1 && iMap[y-2][0] != -2)
			{	
				//if bottom is covered bomb in top left
				if(iMap[y-2][1] != -1 && iMap[y-2][1] != -2 && iMap[y+1][1] == -1)
				{
					onetwoX = 1;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}
			}
		}
		//right wall check
		if(iMap[y][colDimension - 1] == 1 && iMap[y][colDimension - 2] == 1)
		{
			//check if top and bottom are covered
			if(iMap[y+1][colDimension - 1] != -1 && iMap[y+1][colDimension - 1] != -2 && iMap[y-2][colDimension - 1] != -1 && iMap[y-2][colDimension - 1] != -2)
			{
				//if bottom is covered bomb in top left
				if(iMap[y-2][colDimension - 2] != -1 && iMap[y-2][colDimension - 2] != -2 && iMap[y+1][colDimension - 2] == -1)
				{
					onetwoX = colDimension - 2;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}
			}
		}
	}
	
	for(int y = 0; y < rowDimension; y++)
	{
		if(y + 1 < rowDimension && y - 1 >= 0)
		{
			//if there is a 1-2 pattern on the left wall
			if(iMap[y][0] == 1 && iMap[y][1] == 2)
			{
				//if top is uncovered;
				if(iMap[y][2] != -1 && iMap[y][2] != -2 && iMap[y+1][2] != -1 && iMap[y+1][2] != -2 && iMap[y+1][1] != -1 && iMap[y+1][1] != -2 && iMap[y+1][0] != -1 && iMap[y+1][0] != -2 && iMap[y-1][2] == -1)
				{
					onetwoX = 2;
					onetwoY = y - 1;
					patOneTwo = true;
					return;
				}
				//IF BOTTOM uncovered
				if(iMap[y][2] != -1 && iMap[y][2] != -2 && iMap[y-1][2] != -1 && iMap[y-1][2] != -2 && iMap[y-1][1] != -1 && iMap[y-1][1] != -2 && iMap[y-1][0] != -1 && iMap[y-1][0] != -2 && iMap[y+1][2] == -1)
				{
					onetwoX = 2;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}

			}
		}
		if(y + 1 < rowDimension && y - 1 >= 0)
		{
			//if there is a 2-1 pattern on the right wall
			if(iMap[y][colDimension - 1] == 1 && iMap[y][colDimension - 2] == 2 && iMap[y][colDimension - 3] != -1 && iMap[y][colDimension - 3] != -2)
			{ 
				//if the uncovered tiles are under the 1-1
				if((iMap[y-1][colDimension - 1] != -1 && iMap[y-1][colDimension - 1] != -2) && (iMap[y-1][colDimension - 2] != -1 && iMap[y-1][colDimension - 2] != -2) && (iMap[y-1][colDimension - 3] != -1 && iMap[y-1][colDimension - 3] != -2) && iMap[y+1][colDimension-3] == -1)
				{
					onetwoX = colDimension - 3;
					onetwoY = y + 1;
					patOneTwo = true;
					return;
				}
				//if the uncovered tiles are above the 1-1
				if((iMap[y+1][colDimension - 1] != -1 && iMap[y+1][colDimension - 1] != -2) && (iMap[y+1][colDimension - 2] != -1 && iMap[y+1][colDimension - 2] != -2) && (iMap[y+1][colDimension - 3] != -1 && iMap[y+1][colDimension - 3] != -2)&& iMap[y-1][colDimension-3] == -1)
				{
					onetwoX = colDimension - 3;
					onetwoY = y - 1;
					patOneTwo = true;
					return;
				}
			
			}
		}
	}
}

void MyAI::allMinesFlagged()
{
	for (int aX = 0; aX < colDimension; aX++ )
	{
		for (int aY = 0; aY < rowDimension; aY++ )
		{
			if(iMap[aY][aX] != 0 && iMap[aY][aX] != -1 && mapPattern[aY][aX] != -2)
			{
				int sMines = iMap[aY][aX];
				int flagged = 0;
				//top right
				if((aY + 1 < rowDimension) && (aX - 1 >= 0) && ((iMap[aY +1][aX - 1] == -2)))
				{
					flagged++;
				}
				//top middle
				if((aY + 1 < rowDimension) && (aX < colDimension) && ((iMap[aY + 1][aX] == -2)))
				{
					flagged++;
				}
				//top right
				if((aY + 1 < rowDimension) && (aX + 1 < colDimension) && (iMap[aY + 1][aX + 1] == -2))
				{
					flagged++;
				}
				//middle left
				if((aY < rowDimension) && (aX - 1 >= 0) && ((iMap[aY][aX - 1] == -2)))
				{
					flagged++;
				}
				//middle right
				if(aY < rowDimension && aX + 1 < colDimension && iMap[aY][aX + 1] == -2)
				{
					flagged++;
				}
				// bottom left
				if((aY - 1 >= 0) && (aX - 1 >= 0) && (iMap[aY - 1][aX - 1] == -2))
				{
					flagged++;
				}
				//bottom middle
				if((aY - 1 >= 0) && (aX < colDimension) && (iMap[aY - 1][aX] == -2))
				{
					flagged++;
				}
				//bottom right
				if((aY - 1 >= 0) && (aX + 1 < colDimension) && ((iMap[aY - 1][aX + 1] == -2)))
				{	
					flagged++;
				}
				if(flagged == sMines)
				{
					flagX = aX;
					flagY = aY;
					flaggedClear = true;
					mapPattern[aY][aX] = -2;
					return;
				}
			}
		}
	}

}
void MyAI::updateMap()
{
	//check if theirs mines near any pieces
	for (int aX = 0; aX < colDimension; aX++ )
	{
		for (int aY = 0; aY < rowDimension; aY++ )
		{
			if(iMap[aY][aX] != 0 && iMap[aY][aX] != -1 && iMap[aY][aX] != -2)
			{
				int sMines = iMap[aY][aX];
				//top left
				if(aY + 1 < rowDimension && aX - 1 >= 0 && iMap[aY +1][aX - 1] == -2)
				{
					--sMines;
				}
				//top middle
				if(aY + 1 < rowDimension && aX < colDimension && iMap[aY + 1][aX] == -2)
				{
					--sMines;
				}
				//top right
				if(aY + 1 < rowDimension && aX + 1 < colDimension && iMap[aY + 1][aX + 1] == -2)
				{
					--sMines;
				}
				//middle left
				if(aY < rowDimension && aX - 1 >= 0 && iMap[aY][aX - 1] == -2)
				{
					--sMines;
				}
				//middle right
				if(aY < rowDimension && aX + 1 < colDimension && iMap[aY][aX + 1] == -2)
				{
					--sMines;
				}
				// bottom left
				if((aY - 1 >= 0) && (aX - 1 >= 0) && (iMap[aY - 1][aX - 1] == -2))
				{
					--sMines;
				}
				//bottom middle
				if((aY - 1 >= 0) && (aX < colDimension) &&  (iMap[aY - 1][aX] == -2))
				{
					--sMines;
				}
				//bottom right
				if((aY - 1 >= 0) && (aX + 1 < colDimension) &&  (iMap[aY - 1][aX + 1] == -2))
				{	
					--sMines;
				}
				
				map[aY][aX] = sMines;
			}
		}
	}
}

void MyAI::checkOneTwoOne()
{
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			// if 1-2-1
			if(y + 1 < rowDimension && y - 1 >= 0 && x - 1 >= 0 && x + 3 < colDimension && map[y][x] == 1 && map[y][x+1] == 2 && map[y][x+2] == 1)
			{
				if(map[y][x-1] != -1 && map[y][x+3] != -1)
				{
					//if above is uncovered
					if(map[y+1][x-1] != -1 && map[y+1][x] != -1 && map[y+1][x+1] != -1 && map[y+1][x+2] != -1 && map[y+1][x+3] != -1
					&& map[y-1][x] == -1 && map[y-1][x+2] == -1)
					{
						otoXa = x;
						otoXb = x+2;
						otoYa = y -1;
						otoYb = y-1;
						patOneTwoOne = true;
						return;
					}
					
					//if under is uncovered
					if(map[y-1][x-1] != -1 && map[y-1][x] != -1&& map[y-1][x+1] != -1 && map[y-1][x+2] != -1 && map[y-1][x+3] != -1
					&& map[y+1][x] == -1 && map[y+1][x+2] == -1)
					{
						otoXa = x;
						otoXb = x+2;
						otoYa = y+1;
						otoYb = y+1;
						patOneTwoOne = true;
						return;
					}
				}
			}
			//roof above
			if(y + 1 >= rowDimension && x - 1 >= 0 && x + 3 < colDimension && map[y][x] == 1 && map[y][x+1] == 2 && map[y][x+2] == 1 && map[y][x-1] != -1 && map[y][x+3] != -1)
			{
				if(map[y-1][x] == -1 && map[y-1][x+2] == -1)
				{
					otoXa = x;
					otoXb = x+2;
					otoYa = y-1;
					otoYb = y-1;
					patOneTwoOne = true;
					return;	
				}
			}
			//floor below
			if(y - 1 < 0 && x - 1 >= 0 && x + 3 < colDimension && map[y][x] == 1 && map[y][x+1] == 2 && map[y][x+2] == 1 && map[y][x-1] != -1 && map[y][x+3] != -1)
			{
				if(map[y+1][x] == -1 && map[y+1][x+2] == -1)
				{
					otoXa = x;
					otoXb = x+2;
					otoYa = y+1;
					otoYb = y+1;
					patOneTwoOne = true;
					return;	
				}
			}
			//if 1-2-1 vertical
			if(y + 1 < rowDimension && y - 3 >= 0 && x - 1 >= 0 && x + 1 < colDimension && map[y][x] == 1 && map[y-1][x] == 2 && map[y-2][x] == 1)
			{
				if(map[y+1][x] != -1 && map[y-3][x] != -1)
				{
					//if right is uncovered
					if(map[y+1][x+1] != -1 && map[y][x+1] != -1 && map[y-1][x+1] != -1 && map[y-2][x+1] != -1 && map[y-3][x+1] != -1
					&& map[y][x-1] == -1 && map[y-2][x-1] == -1)
					{
						otoXa = x-1;
						otoXb = x-1;
						otoYa = y;
						otoYb = y-2;
						patOneTwoOne = true;
						return;						
					}
					//if left is uncovered
					if(map[y+1][x-1] != -1 && map[y][x-1] != -1 && map[y-1][x-1] != -1 && map[y-2][x-1] != -1 && map[y-3][x-1] != -1
					&& map[y][x+1] == -1 && map[y-2][x+1] == -1)
					{
						otoXa = x+1;
						otoXb = x+1;
						otoYa = y;
						otoYb = y-2;
						patOneTwoOne = true;	
						return;
					}
				}
			}
			//wall on left
			if(x-1 < 0 && y - 1 < rowDimension && y - 3 >= 0 && map[y][x] == 1 && map[y-1][x] == 2 && map[y-2][x] == 1)
			{
				if(map[y+1][x] != -1 && map[y-3][x] != -1 && map[y][x+1] == -1 && map[y-2][x+1] == -1)
				{
					otoXa = x+1;
					otoXb = x+1;
					otoYa = y;
					otoYb = y-2;
					patOneTwoOne = true;	
					return;
				}
			}
			//wall on left
			if(x+1 >= colDimension && y - 1 < rowDimension && y - 3 >= 0 && map[y][x] == 1 && map[y-1][x] == 2 && map[y-2][x] == 1)
			{
				if(map[y+1][x] != -1 && map[y-3][x] != -1 && map[y][x-1] == -1 && map[y-2][x-1] == -1)
				{
					otoXa = x-1;
					otoXb = x-1;
					otoYa = y;
					otoYb = y-2;
					patOneTwoOne = true;	
					return;
				}
			}
		}
	}
	
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			// if 1-2-1
			if(y + 1 < rowDimension && y - 1 >= 0 && x - 1 >= 0 && x + 3 < colDimension && iMap[y][x] == 1 && iMap[y][x+1] == 2 && iMap[y][x+2] == 1)
			{
				if(iMap[y][x-1] != -1 && iMap[y][x-1] != -2 && iMap[y][x+3] != -1 && iMap[y][x+3] != -2)
				{
					//if above is uncovered
					if(iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2 && iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y+1][x+2] != -1 && iMap[y+1][x+2] != -2 && iMap[y+1][x+3] != -1 && iMap[y+1][x+3] != -2
					&& iMap[y-1][x] == -1 && iMap[y-1][x+2] == -1)
					{
						otoXa = x;
						otoXb = x+2;
						otoYa = y -1;
						otoYb = y-1;
						patOneTwoOne = true;
						return;
					}
					
					//if under is uncovered
					if(iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2 && iMap[y-1][x] != -1 && iMap[y-1][x] != -2 && iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2 && iMap[y-1][x+2] != -1 && iMap[y-1][x+2] != -2 && iMap[y-1][x+3] != -1 && iMap[y-1][x+3] != -2
					&& iMap[y+1][x] == -1 && iMap[y+1][x+2] == -1)
					{
						otoXa = x;
						otoXb = x+2;
						otoYa = y+1;
						otoYb = y+1;
						patOneTwoOne = true;
						return;
					}
				}
			}
			//roof above
			if(y + 1 >= rowDimension && x - 1 >= 0 && x + 3 < colDimension && iMap[y][x] == 1 && iMap[y][x+1] == 2 && iMap[y][x+2] == 1 && iMap[y][x-1] != -1 && iMap[y][x-1] != -2 && iMap[y][x+3] != -1 && iMap[y][x+3] != -2)
			{
				if(iMap[y-1][x] == -1 && iMap[y-1][x+2] == -1)
				{
					otoXa = x;
					otoXb = x+2;
					otoYa = y-1;
					otoYb = y-1;
					patOneTwoOne = true;
					return;	
				}
			}
			//floor below 
			
			if(y - 1 < 0 && x - 1 >= 0 && x + 3 < colDimension && iMap[y][x] == 1 && iMap[y][x+1] == 2 && iMap[y][x+2] == 1 && iMap[y][x-1] != -1 && iMap[y][x-1] != -2 && iMap[y][x+3] != -1 && iMap[y][x+3] != -2)
			{
				if(iMap[y+1][x] == -1 && iMap[y+1][x+2] == -1)
				{
					otoXa = x;
					otoXb = x+2;
					otoYa = y+1;
					otoYb = y+1;
					patOneTwoOne = true;
					return;	
				}
			}
			//if 1-2-1 vertical
			if(y + 1 < rowDimension && y - 3 >= 0 && x - 1 >= 0 && x + 1 < colDimension && iMap[y][x] == 1 && iMap[y-1][x] == 2 && iMap[y-2][x] == 1)
			{
				if(iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y-3][x] != -1 && iMap[y-3][x] != -2)
				{
					//if right is uncovered
					if(iMap[y+1][x+1] != -1 && iMap[y+1][x+1] != -2 && iMap[y][x+1] != -1 && iMap[y][x+1] != -2 && iMap[y-1][x+1] != -1 && iMap[y-1][x+1] != -2 && iMap[y-2][x+1] != -1 && iMap[y-2][x+1] != -2 && iMap[y-3][x+1] != -1 && iMap[y-3][x+1] != -2
					&& iMap[y][x-1] == -1 && iMap[y-2][x-1] == -1)
					{
						otoXa = x-1;
						otoXb = x-1;
						otoYa = y;
						otoYb = y-2;
						patOneTwoOne = true;
						return;						
					}
					//if left is uncovered
					if(iMap[y+1][x-1] != -1 && iMap[y+1][x-1] != -2 && iMap[y][x-1] != -1 && iMap[y][x-1] != -2 && iMap[y-1][x-1] != -1 && iMap[y-1][x-1] != -2 && iMap[y-2][x-1] != -1 && iMap[y-2][x-1] != -2 && iMap[y-3][x-1] != -1 && iMap[y-3][x-1] != -2
					&& iMap[y][x+1] == -1 && iMap[y-2][x+1] == -1)
					{
						otoXa = x+1;
						otoXb = x+1;
						otoYa = y;
						otoYb = y-2;
						patOneTwoOne = true;	
						return;
					}
				}
			}
			//wall on left
			if(x-1 < 0 && y + 1 < rowDimension && y - 3 >= 0 && iMap[y][x] == 1 && iMap[y-1][x] == 2 && iMap[y-2][x] == 1)
			{
				if(iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y-3][x] != -1 && iMap[y-3][x] != -2 && iMap[y][x+1] == -1 && iMap[y-2][x+1] == -1)
				{
					otoXa = x+1;
					otoXb = x+1;
					otoYa = y;
					otoYb = y-2;
					patOneTwoOne = true;	
					return;
				}
			}
			//wall on left
			
			if(x+1 >= colDimension && y + 1 < rowDimension && y - 3 >= 0 && iMap[y][x] == 1 && iMap[y-1][x] == 2 && iMap[y-2][x] == 1)
			{
				if(iMap[y+1][x] != -1 && iMap[y+1][x] != -2 && iMap[y-3][x] != -1 && iMap[y-3][x] != -2 && iMap[y][x-1] == -1 && iMap[y-2][x-1] == -1)
				{
					otoXa = x-1;
					otoXb = x-1;
					otoYa = y;
					otoYb = y-2;
					patOneTwoOne = true;	
					return;
				}
			}
		}
	}
}
void MyAI::checkOneTwoTwoOne()
{
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			if( x + 4 < colDimension && x - 1 >= 0 && map[y][x-1] != -1 && map[y][x+4] != -1 && map[y][x] == 1 && map[y][x+1] == 2 && map[y][x+2] == 2 
				&& map[y][x+3] == 1)
			{
				//if roof
				if(y+1 >= rowDimension && map[y-1][x+1] == -1 && map[y-1][x+2] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+2;
					ottoYb = y-1;
					patOneTwoTwoOne = true;
					return;
				}
				//if floor
				if(y - 1 < 0 && map[y+1][x+1] == -1 && map[y+1][x+1] == -1)
				{
					ottoXa = x+1;
					ottoYa = y +1;
					ottoXb = x+2;
					ottoYb = y+1;
					patOneTwoTwoOne = true;
					return;
				}
				
				//inner patterns 
				//if uncovered top
				if(y+1 < rowDimension && y - 1 >= 0 && map[y+1][x-1] != -1 && map[y+1][x] != -1 && map[y+1][x+1] != -1 && map[y+1][x+2] != -1 && map[y+1][x+3] != -1 && map[y+1][x+4] != -1
					&& map[y-1][x+1] == -1 && map[y-1][x+2] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+2;
					ottoYb = y-1;
					patOneTwoTwoOne = true;
					return;
				}
				
				//if uncovered bottom
				if(y+1 < rowDimension && y - 1 >= 0 && map[y-1][x-1] != -1 && map[y-1][x] != -1 && map[y-1][x+1] != -1 && map[y-1][x+2] != -1 && map[y-1][x+3] != -1 && map[y-1][x+4] != -1
					&& map[y+1][x+1] == -1 && map[y+1][x+2] == -1)
				{
					ottoXa = x+1;
					ottoYa = y+1;
					ottoXb = x+2;
					ottoYb = y+1;
					patOneTwoTwoOne = true;
					return;
				}
			}
			//horizontal
			if(y - 4 >= 0 && y + 1 < rowDimension && map[y][x] == 1 && map[y-1][x] == 2 && map[y-2][x] == 2 && map[y-3][x] == 1 && map[y+1][x] != -1 && map[y-4][x] != -1)
			{
				//wall to left
				if(x - 1 < 0 && map[y-1][x+1] == -1 && map[y-2][x+1] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
				
				//wall to right
				if(x + 1 >= colDimension && map[y-1][x-1] == -1 && map[y-2][x-1] == -1)
				{
					ottoXa = x-1;
					ottoYa = y -1;
					ottoXb = x-1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
				//if left side covered
				if(x+1 < colDimension && x -1 >= 0 && map[y+1][x-1] != -1  && map[y][x-1] != -1  && map[y-1][x-1] != -1  && map[y-2][x-1] != -1  && map[y-3][x-1] != -1  && map[y-4][x-1] != -1
				&& map[y-1][x+1] == -1 && map[y-2][x+1] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
				//if right side covered
				if(x+1 < colDimension && x -1 >= 0 && map[y+1][x+1] != -1  && map[y][x+1] != -1  && map[y-1][x+1] != -1  && map[y-2][x+1] != -1  && map[y-3][x+1] != -1  && map[y-4][x+1] != -1
				&& map[y-1][x-1] == -1 && map[y-2][x-1] == -1)
				{
					ottoXa = x-1;
					ottoYa = y -1;
					ottoXb = x-1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
			}
		}
	}
	
	for ( int x = 0; x < colDimension; x++ )
	{
        for ( int y = 0; y < rowDimension; y++ )
		{
			if(x + 4 < colDimension && x - 1 >= 0 && iMap[y][x-1] != -1 && iMap[y][x+4] != -1 && iMap[y][x-1] != -2 && iMap[y][x+4] != -2 && iMap[y][x] == 1 && iMap[y][x+1] == 2 && iMap[y][x+2] == 2 
				&& iMap[y][x+3] == 1)
			{
				//if roof
				if(y+1 >= rowDimension && iMap[y-1][x+1] == -1 && iMap[y-1][x+2] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+2;
					ottoYb = y-1;
					patOneTwoTwoOne = true;
					return;
				}
				//if floor
				if(y - 1 < 0 && iMap[y+1][x+1] == -1 && iMap[y+1][x+1] == -1)
				{
					ottoXa = x+1;
					ottoYa = y +1;
					ottoXb = x+2;
					ottoYb = y+1;
					patOneTwoTwoOne = true;
					return;
				}
				
				//inner patterns 
				//if uncovered top
				if(y - 1 >= 0 && y+1 < rowDimension && iMap[y+1][x-1] != -1 && iMap[y+1][x] != -1 && iMap[y+1][x+1] != -1 && iMap[y+1][x+2] != -1 && iMap[y+1][x+3] != -1 && iMap[y+1][x+4] != -1
					&& iMap[y+1][x-1] != -2 && iMap[y+1][x] != -2 && iMap[y+1][x+1] != -2 && iMap[y+1][x+2] != -2 && iMap[y+1][x+3] != -2 && iMap[y+1][x+4] != -2
					&& iMap[y-1][x+1] == -1 && iMap[y-1][x+2] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+2;
					ottoYb = y-1;
					patOneTwoTwoOne = true;
					return;
				}
				
				//if uncovered bottom
				if(y+1 < rowDimension && y - 1 >= 0 && iMap[y-1][x-1] != -1 && iMap[y-1][x] != -1 && iMap[y-1][x+1] != -1 && iMap[y-1][x+2] != -1 && iMap[y-1][x+3] != -1 && iMap[y-1][x+4] != -1
					&& iMap[y-1][x-1] != -2 && iMap[y-1][x] != -2 && iMap[y-1][x+1] != -2 && iMap[y-1][x+2] != -2 && iMap[y-1][x+3] != -2 && iMap[y-1][x+4] != -2
					&& iMap[y+1][x+1] == -1 && iMap[y+1][x+2] == -1)
				{
					ottoXa = x+1;
					ottoYa = y+1;
					ottoXb = x+2;
					ottoYb = y+1;
					patOneTwoTwoOne = true;
					return;
				}
			}
			
			//horizontal
			if(y - 4 >= 0 && y + 1 < rowDimension && iMap[y][x] == 1 && iMap[y-1][x] == 2 && iMap[y-2][x] == 2 && iMap[y-3][x] == 1 && iMap[y+1][x] != -1 && iMap[y-4][x] != -1  && iMap[y+1][x] != -2 && iMap[y-4][x] != -2)
			{
				//wall to left
				if(x - 1 < 0 && iMap[y-1][x+1] == -1 && iMap[y-2][x+1] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
				
				//wall to right
				if(x + 1 >= colDimension && iMap[y-1][x-1] == -1 && iMap[y-2][x-1] == -1)
				{
					ottoXa = x-1;
					ottoYa = y -1;
					ottoXb = x-1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
				//if left side covered
				if(x+1 < colDimension && x -1 >= 0 && iMap[y+1][x-1] != -1  && iMap[y][x-1] != -1  && iMap[y-1][x-1] != -1  && iMap[y-2][x-1] != -1  && iMap[y-3][x-1] != -1  && iMap[y-4][x-1] != -1
					&& iMap[y+1][x-1] != -2  && iMap[y][x-1] != -2  && iMap[y-1][x-1] != -2  && iMap[y-2][x-1] != -2  && iMap[y-3][x-1] != -2  && iMap[y-4][x-1] != -2
					&& iMap[y-1][x+1] == -1 && iMap[y-2][x+1] == -1)
				{
					ottoXa = x+1;
					ottoYa = y -1;
					ottoXb = x+1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
				//if right side covered
				if(x+1 < colDimension && x -1 >= 0 && iMap[y+1][x+1] != -1  && iMap[y][x+1] != -1  && iMap[y-1][x+1] != -1  && iMap[y-2][x+1] != -1  && iMap[y-3][x+1] != -1  && iMap[y-4][x+1] != -1
					&& iMap[y+1][x+1] != -2  && iMap[y][x+1] != -2  && iMap[y-1][x+1] != -2  && iMap[y-2][x+1] != -2  && iMap[y-3][x+1] != -2  && iMap[y-4][x+1] != -2
					&& iMap[y-1][x-1] == -1 && iMap[y-2][x-1] == -1)
				{
					ottoXa = x-1;
					ottoYa = y -1;
					ottoXb = x-1;
					ottoYb = y-2;
					patOneTwoTwoOne = true;
					return;
				}
			}
		}
	}
}

void MyAI::guess()
{
	for ( int x = 0; x < colDimension; x++ )
    {
		if(iMap[rowDimension - 1][x] == -1)
		{
			guessY = rowDimension - 1;
			guessX = x;
			return;
		}
		if(iMap[0][x] == -1)
		{
			guessY = 0;
			guessX = x;
			return;
		}
	}
	for(int y = 0; y < rowDimension; y++)
	{
		if(iMap[y][0] == -1)
		{
			guessY = y;
			guessX = 0;
			return;
		}
		if(iMap[y][colDimension - 1] == -1)
		{
			guessY = y;
			guessX = colDimension - 1;
			return;
		}
	}
	do
	{
		guessX = rand() % colDimension;
		guessY = rand() % rowDimension;
	}
	while(iMap[guessY][guessX] != -1);
	return;
}

bool MyAI::checkDone()
{
	for ( int x = 0; x < colDimension; x++ )
    {
        for ( int y = 0; y < rowDimension; y++ )
		{
            if(iMap[y][x] == -1)
			{
				return false;
			}
		}
	}
	return true;
}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================
// ======================================================================