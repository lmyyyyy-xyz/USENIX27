X = 0.1:0.1:125;
Y1 = (15000. - 120*X)/210;
bar(X, Y1);

X = 0.1:0.05:40;
Y1 = (15000. - 120*X)/210;
Y2 = max((4000 - 110.*X)./30, 0);
Y3 = max(75 - X, 0);
Ytop = min([Y1; Y2; Y3]);
bar(X, Ytop);

hold on
X=15:25:40;
title('Solution space and objective')
plot(X,(6315.63-143.0*X)/60.0);
hold off

x = [1 1; 110 30] \ [75; 4000]
P = [143 60] * x
