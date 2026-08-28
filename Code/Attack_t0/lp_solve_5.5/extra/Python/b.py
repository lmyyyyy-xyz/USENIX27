r"""
This file contains a routine for computing the domination number of a graph and, optionally, for returning a dominating set of minimum size.  A dominating set in a graph $G$ is a set of vertices such that every vertex of $G$ is either in the set or adjacent to a vertex in the set.  The domination number $\gamma(G)$ is the minimum size of a dominating set.

AUTHORS:
    Stephen G. Hartke -- (2008-09-24) initial version

NOTES:
    We assume that G is a graph on vertices {0,1,...,n-1}.
    This routine requires the package lp_solve version 5.5.
"""

#*****************************************************************************
#      Copyright (C) 2008 Stephen G. Hartke <lastname at gmail.com>
#
# Distributed  under  the  terms  of  the  GNU  General  Public  License (GPL)
#                         http://www.gnu.org/licenses/
#*****************************************************************************

# lp_solve, for solving integer program
import lpsolve55
