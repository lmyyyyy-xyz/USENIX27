# $Id: w203_1.zpl,v 1.1 2006/01/27 19:57:32 bzfkocht Exp $
param p := 3;
set V := { 1 .. 3 };
set P := { 1 .. p };
var x[V * P] binary;
subto cap: forall <p> in P do sum <v> in V : x[v,p] <= 2;
