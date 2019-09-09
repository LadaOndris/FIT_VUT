
#include "m.h"

// zde vznikne externi definice ?
extern int f1(void); 

int f2(void) {
    return f1();
}
