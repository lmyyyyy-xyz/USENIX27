# $Id$
/^\#diff-option:/ { print substr($0, index($0, "--")); }
{ next; }
