#include "Win_Case.h"
void Win_Case::SetWinCaseCombination(Position first_position, Position second_position,Position third_position)
{
combination[0] = first_position;
combination[1] = second_position;
combination[2] = third_position;
}




Position Win_Case::GetCombination(int passed_index){ 
if(passed_index > 2){
    passed_index = passed_index % 3;
    
}

return combination[passed_index];


}
