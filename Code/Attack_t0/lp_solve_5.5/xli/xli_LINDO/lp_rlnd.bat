rem flex -L -l lp_rlnd.l
flex -L lp_rlnd.l
rem sed -e "s/yy/lnd_yy/g" lex.yy.c >lp_rlnd.inc
sed -e "s/yy/lnd_yy/g" lex.yy.c | sed -e "s/^#line.*//g" >lp_rlnd.inc
del lex.yy.c

bison --no-lines -y lp_rlnd.y
sed -e "s/yy/lnd_yy/g" y.tab.c >lp_rlnd.c
del y.tab.c
