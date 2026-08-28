/* chvatal_diet.zpl */

/* Objective function */
min: +3 C1 +24 C2 +13 C3 +9 C4 +20 C5 +19 C6;

/* Constraints */
need_1: +110 C1 +205 C2 +160 C3 +160 C4 +420 C5 +260 C6 >= 2000;
need_2: +4 C1 +32 C2 +13 C3 +8 C4 +4 C5 +14 C6 >= 55;
need_3: +2 C1 +12 C2 +54 C3 +284 C4 +22 C5 +80 C6 >= 800;

/* Variable bounds */
C1 <= 4;
C2 <= 3;
C3 <= 2;
C4 <= 8;
C5 <= 2;
C6 <= 2;

/* Integer definitions */
int C1,C2,C3,C4,C5,C6;
