rem flex -L -l lp_rlpt.l
flex -L lp_rlpt.l
rem sed -e "s/yy/lpt_yy/g" lex.yy.c >lp_rlpt.inc
sed -e "s/yy/lpt_yy/g" lex.yy.c | sed -e "s/^#line.*//g" >lp_rlpt.inc
del lex.yy.c

bison --no-lines -y lp_rlpt.y
sed -e "s/yy/lpt_yy/g" y.tab.c >lp_rlpt.c
del y.tab.c
