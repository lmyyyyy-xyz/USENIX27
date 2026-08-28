# $Id: w165.zpl,v 1.1 2003/09/08 15:41:30 bzfkocht Exp $
set A:={1,2};
set B:={<1,1>,<2,2>};
param x := if A == B then 1 else 2 end;