#include "Win_Case.h"
void Win_Case::SetPositionCombination()

{

}




Position Win_Case::GetCombination(int passed_index){ 
if(passed_index > 3){
    passed_index = passed_index % 3;
    
}

return combination[passed_index];


}
