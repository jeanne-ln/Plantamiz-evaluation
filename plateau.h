#ifndef PLANTAMIZ_PLATEAU_H
#define PLANTAMIZ_PLATEAU_H

#include "plantamiz.h"

void initialise_plateau(plateau* ptab);
void echange(plateau* ptab, position* A, position* B);
void chute(plateau* ptab, position* trou, char element);
void bouche_les_trous(plateau* ptab);

#endif //PLANTAMIZ_PLATEAU_H
