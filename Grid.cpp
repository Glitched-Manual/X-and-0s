#include "Grid.h"

Grid::Grid()
{
    SetGameTiles();
    std::cout << "Tiles set" << std::endl;
}

void Grid::SetGameTiles()
{ 
    for(unsigned int yi = 0; yi < 3; yi++)
    {
        for(unsigned int xi = 0; xi < 3; xi++)
        {
             GetGameTile(xi,yi)->SetTilePosition(xi,yi);
        }
    }
}

void Grid::DisplayGrid()
{
/*

 x | x | x |\n
 ---------- \n
 x | x | x |\n
 ---------- \n
 x | x | x |\n
*/


for(unsigned int yi = 0; yi < 3; yi++)
    {
        for(unsigned int xi = 0; xi < 3; xi++)
        {
            // game_tiles[xi][yi].SetTilePosition(xi,yi);
           std::cout << " " << GetGameTile(xi,yi)->GetTileMark() << " |";
          //if x == 2 add "\n" and "-----\n"  
          if(xi==2)
	  {
	   std::cout<< "\n ----------\n";
	  }
        }
    }
  std::cout<< "\n";
}
