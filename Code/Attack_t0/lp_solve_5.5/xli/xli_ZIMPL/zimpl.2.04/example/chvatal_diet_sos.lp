/* chvatal_diet_sos.zpl */

/* Objective function */
min: +3 x$Oatmeal +24 x$Chicken +13 x$Eggs +9 x$Milk +20 x$Pie +19 x$Pork;

/* Constraints */
need_;Energy;: +110 x$Oatmeal +205 x$Chicken +160 x$Eggs +160 x$Milk +420 x$Pie +260 x$Pork >= 2000;
need_;Protein;: +4 x$Oatmeal +32 x$Chicken +13 x$Eggs +8 x$Milk +4 x$Pie +14 x$Pork >= 55;
need_;Calcium;: +2 x$Oatmeal +12 x$Chicken +54 x$Eggs +284 x$Milk +22 x$Pie +80 x$Pork >= 800;

/* Variable bounds */
x$Oatmeal <= 4;
x$Chicken <= 3;
x$Eggs <= 2;
x$Milk <= 8;
x$Pie <= 2;
x$Pork <= 2;

/* Integer definitions */
int x$Oatmeal,x$Chicken,x$Eggs,x$Milk,x$Pie,x$Pork;

/* SOS definitions */
SOS
s1_: x$Oatmeal:100,x$Chicken:200 <= 1;
SOS
s2_: x$Oatmeal:100,x$Chicken:200,x$Eggs:300 <= 2;
