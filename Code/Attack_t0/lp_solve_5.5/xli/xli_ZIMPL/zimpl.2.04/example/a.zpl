# Variable definitions
var x1 integer >= 0;
var x2 integer >= 0;

# Objective function
maximize obj: -x1 +2*x2;

# Constraints
subto C1: +5 >= +2*x1 +x2 >= 1;
subto R2: -4*x1 +4*x2 <= 5;
