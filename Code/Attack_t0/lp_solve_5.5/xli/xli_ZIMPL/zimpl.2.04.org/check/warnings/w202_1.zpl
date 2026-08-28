# $Id: w202_1.zpl,v 1.1 2006/01/19 20:53:06 bzfkocht Exp $
set E := { 1..3 } * { 4..5 };
set X := { <i,j> in E with i > 10: <i + j, 6> };
