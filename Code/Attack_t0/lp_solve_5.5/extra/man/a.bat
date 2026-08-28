@echo off
echo static struct _values %1[] =
echo {
replreg "&nbsp;" " " get_%1.htm | replreg -l ".*<[tT][dD]> *([^<>() ]*) *\(([0-9]+)\) *</[tT][dD]>.*" "  { \1, """\1""" },"
echo };
echo.
echo   { "%1", setintfunction(get_%1), setvalues(%1) },
