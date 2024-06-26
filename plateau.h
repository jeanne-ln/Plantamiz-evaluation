#ifndef PLANTAMIZ_PLATEAU_H
#define PLANTAMIZ_PLATEAU_H

#include "plantamiz.h"

plateau* premier_plateau();
void echange(plateau* ptab, position* A, position* B);
void chute(plateau* ptab, position* trou, char element);

#endif //PLANTAMIZ_PLATEAU_H
