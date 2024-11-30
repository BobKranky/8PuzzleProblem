// Hasan Raza
// Solution Finder for the 8 Puzzle Problem Using Iterative Depth-First-Search

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int ROWS = 3;
const int COLS = 3;
const int DEPTHMAX = 10; //predetermined max depth. if the maxdepth is reached then the algorithm backtracks
bool up = true;
bool down = true;
bool right = true;
bool left = true;
int depth = 0;
int currentposition = 0;

bool pathAvail[4] = {up, down, left, right};

std::vector<int> queue; //vector for DFS queue
std::vector<int> moves; //vector for moves made since start state
std::vector<int> reversemoves; //vector for reverse moves made since start state. used to easily know how to back to start state
std::vector<int> depthmoves; // vector for keeping track of depth of moves in queue. 

std::vector<int> pastmoves; // vector for keeping track of past moves.
std::vector<int> paststates; // vector for keeping track of past states. 
std::vector<int> futurestates; // vector for keeping track of future states. 

//std::string availability[2] = {"Not available", "Available"}; uncomment this line and lines 321 - 325 to see how availablemoves works. 

int grid[3][3] = {{4, 1, 2},  //start grid
                  {7, 6, 3},
                  {5, 0, 8}};


int idealGrid[3][3] = {{1, 2, 3}, //End grid
                       {4, 5, 6},
                       {7, 8, 0}};

void swap(int tempArray[ROWS][COLS], int row1, int col1, int row2, int col2) //swap function for moving 0. very important function
{
  int a = tempArray[row1][col1];
  int b = tempArray[row2][col2];

  tempArray[row1][col1] = b;
  tempArray[row2][col2] = a;
}

void printGrid() //prints grid
{
  for (int row = 0; row < 3; row++)
  {
    for (int col = 0; col < 3; col++)
    {
      std::cout << grid[row][col] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int findZeroRow() //searches through function and discovers the row that the 0 is residing. 
{
  int row;
  int col;

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (grid[i][j] == 0)  //the for loops search through grid until 0 tile is found.
      {
        row = i;
        col = j;
        break;
      }
      else
      {
      }
    }
  }
  return row;
}

int findZeroCol() //searches through function and discovers the column that the 0 is residing. 
{
  int row;
  int zero;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (grid[i][j] == 0) //the for loops search through grid until 0 tile is found.
      {
        row = i;
        zero = j;
        break;
      }
      else
      {
      }
    }
  }
  return zero;
}

void findZero() //finds exact location of zero and prints it to terminal
{

  int row = findZeroRow();
  int col = findZeroCol(); //uses previous two functions to easily grab row and column of 0

  std::cout << "The zero is located at " << row << " " << col << std::endl;
  std::cout << std::endl;
}

void moveLeft() //function to move 0 left.
{
  int row = findZeroRow();
  int col = findZeroCol(); //grabs row and column of 0

  if (col == 0 || queue.back() != 2) //if column = 0 or the end of the queue is not == 2, then you cannot move left. 
  {
    std::cout << "Cannot move left: "<<std::endl;
  }
  else if (queue.back() == 2) //if end of the queue is == 2, move left
  {
    swap(grid, row, col - 1, row, col);
    std::cout << "Move left: " << std::endl;

    moves.push_back(2);         //left move is added to history 
    reversemoves.push_back(3);  //reverse of left (right) move is added to reverse history 
    queue.pop_back();           //queue is popped as end of queue move was just made
    depthmoves.pop_back();      //depthmoves is popped as end of queue move was just made 
    depth++;                    //since a DFS move was made, our depth is now 1 greater
  }
  else
  {
    std::cout << "Error moving left" << std::endl;
  }
  printGrid();
}

void moveRight() //function to move 0 right.
{
  int row = findZeroRow();
  int col = findZeroCol();

  if (col == 2 || queue.back() != 3) //if column = 2 or the end of the queue is not == 3, then you cannot move right. 
  {
    std::cout << "Cannot move right" << std::endl;
  }
  else if (queue.back() == 3)
  {
    swap(grid, row, col + 1, row, col);
    std::cout << "Move right " << std::endl;

    moves.push_back(3);         //right move is added to history 
    reversemoves.push_back(2);  //reverse of right (left) move is added to reverse history 
    queue.pop_back();           //queue is popped as end of queue move was just made
    depthmoves.pop_back();      //depthmoves is popped as end of queue move was just made 
    depth++;                    //since a DFS move was made, our depth is now 1 greater
  }
  else
  {
    std::cout << "Error moving right" << std::endl;
  }
  printGrid();
}

void moveUp() //function to move 0 up.
{
  int row = findZeroRow();
  int col = findZeroCol();

  if (row == 0 || queue.back() != 0)
  {
    std::cout << "Cannot move up" << std::endl;
  }
  else if (queue.back() == 0)
  {
    swap(grid, row - 1, col, row, col);
    std::cout << "Move up " << std::endl;

    moves.push_back(0);                   //up move is added to history
    reversemoves.push_back(1);            //reverse of up (down) move is added to reverse history 
    queue.pop_back();                     //queue is popped as end of queue move was just made
    depthmoves.pop_back();                //depthmoves is popped as end of queue move was just made 
    depth++;                              //since a DFS move was made, our depth is now 1 greater
  }
  else
  {
    std::cout << "Error moving up" << std::endl;
  }
  printGrid();
}

void moveDown() //function to move 0 down.
{
  int row = findZeroRow();
  int col = findZeroCol();

  if (row == 2 || queue.back() != 1)
  {

  }
  else if (queue.back() == 1)
  {
    swap(grid, row + 1, col, row, col);
    std::cout << "Move down " << std::endl;
    
    moves.push_back(1);                         
    reversemoves.push_back(0);              
    queue.pop_back();                         
    depthmoves.pop_back();                    
    depth++;                                  
  }
  else
  {
    std::cout << "Error moving down" << std::endl;
  }
  printGrid();
}

int availableMoves() //discovers all available moves that 0 can do. also makes sure that the 0 is not revisiting states it has already visited.
{
  int row = findZeroRow();
  int col = findZeroCol();

  int pathavailable = 0;

  if (depth == DEPTHMAX) //if depth reaches predetermined max, there are no available moves
  {
    pathAvail[0] = false;
    pathAvail[1] = false;
    pathAvail[2] = false;
    pathAvail[3] = false;
    pathavailable = 0;
  }
  else if (depth < DEPTHMAX) //checks available moves based on position: ie, if the zero is against an edge, cannot cross it
  {
    if (row == 0)
    {
      up = false;
    }
    else
    {
      up = true;
    }

    if (row == 2)
    {
      down = false;
    }
    else
    {
      down = true;
    }

    if (col == 0)
    {

      left = false;
    }
    else
    {
      left = true;
    }
    if (col == 2)
    {

      right = false;
    }
    else
    {
      right = true;
    }

    
    currentposition = 0;


    for (int i = 0; i < reversemoves.size(); i++) //used to determine position of zero in relation to the moves it took to get there from the start state. 
    {

      currentposition = currentposition * 10 + reversemoves[i];
    }

    //std::cout << currentposition << std::endl;

    for (int i = 0; i < 4; i++) //uses current position to determine its potential future states. 
    {
      futurestates.push_back(currentposition * 10 + i);
    }

    for (int i = 0; i < paststates.size(); i++) //if future states have already been accessed, then the zero is not allowed to move there again
    {
      for (int j = 0; j < 4; j++)
      {
        if (paststates[i] == futurestates[j]) //checks if each future state is already in the past states
        {
          switch (j)
          {
          case 0:
            down = false;
            break;
          case 1:
            up = false;
            break;
          case 2:
            right = false;
            break;
          case 3:
            left = false;

            break;
          }
        }
      }
    }
    futurestates.clear(); //clears future states after available moves have been determined

    pathAvail[0] = up;
    pathAvail[1] = down;
    pathAvail[2] = left;
    pathAvail[3] = right;

    pathavailable = up + down + left + right; //determines number of available paths

    // std::cout << "The available moves are: " << std::endl;
    // std::cout << "right: " << availability[right] << std::endl;
    // std::cout << "up: " << availability[up] << std::endl;
    // std::cout << "down: " << availability[down] << std::endl;
    // std::cout << "left: " << availability[left] << std::endl;
    //findZero();
  }
  return pathavailable;
}

bool compareGrids() //compares current grid to ideal grid. returns true if they are identical
{
  int points = 0;
  bool result = false;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (grid[i][j] != idealGrid[i][j])
      {
        result = false;
      }
      else
      {
        points++; //counts the matching numbers
      }
    }
  }

  if (points == 9) //if all tiles are in correct position
  {
    result = true;
  }
  return result;
}

void backtrack() //backtracks if there are no available moves or depth reaches predetermined end point. 
{

  int row = findZeroRow();
  int col = findZeroCol();

  if (!reversemoves.empty() && depth > 0) //checks if we are not in start state and have a depth of >0
  {
    std::cout << "Backtracking: " << std::endl;

    if (reversemoves.back() == 0) //checks reversemoves to undo the most recent move. 
    {
      swap(grid, row - 1, col, row, col); //swaps
      printGrid();
      reversemoves.pop_back();  //pops reversemoves

      depth--;
      //std::cout << depth << std::endl;
    }
    else if (reversemoves.back() == 1) //checks reversemoves to undo the most recent move. 
    {
      swap(grid, row + 1, col, row, col);
      printGrid();
      reversemoves.pop_back();

      depth--;
      //std::cout << depth << std::endl;
    }
    else if (reversemoves.back() == 2)  //checks reversemoves to undo the most recent move. 
    {
      swap(grid, row, col - 1, row, col);
      printGrid();
      reversemoves.pop_back();
      depth--;
      //std::cout << depth << std::endl;
    }
    else if (reversemoves.back() == 3)  //checks reversemoves to undo the most recent move. 
    {
      swap(grid, row, col + 1, row, col);
      printGrid();
      reversemoves.pop_back();
      depth--;
      //std::cout << depth << std::endl;
    }
    else
    {
    }
  }
  else
  {
    std::cout << "Cannot backtrack" << std::endl;
  }
}

void addQueue() //adds moves to queue
{
  availableMoves(); //checks available moves

  if (depth < DEPTHMAX) //if depth is smaller than predetermined max, add available moves onto queue. 
  {
    
    if (up == 1)
    {
      queue.push_back(0);               //pushes avaialble moves
      depthmoves.push_back(depth + 1);  //pushes depth of avaialble moves
    }
    if (down == 1)
    {
      queue.push_back(1);
      depthmoves.push_back(depth + 1);
    }
    if (left == 1)
    {
      queue.push_back(2);
      depthmoves.push_back(depth + 1);
    }
    if (right == 1)
    {
      queue.push_back(3);
      depthmoves.push_back(depth + 1);
    }
  }
}

void checkMoves() // adds current state to past states
{
  currentposition = 0;
  for (int i = 0; i < reversemoves.size(); i++)
  {
    currentposition = currentposition * 10 + reversemoves[i];
  }
  paststates.push_back(currentposition);
}

void movequeue() //function to control how moves are made and pastmoves are saved. 
{
  {                         //makes a move depending on end of queue.
    if (queue.back() == 0)
    {
      moveUp();
      pastmoves.push_back(0);
    }
    else if (queue.back() == 1)
    {
      moveDown();
      pastmoves.push_back(1);
    }

    else if (queue.back() == 2) 
    {
      moveLeft();
      pastmoves.push_back(2);
    }

    else if (queue.back() == 3) 
    {
      moveRight();
      pastmoves.push_back(3);
    }
    else
    {
      std::cout << "cannot move " << std::endl;
    }
    checkMoves();
  }
}

void DFS() //depth first search 
{
  availableMoves(); //checks available moves.

  printGrid(); //prints grid

  {
    while (compareGrids() != true)
    {

      if (depth == DEPTHMAX)
    {
      backtrack();

    }

      if (depth < DEPTHMAX && availableMoves() == 0)
      {
        backtrack();
      }
      
      addQueue();

      movequeue();
    }
  }
}

int main()
{
  DFS();

  return 0;
}
