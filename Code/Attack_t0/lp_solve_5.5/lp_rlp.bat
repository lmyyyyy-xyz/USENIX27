rem Download win_flex and win_bison from https://github.com/lexxmark/winflexbison/

rem flex -L -l lp_rlp.l
win_flex -L lp_rlp.l
rem sed -e "s/^#line.*//g" lex.yy.c >lp_rlp.h
sed -e "s/yy/lp_yy/g" lex.yy.c | sed -e "s/^#line.*//g" >lp_rlp.h
rem copy lex.yy.c lp_rlp.h
del lex.yy.c

rem bison --no-lines -y lp_rlp.y
win_bison --no-lines lp_rlp.y -o y.tab.c
sed -e "s/yy/lp_yy/g" y.tab.c >lp_rlp.c
rem copy y.tab.c lp_rlp.c
del y.tab.c
