rem Download win_flex and win_bison from https://github.com/lexxmark/winflexbison/

rem flex -L -l lp_rlpt.l
win_flex -L lp_rlpt.l
rem sed -e "s/yy/lpt_yy/g" lex.yy.c >lp_rlpt.inc
sed -e "s/yy/lpt_yy/g" lex.yy.c | sed -e "s/^#line.*//g" >lp_rlpt.inc
del lex.yy.c

rem bison --no-lines -y lp_rlpt.y
win_bison --no-lines lp_rlpt.y -o y.tab.c
sed -e "s/yy/lpt_yy/g" y.tab.c >lp_rlpt.c
del y.tab.c
