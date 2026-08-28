X = 0.1:0.05:38;
Y1 = (15000. - 120*X)/210;
Y2 = max((4000 - 110.*X)./30, 0);
Y3 = max(75 - X, 0.);
Ytop = min(min(Y1, Y2), Y3);
plot2d3(X, Ytop)

X=15:20:35;
plot2d(X,(6315.63-143.0*X)/60.0)
xtitle('Solution space and objective')

x = [1, 1; 110, 30] \ [75; 4000]
P = [143, 60] * x
