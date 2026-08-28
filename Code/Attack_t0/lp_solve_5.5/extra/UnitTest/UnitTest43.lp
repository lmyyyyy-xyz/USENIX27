/* Objective function */
min: +89000 C1 +11000 C2 +1000 C3;

/* Constraints */
Nutr643Abs: +227.272727273 C1 +184.848484848 C2 +1010.1010101 C3 <= 601;
Nutr649Abs: +1010.1010101 C1 >= 225;
IngStep3: +C3 -0.003 C4 + C5 = 0;
IngRes2Rel0: -0.56 C1 +0.44 C2 >= 0;
IngRes2Rel1: -0.7 C1 +0.3 C2 <= 0;
total: +C1 +C2 +C3 = 1;

/* Variable bounds */
71.1 <= C4 <= 71.9;

/* Integer definitions */
int C4;
