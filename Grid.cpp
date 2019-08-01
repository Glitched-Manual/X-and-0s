#include "Grid.h"

Grid::Grid()
{
	
    SetGameTiles();
	if (debug.is_debug_mode())
	{
		std::cout << "Tiles set" << std::endl;
	}
  
}

Grid::~Grid()
{
	if(debug.is_debug_mode())
	{
		std::cout << "Grid Destructor called" << std::endl;
	}
	
}


Tile Grid::GetGameTile(int passed_x, int passed_y)
{ 
	if (debug.is_debug_mode())
	{
		std::cout << "GetGameTiles Called" << std::endl;
	}

	return game_tiles[passed_x][passed_y]; 
}

void Grid::SetGameTiles()
{
	if (debug.is_debug_mode())
	{
		std::cout << "SetGameTiles Called" << std::endl;
	}
	//y cordinate iteration
for(unsigned int yi = 0; yi < 3; yi++)
    {
	//loop through x cordinate iteration before increasing y iteration
        for(unsigned int xi = 0; xi < 3; xi++)
        {
			game_tiles[xi][yi].SetTilePosition(xi,yi);
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
           std::cout << " " << *GetGameTile(xi,yi).GetTileMark() << " |";
          //if x == 2 add "\n" and "-----\n"  
          if(xi==2)
	  {
	   std::cout<< "\n ----------\n";
	  }
        }
    }
  std::cout<< "\n";
}

bool Grid::LoadGameObjectContent()
{
	//load texture
	game_grid_texture = NULL;

	//open grid image

}


void Grid::Draw(SDL_Renderer* passed_Renderer)
{
	//render texture
}


void Grid::Update()
{
	//update if animated probably not for now
}

void Grid::CleanGameObjectContent()
{

}