/* Unnamed */

/* Objective function */
max: +2 C1 +3 C2 -2 C3 +3 C4 +3 c5;

/* Constraints */
+0.5 C1 +4 C2 +3 C3 +C4 +2 c5 >= 3;
+C1 +2 C2 +C3 +4 C4 +2 c5 = 8;

/* Variable bounds */
C2 >= 2;
C4 <= 5.3;

/* Integer definitions */
int C4;
