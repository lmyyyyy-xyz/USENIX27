/* a.zpl */

/* Objective function */
max: -x1 +2 x2;

/* Constraints */
C1_1: +5 >= +2 x1 +x2 >= 1;
R2_1: -4 x1 +4 x2 <= 5;

/* Integer definitions */
int x1,x2;
