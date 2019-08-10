#include "Win_Case.h"

Win_Case:: Win_Case()
{
	//combination = std::make_shared<Position[]>(new Position[3], [](Position* comb) { delete[]comb; });
	unsigned int combination_index = 0;

	combination[combination_index] = new Position;
	combination_index++;
	combination[combination_index] = new Position;
	combination_index++;
	combination[combination_index] = new Position;

}

Win_Case::Win_Case(Position* first_position, Position* second_position, Position* third_position)
{
	unsigned int combination_index = 0;

	combination[combination_index] = first_position;
	combination_index++;
	combination[combination_index] = second_position;
	combination_index++;
	combination[combination_index] = third_position;
}

Win_Case:: ~Win_Case()
{


}

 Position* Win_Case::GetCombination(int passed_index) 
 {
	if (passed_index > 2) 
	{
		passed_index = passed_index % 3;

	}

	return combination[passed_index];
	
}

void Win_Case::SetWinCaseCombination(Position first_position, Position second_position, Position third_position)
{
	//set 0-2 combination

	// increase to make to next iteration got tired of typing 0,1,2
	int combo_num = 0;

	combination[combo_num]->SetX(*first_position.GetX());
	combination[combo_num]->SetY(*first_position.GetY()); //nullptr break

    ++combo_num;

	combination[combo_num]->SetX(*second_position.GetX());
	combination[combo_num]->SetY(*second_position.GetY());

	++combo_num;

	combination[combo_num]->SetX(*third_position.GetX());
	combination[combo_num]->SetY(*third_position.GetY());
}