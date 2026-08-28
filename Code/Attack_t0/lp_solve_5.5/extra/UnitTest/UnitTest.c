#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "lp_lib.h"

#if defined FORTIFY
#include "lp_fortify.h"

int EndOfPgr(int i)
{
    exit(i);
}
#endif

void press_ret(void)
{
  printf("[return]");
  getchar();
}

#define tol 1e-6

#define ISEQUAL(value1, value2) (fabs(value1 - value2) < tol)

static REAL INF;

static void CheckRow(lprec *lp, int rowno, REAL *againstrow, int constr_type, REAL RHS, REAL range)
{
  int Ncolumns, i;
  REAL RHS1, *row, range1;
  int constr_type1;

  assert(lp != NULL);
  Ncolumns = get_Ncolumns(lp);
  row = (REAL *) malloc((1 + Ncolumns) * sizeof(*row));
  assert( row != NULL );
  get_row(lp, rowno, row);
  for (i = 1; i <= Ncolumns; i++)
    assert( ISEQUAL(row[i], againstrow[i-1]) );
  RHS1 = get_rh(lp, rowno);
  assert( ISEQUAL(RHS1, RHS) );
  if (rowno != 0) {
    constr_type1 = get_constr_type(lp, rowno);
    assert( constr_type1 == constr_type );
    range1 = get_rh_range(lp, rowno);
    assert( ISEQUAL(range1, range) );
  }
  free(row);
}

static void Init()
{
  lprec *lp;

  lp = make_lp(0, 0);
  assert(lp != NULL);
  INF = get_infinite(lp);
  delete_lp(lp);
}


void showmat(lprec *lp, MATrec *mat)
{
	int i, j, n;

	for (n = lp->columns, i = 0; i <= n; i++) {
		printf("col_end[%d] = %d\n", i, mat->col_end[i]);
	}
	for (n = mat->col_end[mat->columns], i = 0; i < n; i++) {
		printf("col_mat_rownr[%d] = %d, col_mat_colnr[%d] = %d, col_mat_value[%d] = %f\n", i, mat->col_mat_rownr[i], i, mat->col_mat_colnr[i], i, mat->col_mat_value[i]);
	}

    mat_validate(mat);
    printf("mat->row_end_valid = %d\n", mat->row_end_valid);
	for (n = lp->rows, i = 0; i <= n; i++) {
		printf("row_end[%d] = %d\n", i, mat->row_end[i]);
	}
	for (n = mat->row_end[mat->rows], i = 0; i < n; i++) {
		printf("row_mat[%d] = %d\n", i, mat->row_mat[i]);
	}
	for (n = mat->row_end[mat->rows], j = 0; j < n; j++) {
		i = mat->row_mat[j];
		printf("col_mat_rownr[%d] = %d, col_mat_colnr[%d] = %d, col_mat_value[%d] = %f\n", i, mat->col_mat_rownr[i], i, mat->col_mat_colnr[i], i, mat->col_mat_value[i]);
	}
    printf("\n");
}

void UnitTest33()
{
  lprec *lp;
  REAL a;
  int Norig_rows, i, ret;

  lp = read_LP("UnitTest33.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    set_verbose(lp, 2);

	write_LP(lp, stdout);

	showmat(lp, lp->matA);

	set_mat(lp, 2, 3, 8.0);

	write_LP(lp, stdout);

	showmat(lp, lp->matA);

    delete_lp(lp);
  }
}

/*
   04.10.07
   demonstrates a problem in del_constraint
   The problem is in del_constraint that psundo->orig_rows is not decremented
   Solved in del_constraint
*/
void UnitTest1()
{
  lprec *lp;
  REAL a;
  int Norig_rows, i, ret;

  lp = read_LP("UnitTest1.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    set_verbose(lp, 2);

#if 0
	min: -2 x3;

	/* Constraints */
	c1: +x2 -x1 <= 10;
	c: +x3 <= 5;
	c2: +x3 +x2 +x1 <= 20;

	/* Variable bounds */
	2 <= x3 <= 3;
	x1 <= 30;
#endif
    write_LP(lp, stdout);

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, -6.0) );

    del_constraint(lp, 2);

#if 0
	/* Objective function */
	min: -2 x3;

	/* Constraints */
	c1: +x2 -x1 <= 10;
	c2: +x3 +x2 +x1 <= 20;

	/* Variable bounds */
	2 <= x3 <= 3;
	x1 <= 30;
#endif
    write_LP(lp, stdout);

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, -6.0) );

#if 0
	Value of objective function: -6
#endif
    print_objective(lp);

#if 0
	Actual values of the variables:
	x3                              3
	x2                              0
	x1                              0
#endif
    print_solution(lp, 1);

    Norig_rows = get_Norig_rows(lp); /* should be 2 after del_constraint, was 3 */
    assert( Norig_rows == 2 );
    i = get_nameindex(lp, "x3", FALSE);
    a = get_var_primalresult(lp, Norig_rows + i);
    assert( ISEQUAL(a, 3.0) );      /* should be 3.0, was 0.0 */

    delete_lp(lp);
  }
}

/*
   14.06.09
   demonstrates a problem in del_constraint
   The problem is in varmap_delete()
   sometimes need locked if presolved unlocked if not

*/
void UnitTest1presolve()
{
  lprec *lp;
  REAL a;
  int Norig_rows, i, ret;

  lp = read_LP("UnitTest1presolve.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    set_verbose(lp, 6 /*2*/);

#if 0
        min: -2 x3;

        /* Constraints */
        c1: +x2 -x1 <= 10;
        c: +x3 <= 5;
        c2: +x3 +x2 +x1 <= 20;

        /* Variable bounds */
        2 <= x3 <= 3;
        x1 <= 30;
#endif
    write_LP(lp, stdout);
    set_presolve(lp,PRESOLVE_ROWS+PRESOLVE_COLS+PRESOLVE_LINDEP,get_presolveloops(lp) );
    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( fabs(a +464.0)< 1.0 );

    delete_lp(lp);
  }
}

/*
   14.06.09
   demonstrates a problem in del_constraint
   The problem is in varmap_delete()
   sometimes need locked if presolved unlocked if not

*/
void UnitTest2presolve()
{
  lprec *lp;
  REAL a;
  int Norig_rows, i, ret, index;

  lp = read_LP("UnitTest1presolve.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    write_LP(lp, stdout);
	Norig_rows = get_Norig_rows(lp);
	Norig_rows - lp->rows;
    set_presolve(lp,PRESOLVE_ROWS+PRESOLVE_COLS+PRESOLVE_LINDEP,get_presolveloops(lp) );
    Norig_rows = get_Norig_rows(lp); /* should be 27 after del_constraintlp->rows = 25 */
    Norig_rows - lp->rows;
    ret = solve(lp);
    set_verbose(lp, 6 /*2*/);
    Norig_rows = get_Norig_rows(lp); /* should be 27 lp->rows = 25 after presolve*/
    Norig_rows - lp->rows;
    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( fabs(a +464.0)< 1.0 );


    del_constraint(lp, 2);
    Norig_rows = get_Norig_rows(lp); /* should be 27 , lp->rows = 24 after del_constraint */
    assert( Norig_rows == 27 );
    /* assert( lp->rows == 24 ); */ /* This could change over time if presolve changes, so don't test it */
    write_LP(lp, stdout);  // check row 2 here should be "X21" not "XO5"
    lp->solutioncount;
    index = get_nameindex(lp, "X05", TRUE);  //
    assert( index == 3 );

    ret = solve(lp);
    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( fabs(a +464.0)< 1.0 );

    print_objective(lp);

//    print_solution(lp, 1);

    Norig_rows = get_Norig_rows(lp); /* should be 27 after del_constraint, was 24 */
    assert( Norig_rows == 27 );
    i = get_nameindex(lp, "X36", FALSE);
    a = get_var_primalresult(lp, Norig_rows + i);
    assert( fabs(a -339.0)< 1.0 );      /* should be 3.0, was 0.0 */

    index = get_orig_index(lp, 2);
    index = get_lp_index(lp, 3);   // 3 deleted by presolve
    index = get_nameindex(lp, "X05", TRUE);  //
    index = get_lp_index(lp, 13);  // 13 deleted by presolve
    index = get_lp_index(lp, 5);  // originally R12 now 3 in current active row set.
    index = get_nameindex(lp, "R12", TRUE);  // comes back 5  so need to take get_lp_index(
    index = get_lp_index(lp, index);  // 3 = R12 in last print
    del_constraint(lp, index);
    Norig_rows = get_Norig_rows(lp); /* should be 27 , lp->rows = 23 after del_constraint */
    assert( Norig_rows == 27 );
    /* assert( lp->rows == 23 ); */ /* This could change over time if presolve changes, so don't test it */
    write_LP(lp, stdout);
    lp->solutioncount;

	ret = solve(lp);

    delete_lp(lp);
  }
}

/*
   04.10.07
   demonstrates a problem in del_constraint
   The problem is in del_constraint that psundo->orig_rows is not decremented
   Solved in del_constraint
*/
void UnitTest2()
{
  lprec *lp;
  REAL a;
  int Norig_rows, i, ret;
  char *name;

  lp = read_LP("UnitTest2.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    set_verbose(lp, 2);

#if 0
	/* Objective function */
	min: -2 x3;

	/* Constraints */
	c1: +x2 -x1 <= 10;
	c: +x3 <= 5;
	c2: +x3 +x2 +x1 <= 20;

	/* Variable bounds */
	2 <= x3 <= 3;
	x1 <= 30;
#endif
    write_LP(lp, stdout);

    del_constraint(lp, 2);

#if 0
	/* Objective function */
	min: -2 x3;

	/* Constraints */
	c1: +x2 -x1 <= 10;
	c2: +x3 +x2 +x1 <= 20;

	/* Variable bounds */
	2 <= x3 <= 3;
	x1 <= 30;
#endif
    write_LP(lp, stdout);

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, -6.0) );

#if 0
	Value of objective function: -6
#endif
    print_objective(lp);

#if 0
	Actual values of the variables:
	x3                              3
	x2                              0
	x1                              0
#endif
    print_solution(lp, 1);

     Norig_rows = get_Norig_rows(lp); /* should be 2 after del_constraint, was 3 */
    assert( Norig_rows == 2 );
    i = get_nameindex(lp, "x3", FALSE);
    a = get_var_primalresult(lp, Norig_rows + i);
    assert( ISEQUAL(a, 3.0) );       /* should be 3.0, was 0.0 */

    name = get_origrow_name(lp, 2);
    assert( strcmp(name, "c2") == 0 ); /* should be 'c2', was 'c' */

    delete_lp(lp);
  }
}

/*
   26.10.07
   solve returned OPTIMAL instead of SUBOPTIMAL when a suboptimal solution was found when a break on first or value was done
*/
void UnitTest3()
{
  lprec *lp;
  int ret;
  REAL a;

  lp = read_LP("UnitTest3.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    set_verbose(lp, 2);

    set_break_at_first(lp, TRUE);

    ret = solve(lp);

    assert(ret == SUBOPTIMAL);

    a = get_objective(lp);
    //assert( ISEQUAL(a, 19263.0) );

    delete_lp(lp);
  }
}

/*
   In add_row mode, set_constr_type did a mat_multrow while it must be a mat_multcol then
   The constraint matrix was completely screwed up
*/
void UnitTest4()
{
  lprec *lp;

  lp = make_lp(0, 2);
  assert(lp != NULL);
  if (lp != NULL) {
    set_add_rowmode(lp, TRUE);
    str_set_obj_fn(lp, "3 4");
    str_add_constraint(lp, "1 2", LE, 2);
    str_add_column(lp, "5 6");
    str_add_constraint(lp, "2 1 8", LE, 2);
    set_constr_type(lp, 1, GE); /* screwed up the constraint matrix */
    set_add_rowmode(lp, FALSE);

#if 0
	/* Objective function */
	min: +3 C1 +4 C2 +5 C3;

	/* Constraints */
	+C1 +2 C2 +6 C3 >= 2;
	+2 C1 +C2 +8 C3 <= 2;
#endif
    write_LP(lp, stdout);

    { REAL a[] = {3.0, 4.0, 5.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {1.0, 2.0, 6.0}; CheckRow(lp, 1, a, GE, 2.0, INF); }
    { REAL a[] = {2.0, 1.0, 8.0}; CheckRow(lp, 2, a, LE, 2.0, INF); }

    delete_lp(lp);
  }
}

/* A crached occured in add_constraintex, add_columnex in these cases */
void UnitTest5()
{
  lprec *lp;

  lp = make_lp(0, 2);
  assert(lp != NULL);
  if (lp != NULL) {
    add_constraintex(lp, 0, NULL, NULL, LE, 0);
    add_columnex(lp, 0, NULL, NULL);

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	0 C1 <= 0;
#endif
    write_LP(lp, stdout);

    delete_lp(lp);
  }

  lp = make_lp(0, 2);
  assert(lp != NULL);
  if (lp != NULL) {
    add_constraintex(lp, 0, NULL, NULL, LE, 0);
    add_columnex(lp, 0, NULL, NULL);

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	0 C1 <= 0;
#endif
    write_LP(lp, stdout);

    delete_lp(lp);
  }
}

/*
   Reading this MPS file must fail:
     MPS_readfile: invalid data card; columns 23-24 must be blank
     Syntax error on line 13:  LO BND1      x1       -549755813888
*/
void UnitTest6()
{
    lprec *lp;

    lp = read_MPS("UnitTest6.mps", 4);
    assert(lp == NULL);
    if (lp != NULL)
      delete_lp(lp);
}

/*
   reading free MPS failed if a row/column name was completely made of numbers.
   Note that reading fixed format was ok.
*/
void UnitTest7()
{
  lprec *lp;
  char *name;
  int ret;
  REAL a;

  lp = read_freeMPS("UnitTest7.mps", 4);
  assert(lp != NULL);
  if (lp != NULL) {

#if 0
	NAME
	ROWS
	 N  R0
	 L  666
	 L  c2
	COLUMNS
	    x1        R0        -8.000000000   666       10.000000000
	    x1        c2        2.0000000000
	    x2        R0        -15.00000000   666       21.000000000
	    x2        c2        1.0000000000
	RHS
	    RHS       666       155.00000000   c2        22.000000000
	ENDATA
#endif
    write_MPS(lp, stdout);

#if 0
	/* Objective function */
	min: -8 x1 -15 x2;

	/* Constraints */
	666: +10 x1 +21 x2 <= 155;
	c2: +2 x1 +x2 <= 22;
#endif
    write_LP(lp, stdout);

    { REAL a[] = {-8.0, -15.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {10.0, 21.0}; CheckRow(lp, 1, a, LE, 155.0, INF); }
    { REAL a[] = {2.0, 1.0}; CheckRow(lp, 2, a, LE, 22.0, INF); }

    name = get_row_name(lp, 1);
    assert( strcmp(name, "666") == 0 ); /* should be '666' */

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, -118.9375) );

    delete_lp(lp);
  }
}

/*
   reading free MPS went wrong if a FR, MI, PL, BV bound was defined on a variable.
   Note that reading fixed format was ok.
*/
void UnitTest8()
{
  lprec *lp;
  REAL a;
  int ret;

  lp = read_freeMPS("UnitTest8.mps", 4);
  assert(lp != NULL);
  if (lp != NULL) {

#if 0
	NAME
	ROWS
	 N  R0
	 L  c1
	 L  c2
	COLUMNS
	    x1        R0        -8.000000000   c1        10.000000000
	    x1        c2        2.0000000000
	    x2        R0        -15.00000000   c1        21.000000000
	    x2        c2        1.0000000000
	RHS
	    RHS       c1        155.00000000   c2        22.000000000
	BOUNDS
	 FR BND       x1
	ENDATA
#endif
    write_MPS(lp, stdout);

#if 0
	/* Objective function */
	min: -8 x1 -15 x2;

	/* Constraints */
	c1: +10 x1 +21 x2 <= 155;
	c2: +2 x1 +x2 <= 22;

	/* Variable bounds */
	x1 >= -Inf;
#endif
    write_LP(lp, stdout);

    { REAL a[] = {-8.0, -15.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {10.0, 21.0}; CheckRow(lp, 1, a, LE, 155.0, INF); }
    { REAL a[] = {2.0, 1.0}; CheckRow(lp, 2, a, LE, 22.0, INF); }

    a = get_lowbo(lp, 1);
    assert( ISEQUAL(a, -get_infinite(lp)) );

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, -118.9375) );

    delete_lp(lp);
  }
}

/*
   Don't know anymore what the problem was here. Probably a messed up matrix after set_rowex
*/
void UnitTest9()
{
  lprec *lp;
  double row;
  int colno, ret;

  lp = make_lp(0, 10);
  assert(lp != NULL);
  {
    double drA_row[3];
    int diA_column[sizeof(drA_row)/sizeof(*drA_row)];

    drA_row[0] = -1;
    drA_row[1] = 1;
    drA_row[2] = 1;
    diA_column[0] = 2;
    diA_column[1] = 4;
    diA_column[2] = 6;

    ret = add_constraintex(lp, sizeof(diA_column)/sizeof(*diA_column), drA_row, diA_column, GE, 0);
  }

  {
    double drA_row[2];
    int diA_column[sizeof(drA_row)/sizeof(*drA_row)];

    drA_row[0] = -1;
    drA_row[1] = 1;
    diA_column[0] = 5;
    diA_column[1] = 7;

    ret = add_constraintex(lp, sizeof(diA_column)/sizeof(*diA_column), drA_row, diA_column, GE, 0);
  }

  {
    double drA_row[2];
    int diA_column[sizeof(drA_row)/sizeof(*drA_row)];

    drA_row[0] = 1;
    drA_row[1] = -1;
    diA_column[0] = 6;
    diA_column[1] = 8;

    ret = add_constraintex(lp, sizeof(diA_column)/sizeof(*diA_column), drA_row, diA_column, GE, 0);
  }

  {
    double drA_row[2];
    int diA_column[sizeof(drA_row)/sizeof(*drA_row)];

    drA_row[0] = -1;
    drA_row[1] = 1;
    diA_column[0] = 3;
    diA_column[1] = 9;

    ret = add_constraintex(lp, sizeof(diA_column)/sizeof(*diA_column), drA_row, diA_column, GE, 0);
  }

  {
    double drA_row[2];
    int diA_column[sizeof(drA_row)/sizeof(*drA_row)];

    drA_row[0] = 1;
    drA_row[1] = -1;
    diA_column[0] = 4;
    diA_column[1] = 10;

    ret = add_constraintex(lp, sizeof(diA_column)/sizeof(*diA_column), drA_row, diA_column, GE, 0);
  }

  add_constraintex(lp, 0, &row, &colno, LE, 0);
  add_constraintex(lp, 0, &row, &colno, LE, 0);

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	-C2 +C4 +C6 >= 0;
	-C5 +C7 >= 0;
	+C6 -C8 >= 0;
	-C3 +C9 >= 0;
	+C4 -C10 >= 0;
	0 C1 <= 0;
	0 C1 <= 0;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0}; CheckRow(lp, 2, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0}; CheckRow(lp, 3, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0}; CheckRow(lp, 4, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0}; CheckRow(lp, 5, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 6, a, LE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 7, a, LE, 0.0, INF); }

  {
    double drA_row[2];
    int diA_column[2];

    drA_row[0] = -1;
    drA_row[1] = 1;
    diA_column[0] = 1 /* get_nameindex(lp, "C1", FALSE) */;
    diA_column[1] = 3 /* get_nameindex(lp, "C3", FALSE)*/;

    ret = set_rowex(lp, 6, 2, drA_row, diA_column);
  }

  {
    double drA_row[2];
    int diA_column[2];

    drA_row[0] = -1;
    drA_row[1] = 1;
    diA_column[0] = 1 /* get_nameindex(lp, "C1", FALSE) */;
    diA_column[1] = 5 /* get_nameindex(lp, "C5", FALSE) */;

    ret = set_rowex(lp, 7, 2, drA_row, diA_column);
  }

  set_constr_type(lp, 6, GE);
  set_rh(lp, 6, 0);

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	-C2 +C4 +C6 >= 0;
	-C5 +C7 >= 0;
	+C6 -C8 >= 0;
	-C3 +C9 >= 0;
	+C4 -C10 >= 0;
	-C1 +C3 >= 0;
	-C1 +C5 <= 0;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0}; CheckRow(lp, 2, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0}; CheckRow(lp, 3, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0}; CheckRow(lp, 4, a, GE, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0}; CheckRow(lp, 5, a, GE, 0.0, INF); }
  { REAL a[] = {-1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 6, a, GE, 0.0, INF); }
  { REAL a[] = {-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 7, a, LE, 0.0, INF); }

  delete_lp(lp);
}

/* demonstrate problem with set_rowex - wrong values are put in the matrix and previous rows are even tampered */
void UnitTest10()
{
    lprec *lp;
    int ret, colno[] = {7, 8};
    double row[] = {-1, 1};

    lp = make_lp(0, 8);
    assert(lp != NULL);

    set_maxim(lp);

    str_set_obj_fn(lp, "1 1 1 1 1 1 1 1");

    str_add_constraint(lp, "0 0 -1 1 0 0 0 0", EQ, 0);
    str_add_constraint(lp, "0 -1 0 0 1 0 0 0", EQ, 0);
    str_add_constraint(lp, "-1 0 0 0 0 1 0 0", EQ, 0);
    str_add_constraint(lp, "0 0 0 0 0 -3 1 0", EQ, 0);
    str_add_constraint(lp, "0 0 0 0 -3 0 1 0", EQ, 0);
    str_add_constraint(lp, "0 0 0 -3 0 0 1 0", EQ, 0);

    ret = add_constraintex(lp, 0, row, colno, LE, 0); /* just add an empty row here */

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	-C2 +C4 +C6 >= 0;
	-C5 +C7 >= 0;
	+C6 -C8 >= 0;
	-C3 +C9 >= 0;
	+C4 -C10 >= 0;
	-C1 +C3 >= 0;
	-C1 +C5 <= 0;
	/* Objective function */
	max: +C1 +C2 +C3 +C4 +C5 +C6 +C7 +C8;

	/* Constraints */
	-C3 +C4 = 0;
	-C2 +C5 = 0;
	-C1 +C6 = 0;
	-3 C6 +C7 = 0;
	-3 C5 +C7 = 0;
	-3 C4 +C7 = 0;
	0 C1 <= 0;
#endif
    write_LP(lp, stdout);

    { REAL a[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {0.0, 0.0, -1.0, 1.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0}; CheckRow(lp, 2, a, EQ, 0.0, 0.0); }
    { REAL a[] = {-1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0}; CheckRow(lp, 3, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, -3.0, 1.0, 0.0}; CheckRow(lp, 4, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, 0.0, -3.0, 0.0, 1.0, 0.0}; CheckRow(lp, 5, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, -3.0, 0.0, 0.0, 1.0, 0.0}; CheckRow(lp, 6, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 7, a, LE, 0.0, INF); }

    set_rowex(lp, 7, 2, row, colno);

#if 0
	/* Objective function */
	max: +C1 +C2 +C3 +C4 +C5 +C6 +C7 +C8;

	/* Constraints */
	-C3 +C4 = 0;
	-C2 +C5 = 0;
	-C1 +C6 = 0;
	-3 C6 +C7 = 0;
	-3 C5 +C7 = 0;
	-3 C4 +C7 = 0;
	-C7 +C8 <= 0;
#endif
    write_LP(lp, stdout);

    { REAL a[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {0.0, 0.0, -1.0, 1.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0}; CheckRow(lp, 2, a, EQ, 0.0, 0.0); }
    { REAL a[] = {-1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0}; CheckRow(lp, 3, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, -3.0, 1.0, 0.0}; CheckRow(lp, 4, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, 0.0, -3.0, 0.0, 1.0, 0.0}; CheckRow(lp, 5, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, -3.0, 0.0, 0.0, 1.0, 0.0}; CheckRow(lp, 6, a, EQ, 0.0, 0.0); }
    { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0}; CheckRow(lp, 7, a, LE, 0.0, INF); }

    delete_lp(lp);
}

/*
   Test on add_constraint and add_column that failed at some time
   Both in rowmode off and on
*/
void UnitTest11()
{
  lprec *lp;
  int i;

  for (i = 1; i <= 2; i++) {
    lp = make_lp(0, 2);
    assert(lp != NULL);
    set_add_rowmode(lp, (i == 2));
    str_set_obj_fn(lp, "3 4");
    str_add_constraint(lp, "1 2", LE, 2);
    str_add_column(lp, "5 6");
    str_add_constraint(lp, "2 1 8", LE, 2);
    set_add_rowmode(lp, FALSE);

#if 0
	/* Objective function */
	min: +3 C1 +4 C2 +5 C3;

	/* Constraints */
	+C1 +2 C2 +6 C3 <= 2;
	+2 C1 +C2 +8 C3 <= 2;
#endif
    write_LP(lp, stdout);

    { REAL a[] = {3.0, 4.0, 5.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {1.0, 2.0, 6.0}; CheckRow(lp, 1, a, LE, 2.0, INF); }
    { REAL a[] = {2.0, 1.0, 8.0}; CheckRow(lp, 2, a, LE, 2.0, INF); }

    delete_lp(lp);
  }
}

void UnitTest12()
{
  lprec* lp;
  double row_val[][2] = { {4, 9999}, {1, 7} };
  int    row_ix [][2] = { {1, 9999}, {2, 3} };
  int res;

  lp = make_lp (2, 4);
  assert(lp != NULL);
  res = set_rowex (lp, 1, 1, row_val [0], row_ix [0]);

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	R1: +4 C1 <= 0;
	0 C1 <= 0;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {4.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 2, a, FR, 0.0, INF); }

  res = set_rowex (lp, 2, 2, row_val [1], row_ix [1]);

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	R1: +4 C1 <= 0;
	+C2 +7 C3 <= 0;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {4.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 1.0, 7.0, 0.0}; CheckRow(lp, 2, a, FR, 0.0, INF); }

  delete_lp(lp);
}

void UnitTest13()
{
  lprec *lp;

  lp = make_lp(0, 4);
  assert(lp != NULL);

  str_set_obj_fn(lp, "2 3 -2 3");

  str_add_constraint(lp, "3 2 2 1", LE, 4);
  str_add_constraint(lp, "0 4 3 1", GE, 3);

#if 0
	/* Objective function */
	min: +2 C1 +3 C2 -2 C3 +3 C4;

	/* Constraints */
	+3 C1 +2 C2 +2 C3 +C4 <= 4;
	+4 C2 +3 C3 +C4 >= 3;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {2.0, 3.0, -2.0, 3.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {3.0, 2.0, 2.0, 1.0}; CheckRow(lp, 1, a, LE, 4.0, INF); }
  { REAL a[] = {0.0, 4.0, 3.0, 1.0}; CheckRow(lp, 2, a, GE, 3.0, INF); }

  {
    REAL row[] = { 8, 7 };
    int colno[] = {2, 4};

    set_obj_fnex(lp, sizeof(colno) / sizeof(*colno), row, colno);
  }

  {
    REAL row[] = { 8, 7 };
    int colno[] = {2, 4};

    set_rowex(lp, 2, sizeof(colno) / sizeof(*colno), row, colno);
  }

#if 0
	/* Objective function */
	min: +8 C2 +7 C4;

	/* Constraints */
	+3 C1 +2 C2 +2 C3 +C4 <= 4;
	+8 C2 +7 C4 >= 3;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 8.0, 0.0, 7.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {3.0, 2.0, 2.0, 1.0}; CheckRow(lp, 1, a, LE, 4.0, INF); }
  { REAL a[] = {0.0, 8.0, 0.0, 7.0}; CheckRow(lp, 2, a, GE, 3.0, INF); }

  delete_lp(lp);
}

void UnitTest14()
{
  lprec *lp;

  lp = make_lp(9, 14);
  assert(lp != NULL);

  {
    int colno[] = {1, 2};
    REAL row[] = {1, 1};

    set_rowex(lp, 1, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {1, 3, 4};
    REAL row[] = {-1, 1, 1};

    set_rowex(lp, 2, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {5, 6, 7};
    REAL row[] = {1, 1, 1};

    set_rowex(lp, 3, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {6, 7, 14};
    REAL row[] = {1, 2, -1};

    set_rowex(lp, 4, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {2, 7, 8};
    REAL row[] = {1, 1, -1};

    set_rowex(lp, 5, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {8, 9};
    REAL row[] = {1, -1};

    set_rowex(lp, 6, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {4, 6, 10};
    REAL row[] = {1, 1, -1};

    set_rowex(lp, 7, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {5, 11, 12};
    REAL row[] = {-1, 1, 1};

    set_rowex(lp, 8, sizeof(row)/sizeof(*row), row, colno);
  }

  {
    int colno[] = {3, 11, 12, 13};
    REAL row[] = {1, 1, 1, -1};

    set_rowex(lp, 9, sizeof(row)/sizeof(*row), row, colno);
  }

#if 0
	/* Objective function */
	min: ;

	/* Constraints */
	+C1 +C2 <= 0;
	-C1 +C3 +C4 <= 0;
	+C5 +C6 +C7 <= 0;
	+C6 +2 C7 -C14 <= 0;
	+C2 +C7 -C8 <= 0;
	+C8 -C9 <= 0;
	+C4 +C6 -C10 <= 0;
	-C5 +C11 +C12 <= 0;
	+C3 +C11 +C12 -C13 <= 0;
#endif
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 0, a, 0, 0.0, INF); }
  { REAL a[] = {1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 1, a, FR, 0.0, INF); }
  { REAL a[] = {-1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 2, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 3, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0}; CheckRow(lp, 4, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 5, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 6, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0}; CheckRow(lp, 7, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0}; CheckRow(lp, 8, a, FR, 0.0, INF); }
  { REAL a[] = {0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, -1.0, 0.0}; CheckRow(lp, 9, a, FR, 0.0, INF); }

  delete_lp(lp);
}

/*
   Test some models against their known objective value
*/
void UnitTest15()
{
  lprec *lp;
  int i, ret, l;
  REAL objective;
  struct {
    char *name;
    REAL objective;
  } testcases[] =
  {
    {"demo_lag.lp", -1.0},
    {"ex1.lp", 3.0},
    {"ex2.lp", 118.9375},
    {"ex3.lp", 58.8},
    {"ex4.lp", 1779.48103506375},
    {"ex5.lp", 23313.8982433098},
    {"ex6.lp", 19979},
    {"ex7.lp", 0.468936321921965},
    {"ex1sos.lp", -9},
    {"ex1sc.lp", 1734.21864542409},
    {"ex2sc.lp", 1734.13591469417},
    {"ex2sos.lp", -30},
    {"ex3sos.lp", -25},
    {"ex4sos.lp", -90},
    {"ex1sc.mps", 1734.21864542409},
    {"ex2sc.mps", 1734.13591469417},
    {"ex1sos.mps", -9},
    {"ex2sos.mps", -30},
    {"ex3sos.mps", -25},
    {"ex4sos.mps", -90},
    {"ex5sos.mps", 91.71},
    {"ex6sos.mps", 122.445},
  };

  for (i = 0; i < sizeof(testcases) / sizeof(*testcases); i++) {
    l = (int) strlen(testcases[i].name);
    if (strcmp(testcases[i].name + l - 3, ".lp") == 0)
      lp = read_LP(testcases[i].name, 0, "");
    else if (strcmp(testcases[i].name + l - 4, ".mps") == 0)
      lp = read_MPS(testcases[i].name, 0);
    else
      lp = NULL;
    assert(lp != NULL);
    ret = solve(lp);
    assert( ret == OPTIMAL );
    objective = get_objective(lp);
    assert( ISEQUAL(objective, testcases[i].objective) );
    delete_lp(lp);
  }
}

void UnitTest16()
{
  lprec *lp;
  int ret;
  REAL a;

#if 0
	max: -1 + 0.200000 r3 + 0.3333333 r5 + 1.000000 r9 ;

	+ 3 r3 + 5 r5 + 9 r9 <= 17 ;
	int r3 ;
	int r5 ;
	int r9 ;
#endif

  lp = read_LP("UnitTest16.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    ret = solve(lp);

#if 0
	Value of objective function: 0.533333

	Actual values of the variables:
	r3                              1
	r5                              1
	r9                              1
#endif

    a = get_objective(lp);
    assert( ISEQUAL(a, 0.533333) );

    delete_lp(lp);
  }
}

/*
   Checks if all type of constraints are read correctly.
*/

void UnitTest17()
{
  lprec *lp;
  int ret;
  REAL a;

#if 0
	/* Objective function */
	min: +0.001 C1 +0.13 C2 +0.2 C3 +4.4 C4 +0.206 C5 +0.15 C6 +0.1 C7 +0.2004 C8 +0.0095 C9;

	/* Constraints */
	Row1: +42 C1 +14.9 C2 +34.8 C4 >= 1;
	Row2: 1 <= +42 C1 +14.9 C2 +34.8 C4;
	Row3: +3 >= +C1 +4.19999982 C4 +24.9066 C6 >= 1;
	Row4: 1 <= +C1 +4.19999982 C4 +24.9066 C6 <= 3;
	Row5: 2 >= +1.7 C2 +49.8132 C6;
	Row6: +1.7 C2 +49.8132 C6 <= 2;
	Row7: +99.6264010001 C6 <= 4;
	Row8: +30.64 C1 -10.431 C2 -41.0435 C3 -48.3900003 C4 -9.405 C5 -44.500763 C6 +12.804 C7 +52.75 C8 +4.807 C9 >= 0;
	Row9: +29.76 C1 -10.614 C2 -41.939 C3 -49.2600003 C4 -9.57 C5 -45.303763 C6 +12.576 C7 +51.9 C8 +4.598 C9 <= 0;
	Row10: +C9 <= 0.0361;
	Row11: +10.2 C1 -12.255 C2 -1.5675 C3 -1.95 C4 -12.525 C5 -2.955 C6 +65.62 C7 +12.75 C8 +67.235 C9 <= 0;
	Row12: +1.7 >= +C1 +C2 +C3 +C4 +C5 +C6 +C7 +C8 +C9 >= 0.9;

	/* Variable bounds */
	0.01 <= C3 <= 0.53;
	C4 <= 0.4;
	C5 >= 0.0314;
	C6 <= 0.011;
	C7 <= 0.08;
	C9 = 0;
#endif

  lp = read_LP("UnitTest17.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    ret = solve(lp);

#if 0
	Value of objective function: 0.149591

	Actual values of the variables:
	C1                       0.726027
	C2                       0.523008
	C3                       0.363779
	C4                              0
	C5                         0.0314
	C6                          0.011
	C7                              0
	C8                              0
	C9                              0
#endif

    a = get_objective(lp);
    assert( ISEQUAL(a, 0.149591) );

    { REAL a[] = {0.001, 0.13, 0.2, 4.4, 0.206, 0.15, 0.1, 0.2004, 0.0095}; CheckRow(lp, 0, a, 0, 0.0, INF); }
    { REAL a[] = {42, 14.9, 0, 34.8, 0, 0, 0, 0, 0}; CheckRow(lp, 1, a, GE, 1.0, INF); }
    { REAL a[] = {42, 14.9, 0, 34.8, 0, 0, 0, 0, 0}; CheckRow(lp, 2, a, GE, 1.0, INF); }
    { REAL a[] = {1, 0, 0, 4.2, 0, 24.9066, 0, 0, 0}; CheckRow(lp, 3, a, LE, 3.0, 2.0); }
    { REAL a[] = {1, 0, 0, 4.2, 0, 24.9066, 0, 0, 0}; CheckRow(lp, 4, a, GE, 1.0, 2.0); }
    { REAL a[] = {0, 1.7, 0, 0, 0, 49.8132, 0, 0, 0}; CheckRow(lp, 5, a, LE, 2.0, INF); }
    { REAL a[] = {0, 1.7, 0, 0, 0, 49.8132, 0, 0, 0}; CheckRow(lp, 6, a, LE, 2.0, INF); }
    { REAL a[] = {0, 0, 0, 0, 0, 99.626401, 0, 0, 0}; CheckRow(lp, 7, a, LE, 4.0, INF); }
    { REAL a[] = {30.64, -10.431, -41.0435, -48.39, -9.405, -44.500763, 12.804, 52.75, 4.807}; CheckRow(lp, 8, a, GE, 0.0, INF); }
    { REAL a[] = {29.76, -10.614, -41.939, -49.26, -9.57, -45.303763, 12.576, 51.9, 4.598}; CheckRow(lp, 9, a, LE, 0.0, INF); }
    { REAL a[] = {0, 0, 0, 0, 0, 0, 0, 0, 1}; CheckRow(lp, 10, a, LE, 0.0361, INF); }
    { REAL a[] = {10.2, -12.255, -1.5675, -1.95, -12.525, -2.955, 65.62, 12.75, 67.235}; CheckRow(lp, 11, a, LE, 0.0, INF); }
    { REAL a[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; CheckRow(lp, 12, a, LE, 1.7, 0.8); }

    delete_lp(lp);
  }
}

/*
   Screwed up the matrix when count was 0 and rowno[0]=0
*/
void UnitTest18()
{
  lprec *lp;

  lp = make_lp(2, 1);
  assert(lp != NULL);
  if (lp != NULL) {
    REAL column[2] = { 0.0, 0.0 };
    int rowno[2] = { 0, 0};

    set_columnex(lp, 1, 0, column, rowno);
    delete_lp(lp);
  }
}

void UnitTest19()
{
  lprec *lp;

  lp = make_lp(1, 2);
  assert(lp != NULL);
  if (lp != NULL) {
    REAL row[2] = { 0.0, 0.0 };
    int colno[2] = { 0, 0};

    //set_add_rowmode(lp, TRUE);
    set_rowex(lp, 1, 0, row, colno);
    //set_add_rowmode(lp, FALSE);
    delete_lp(lp);
  }
}

/*
   12.01.08
   solve returned SUBOPTIMAL instead of OPTIMAL if an integer solution is found with the same objective value as the relaxed solution then
   searching is stopped.
*/
void UnitTest20()
{
  lprec *lp;
  int ret;
  REAL a;

  lp = read_LP("UnitTest20.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    set_verbose(lp, 2);

    ret = solve(lp);

    assert(ret == OPTIMAL);

    a = get_objective(lp);
    assert( ISEQUAL(a, 0.0) );

    delete_lp(lp);
  }
}

/*
   07.03.09
   set_row screwed up matrix
*/
void UnitTest21()
{
  lprec *lp;

  lp = make_lp(0, 4);
  {
	  double row[] = {0,0,0,0,0};
	  set_obj_fn(lp, row);
  }
  {
	  double row[] = {0,1,1,1,1};
	  add_constraint(lp, row, GE, 1);
  }
  {
	  double row[] = {0,0,-1,1,0};
	  add_constraint(lp, row, GE, 1);
  }
  {
	  double row[] = {0,0,0,0,1};
	  add_constraint(lp, row, GE, 1);
  }
  write_LP(lp, stdout);
  {
	  double row[] = {0,0,0,0,1};
	  set_row(lp, 1, row);
  }
  write_LP(lp, stdout);

  { REAL a[] = {0.0, 0.0, 0.0, 1.0}; CheckRow(lp, 1, a, GE, 1.0, INF); }
  { REAL a[] = {0.0, -1.0, 1.0, 0.0}; CheckRow(lp, 2, a, GE, 1.0, INF); }
  { REAL a[] = {0.0, 0.0, 0.0, 1.0}; CheckRow(lp, 3, a, GE, 1.0, INF); }

  delete_lp(lp);
}

void UnitTest22()
{
	lprec *lp;
	char constrname[5], *ptr;
	int i, j, col;
	REAL constraint[4];
	REAL obj_fn[4];

	lp = make_lp(0,3);
	set_verbose(lp, DETAILED);
	obj_fn[1]=1;
	obj_fn[2]=1;
	obj_fn[3]=1;
	set_obj_fn(lp,obj_fn);
	for (i=0; i<5; i++) {
		for(j=0; j<3; j++){
			constraint[j+1]=ceil(rand()*5.0);
		}
		add_constraint(lp, constraint, GE, ceil(rand()*10.0));
		sprintf(constrname, "Col%d", i+1);
		set_row_name(lp, i+1, constrname);
	}
	write_LP(lp, stdout);
	del_constraint(lp,1);
//solve(lp);
	write_LP(lp, stdout);

	ptr = get_row_name(lp, 1);
	assert(strcmp(ptr, "Col2") == 0);

	ptr = get_row_name(lp, 2);
	assert(strcmp(ptr, "Col3") == 0);

	ptr = get_row_name(lp, 3);
	assert(strcmp(ptr, "Col4") == 0);
}

void UnitTest23()
{
	lprec *lp;
	char constrname[5], *ptr;
	int i, j, col;
	REAL constraint[4];
	REAL obj_fn[4];

	lp = make_lp(0,3);
	set_verbose(lp, DETAILED);
	set_col_name(lp, 1, "x");
	set_col_name(lp, 2, "y");
	set_col_name(lp, 3, "z");
	obj_fn[1]=1;
	obj_fn[2]=1;
	obj_fn[3]=1;
	set_obj_fn(lp,obj_fn);
	str_add_constraint(lp, "0 0 0", EQ, 0);
	str_add_constraint(lp, "0 0 0", EQ, 0);
	str_add_constraint(lp, "1 2 3", GE, 10);
	str_add_constraint(lp, "1 2 3", GE, 20);

	print_lp(lp);
	del_column(lp,2);
//solve(lp);
	print_lp(lp);

	ptr = get_col_name(lp, 1);
	assert(strcmp(ptr, "x") == 0);

	ptr = get_col_name(lp, 2);
	assert(strcmp(ptr, "z") == 0);

}

void UnitTest24()
{
	lprec *lp;
	double onerow[4];
	double a;
	int turnon;

	for (turnon = FALSE; turnon < 2; turnon++)
	{
		lp = make_lp(0, 3);
		set_minim(lp);
		set_add_rowmode(lp, turnon);
		str_set_obj_fn(lp, "0 0 0");
		str_add_constraint(lp, "0 -2 0", EQ, 0);
		str_add_constraint(lp, "0 3 0", LE, 1);
		str_add_constraint(lp, "0 0 4", GE, 1);
		write_LP(lp, stdout);
		{ double row[] = {-5, -6}; int colno[] = {2, 3}; set_rowex(lp, 1, 2, row, colno); }
		set_rh(lp, 1, 1);
		write_LP(lp, stdout);
		get_row(lp, 1, onerow);
		assert( ISEQUAL(onerow[3], -6) ); /* onerow[3] = 1 but it should be -1 */
		a = get_mat(lp, 1, 3);
		assert( ISEQUAL(a, -6) );
		delete_lp(lp);
	}
}

void UnitTest25()
{
	lprec *lp;
	double onerow[4];

	lp = make_lp(0, 3);
	set_minim(lp);
	str_set_obj_fn(lp, "0 0 0");
	str_add_constraint(lp, "1 -1 0", GE, 1);
	str_add_constraint(lp, "1 -1 0", GE, 1);
	str_add_constraint(lp, "0 0 1", EQ, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	//set_mat(lp, 2, 3, 3.14);
	write_LP(lp, stdout);
	showmat(lp, lp->matA);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	get_row(lp, 2, onerow);
	assert( ISEQUAL(onerow[3], 0.0) ); /* onerow[3] = -1 but it should be 0 */
}

void UnitTest26()
{
	lprec *lp;
	double onerow[4];

	lp = make_lp(0, 3);
	set_minim(lp);
	str_set_obj_fn(lp, "0 0 0");
	str_add_constraint(lp, "1 1 -1", LE, 1);
	str_add_constraint(lp, "0 0 1", GE, 1);
	str_add_constraint(lp, "1 0 1", GE, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	get_row(lp, 2, onerow);
	assert( ISEQUAL(onerow[3], 0) ); /* onerow[3] = 1 but it should be 0 */
}

void UnitTest27()
{
	lprec *lp;
	double onerow[4];

	lp = make_lp(0, 3);
	set_minim(lp);
	str_set_obj_fn(lp, "0 0 0");
	str_add_constraint(lp, "0 1 0", LE, 1);
	str_add_constraint(lp, "-1 0 -1", GE, 1);
	str_add_constraint(lp, "0 -1 -1", GE, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	get_row(lp, 2, onerow);
	assert( ISEQUAL(onerow[1], 0) ); /* onerow[1] = -1 but it should be 0 */
}

void UnitTest28()
{
	lprec *lp;
	double onerow[4];

	lp = make_lp(0, 3);
	set_minim(lp);
	str_set_obj_fn(lp, "1 2 3");
	str_add_constraint(lp, "-1 0 -1", LE, 1);
	str_add_constraint(lp, "0 0 1", LE, 1);
	str_add_constraint(lp, "-1 0 -1", GE, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	showmat(lp, lp->matA);
	//set_mat(lp, 3, 2, 3.14);
	//write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	//{ int colno[] = {1, 2, 3}; double row[] = {-1, -1, -1}; set_rowex(lp, 1, 3, row, colno); }
	showmat(lp, lp->matA);
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	get_row(lp, 1, onerow);
	assert( ISEQUAL(onerow[1], -1) ); /* onerow[1] = 0 but it should be -1 */
}

void UnitTest29()
{
	lprec *lp;
	double onerow[4];

	lp = make_lp(0, 3);
	set_minim(lp);
	str_set_obj_fn(lp, "0 0 0");
	str_add_constraint(lp, "1 0 1", GE, 1);
	str_add_constraint(lp, "0 0 -1", GE, 1);
	str_add_constraint(lp, "1 0 1", LE, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, LE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, LE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, EQ);
	set_rh(lp, 3, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, EQ);
	set_rh(lp, 1, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 1, 1, -1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, -1, 0, 1}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 1, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, GE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }
	set_constr_type(lp, 3, LE);
	set_rh(lp, 3, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, -1}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, -1, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, GE);
	set_rh(lp, 2, 1);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 2, row); }
	set_constr_type(lp, 2, EQ);
	set_rh(lp, 2, 0);
	write_LP(lp, stdout);
	{ double row[] = {0, 0, 0, 0}; set_row(lp, 3, row); }

}

void UnitTest30()
{
	lprec *lp;
	double onerow[4];

	lp = make_lp(0, 3);
	set_minim(lp);
	str_set_obj_fn(lp, "0 0 0");
	str_add_constraint(lp, "1 1 1", GE, 1);
	str_add_constraint(lp, "0 1 0", LE, 1);
	str_add_constraint(lp, "1 0 -1", EQ, 0);
	write_LP(lp, stdout);
	showmat(lp, lp->matA);
	{ double row[] = {-1}; int colno[] = {1}; set_rowex(lp, 1, 1, row, colno); }
	//{ double row[] = {0, -1, 0, 0}; set_row(lp, 1, row); }
	set_constr_type(lp, 1, GE);
	set_rh(lp, 1, 1);
	write_LP(lp, stdout);
	get_row(lp, 1, onerow);
	assert( ISEQUAL(onerow[1], -1) ); /* onerow[1] = 0 but it should be -1 */

}

void UnitTest31()
{
	lprec *lp;
	double onecol[4];

	lp = make_lp(3, 0);
	set_minim(lp);
	str_add_column(lp, "0 -1 1 0");
	str_add_column(lp, "0 -1 0 -1");
	str_add_column(lp, "0 1 0 1");
	write_LP(lp, stdout);
	{ double col[] = {-1}; int rowno[] = {1}; set_columnex(lp, 1, 1, col, rowno); }
	write_LP(lp, stdout);
	get_column(lp, 1, onecol);
	assert( ISEQUAL(onecol[2], 0) ); /* onecol[2] = 1 but it should be 0 */

}

void UnitTest32()
{
	lprec *lp;
	double onerow[5];
	double onecol[4];
	double a;

	lp = make_lp(0, 4);
	set_add_rowmode(lp, TRUE);
	set_minim(lp);
	str_set_obj_fn(lp, "7 8 9 10");
	str_add_constraint(lp, "0 -2 0 11", EQ, 21);
	str_add_constraint(lp, "0 3 0 12", LE, 22);
	str_add_constraint(lp, "0 0 4 13", GE, 23);
	write_MPS(lp, stdout);
	write_LP(lp, stdout);
	showmat(lp, lp->matA);
	{ double row[] = {-5, -6}; int colno[] = {2, 3}; set_rowex(lp, 1, 2, row, colno); }
	//set_constr_type(lp, 1, LE);
	//set_rh(lp, 1, 1);
	//set_add_rowmode(lp, FALSE);
	write_LP(lp, stdout);
	showmat(lp, lp->matA);
	get_row(lp, 0, onerow);
	assert( ISEQUAL(onerow[3], 9) ); /* onerow[3] = 1 but it should be -1 */
	printf("get_mat(lp, %d, %d) = %f\n", 0, 3, get_mat(lp, 0, 3));

	a = get_rh(lp, 1);
}

void UnitTest34()
{
	lprec *lp;
	char constrname[7], *ptr;
	int i, j, col;
	REAL constraint[4];
	REAL obj_fn[4];

	lp = make_lp(0,3);
	set_add_rowmode(lp, TRUE);
	set_verbose(lp, DETAILED);
	obj_fn[1]=1;
	obj_fn[2]=1;
	obj_fn[3]=1;
	set_obj_fn(lp,obj_fn);
	for (i=0; i<5; i++) {
		for(j=0; j<3; j++){
			constraint[j+1]=ceil(rand()*5.0);
		}
		add_constraint(lp, constraint, GE, ceil(rand()*10.0));
		sprintf(constrname, "Col%d", i+1);
		set_row_name(lp, i+1, constrname);
	}
	write_LP(lp, stdout);

    del_constraint(lp,1);

    add_constraint(lp, constraint, GE, ceil(rand()*10.0));

	write_LP(lp, stdout);

	sprintf(constrname, "Col%d'", 5);

	set_row_name(lp, 5, constrname);

    write_LP(lp, stdout);

    ptr = get_row_name(lp, 5);
	assert(strcmp(ptr, constrname) == 0);
}

void UnitTest35()
{
	lprec *lp;
	char constrname[7], *ptr;
	int i, j, col;
	REAL constraint[4];
	REAL obj_fn[4];

	lp = make_lp(0,3);
	//set_add_rowmode(lp, TRUE);
	set_verbose(lp, DETAILED);
	obj_fn[1]=1;
	obj_fn[2]=1;
	obj_fn[3]=1;
	set_obj_fn(lp,obj_fn);
	for (i=0; i<3; i++) {
		for(j=0; j<3; j++){
			constraint[j+1]=ceil(rand()*5.0);
		}
		add_constraint(lp, constraint, GE, ceil(rand()*10.0));
		sprintf(constrname, "Col%d", i+1);
		set_row_name(lp, i+1, constrname);
		set_col_name(lp, i+1, constrname);
	}
	write_LP(lp, stdout);

    del_column(lp,1);

	write_LP(lp, stdout);

	constraint[0] = 1;
    add_column(lp, constraint);

	write_LP(lp, stdout);

	sprintf(constrname, "Col%d'", 3);

    set_col_name(lp, 3, constrname);

    write_LP(lp, stdout);

	ptr = get_col_name(lp, 3);
	assert(strcmp(ptr, constrname) == 0);
}

void UnitTest36()
{
  lprec *lp;
  int i, j;
  REAL a;

  for (j = 0; j <= 1; j++)
   for (i = 0; i <= 1; i++) {
    lp = make_lp(0, 2);
    assert(lp != NULL);
	set_sense(lp, j);
    set_add_rowmode(lp, i);
    str_set_obj_fn(lp, "3 4");
    str_add_constraint(lp, "1 2", LE, 3);
	str_add_constraint(lp, "3 4", GE, 5);
    str_add_column(lp, "5 6 8");
    set_add_rowmode(lp, FALSE);

	write_LP(lp, stdout);

	a = get_mat(lp, 0, 2);
	assert( ISEQUAL(a, 4) );

	a = get_mat(lp, 0, 3);
	assert( ISEQUAL(a, 5) );

	a = get_mat(lp, 1, 2);
	assert( ISEQUAL(a, 2) );

	a = get_mat(lp, 2, 2);
	assert( ISEQUAL(a, 4) );

	a = get_mat(lp, 1, 3);
	assert( ISEQUAL(a, 6) );

	a = get_mat(lp, 2, 3);
	assert( ISEQUAL(a, 8) );

	delete_lp(lp);
  }
}

void UnitTest37()
{
    // Define the LP problem (constraint matrix A has 4 rows and 101 columns)
double obj[101] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,0,0,0,0};
double b[4] = {0,3,0,0};
double A[4*101] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,-1,1,0,0,0,0};

// Create problem
lprec *lp = make_lp(4, 101);

// Set presolve settings
set_presolve(lp, PRESOLVE_ROWS | PRESOLVE_IMPLIEDSLK, get_presolveloops(lp));

// Set objective
for (int j = 0; j < 101; j++){
set_obj(lp, j+1, obj[j]);
}

// Set constraint types and RHS
for (int i = 0; i < 4; i++){
set_constr_type(lp, i+1, EQ);
set_rh(lp, i+1, b[i]);
}

// Set constraint matrix
for (int i = 0; i < 4; i++){
for (int j = 0; j < 101; j++){
set_mat(lp, i + 1, j + 1, A[101*i + j]);
}
}

printf("NRows = %d, NCols = %d\n", get_Nrows(lp), get_Ncolumns(lp));
write_LP(lp, stdout);

showmat(lp, lp->matA);

// Solve the problem
int status = solve(lp);

printf("NRows = %d, NCols = %d\n", get_Nrows(lp), get_Ncolumns(lp));
write_LP(lp, stdout);
print_objective(lp);
print_solution(lp, 1);

// Get the solution value of a variable, which turns out to be negative
double solutionVariable = get_var_primalresult(lp, 4 + 1 + 70);
printf("\nValue of a solution variable: %f", solutionVariable);

}

void UnitTest38()
{
lprec *lp;
double row[] = {0, 1, 1, 1};

lp = make_lp(1, 3);
showmat(lp, lp->matA);
set_row(lp, 1, row);
showmat(lp, lp->matA);
solve(lp);
write_LP(lp, stdout);

set_row(lp, 1, row);
showmat(lp, lp->matA);
solve(lp);
write_LP(lp, stdout);

delete_lp(lp);
}

void UnitTest39()
{
lprec *lp;
double rowIn1[] = { 0, 1, 2 };
double rowIn2[] = { 0, 3, 4 };
double rowOut[3];

lp = make_lp(2, 2);
showmat(lp, lp->matA);
set_row(lp, 1, rowIn1);
showmat(lp, lp->matA);
set_row(lp, 2, rowIn2);
showmat(lp, lp->matA);
get_row(lp, 1, rowOut);

printf("%f, %f\n", rowOut[2], rowIn1[2]);

delete_lp(lp);
}

/* v5.5 gave a suboptimal integer solution because MIP_stepOF gave a wrong value */
void UnitTest40()
{
	lprec *lp;
	int ret;
	REAL obj_fn[5], a;

	lp = make_lp(0,4);
	set_verbose(lp, DETAILED);
	set_col_name(lp, 1, "r1");
	set_col_name(lp, 2, "r2");
	set_col_name(lp, 3, "b1");
	set_col_name(lp, 4, "b2");
	obj_fn[1]=1;
	obj_fn[2]=1;
	obj_fn[3]=0;
	obj_fn[4]=0;
	set_obj_fn(lp,obj_fn);
	str_add_constraint(lp, "1 1 0 0", GE, 1);
	str_add_constraint(lp, "1 0 -5.345 0", EQ, 0);
	str_add_constraint(lp, "0 1 0 -4.456", EQ, 0);

    set_binary(lp, 3, 1);
    set_binary(lp, 4, 1);

	//print_lp(lp);
    write_LP(lp, stdout);

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, 4.456) );
}

/* gave a suboptimal integer solution because MIP_stepOF gave a wrong value */
void UnitTest41()
{
	lprec *lp;
	int ret;
	REAL obj_fn[3], a;

	lp = make_lp(0,2);
    set_maxim(lp);
	set_verbose(lp, DETAILED);
	set_col_name(lp, 1, "x");
	set_col_name(lp, 2, "y");
	obj_fn[1]=143;
	obj_fn[2]=60;
	set_obj_fn(lp,obj_fn);
	str_add_constraint(lp, "120 210", LE, 15000);
	str_add_constraint(lp, "110 30", LE, 4000);
	str_add_constraint(lp, "1 1", LE, 75);

    set_int(lp, 1, 1);
    set_int(lp, 2, 1);

	//print_lp(lp);
    write_LP(lp, stdout);

    ret = solve(lp);

    assert( ret == OPTIMAL );
    a = get_objective(lp);
    assert( ISEQUAL(a, 6266.0) );
}

/* Solve returned numerical instability because of the bounds on C6 where the upper bound is not equal to the lower bound, but very very close to it */
void UnitTest42()
{
  lprec *lp;
  int ret;

  lp = read_LP("UnitTest42.lp", 4, "");
  assert(lp != NULL);
  if (lp != NULL) {
    ret = solve(lp);
    assert( ret == OPTIMAL );
    delete_lp(lp);
  }
}


/* Solve (B&B) was in a loop */
void UnitTest43()
{
  lprec *lp;
  int ret;

  lp = read_LP("UnitTest43.lp", 4, "");
  set_timeout(lp, 2000);
  assert(lp != NULL);
  if (lp != NULL) {
    ret = solve(lp);
    assert( ret == INFEASIBLE );
    delete_lp(lp);
  }
}


/* gave no solution or crached */
void UnitTest44()
{
	lprec* lp;
	int ret;
	REAL a;

	lp = read_LP("UnitTest44.lp", 4, "");
	assert(lp != NULL);
	if (lp != NULL) {
		ret = solve(lp);
		assert(ret == OPTIMAL);
		a = get_objective(lp);
		assert(ISEQUAL(a, 4208.7486374784003));
		delete_lp(lp);
	}
}

/* When for a variable which is on its upper bound its bound was removed, solve failed or gave wrong solution */
void UnitTest45()
{
	lprec* lp;
	int columnNr = 0;
	int rowNr = 0;
	int  ret;
	REAL a;

	lp = make_lp(0, 0);
	assert(lp != NULL);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "x_1233_350");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "x_1233_351");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "x_1233_142");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "x_1233_132");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "x_1233_101");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "RC_1233_x_2446_331");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "RC_1233_x_2446_138");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	{
		double row[] = { 0,0,0,0,0,0,0.8,-0.2, };
		add_constraint(lp, row, EQ, 0);
		set_row_name(lp, ++rowNr, "RC_1233_RC2446IngAmountRecipe331");
	}

	{
		double row[] = { 0,0,0,0,0,0,-0.8,+0.2, };
		add_constraint(lp, row, EQ, 0);
		set_row_name(lp, ++rowNr, "RC_1233_RC2446IngAmountRecipe138");
	}

	{
		double row[] = { 0,0,-1,0,0,0,0,0, };
		add_constraint(lp, row, LE, 0);
		set_row_name(lp, ++rowNr, "RC1233IngAmountExternalSum350Max");
	}

	{
		double row[] = { 0,0,0,0,0,0,1,1, };
		add_constraint(lp, row, LE, 0.108061);
		set_row_name(lp, ++rowNr, "RC1233RCAmount2446");
	}

	{
		double row[] = { 0,-0.1,0.9,0,0,0,0,0, };
		add_constraint(lp, row, LE, 0.0);
		set_row_name(lp, ++rowNr, "RC1233IngAmountExternalSum351Max");
	}

	{
		double row[] = { 0,-0.0162,-0.0162,1,0,0,0,0, };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "RC1233IngAmountExternalSum142");
	}

	{
		double row[] = { 0,-0.0132,-0.0132,0,1,0,0,0, };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "RC1233IngAmountExternalSum132");
	}

	{
		double row[] = { 0,-0.00236,-0.00236,0,0,1,0,0, };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "RC1233IngAmountExternalSum101");
	}

	{
		double row[] = { 0,1,1,0,0,0,0,0, };
		add_constraint(lp, row, GE, 0.0);
		set_row_name(lp, ++rowNr, "RC1233ExternalSumAbsolute1");
	}

	{
		double row[] = { 0,1,1,1,1,1,1,1, };
		add_constraint(lp, row, EQ, 1.0);
		set_row_name(lp, ++rowNr, "RC1233Total");
	}

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_350");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_351");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_142");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_132");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_101");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_137");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_p_2452");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_x_139");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	{
		double row[] = { 0,200,0,0,0,0,0,0, -1,0,0,0,0,0,0,0 };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_350");
	}

	{
		double row[] = { 0,0,200,0,0,0,0,0, 0,-1,0,0,0,0,0,0 };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_351");
	}

	{
		double row[] = { 0,0,0,200,0,0,0,0, 0,0,-1,0,0,0,0,0 };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_142");
	}

	{
		double row[] = { 0,0,0,0,200,0,0,0, 0,0,0,-1,0,0,0,0 };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_132");
	}

	{
		double row[] = { 0,0,0,0,0,200,0,0, 0,0,0,0,-1,0,0,0 };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_101");
	}

	{
		double row[] = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,-1,0,0 };
		add_constraint(lp, row, EQ, -160.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_137");
	}

	{
		double row[] = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,-1,0 };
		add_constraint(lp, row, EQ, -40.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_p_2452");
	}

	{
		double row[] = { 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,-1 };
		add_constraint(lp, row, EQ, -40.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_x_139");
	}

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Objective");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);

	{
		double row[] = { 0,0,0,0,0,0,53.8,0.002, 1.03,0.2,0.919,2.82273,0.78237,1.711,1,1.65,-1, };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Objective");
	}

	{
		double row[] = { 0,0,0,0,0,0,53.8,0.002, 1.03,0.2,0.919,2.82273,0.78237,1.711,1,1.65,0, };
		set_obj_fn(lp, row);
	}

	ret = solve(lp);

	assert(ret == OPTIMAL);

	add_columnex(lp, 0, NULL, NULL);
	set_col_name(lp, ++columnNr, "Usage_Site_25_p_2446");
	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, 21.5);

	{
		double row[] = { 0,0,0,0,0,0,200,200, 0,0,0,0,0,0,0,0,0,-1, };
		add_constraint(lp, row, EQ, 0.0);
		set_row_name(lp, ++rowNr, "Usage_Site_25_p_2446");
	}

	ret = solve(lp);

	assert(ret == OPTIMAL);

	set_lowbo(lp, columnNr, 0.0);
	set_upbo(lp, columnNr, INF);
	//set_bounds(lp, columnNr, 0.0, INF);

	ret = solve(lp);

	assert(ret == OPTIMAL);

	write_LP(lp, stdout);

	a = get_objective(lp);
	assert(ISEQUAL(a, 553.99141197110293));
}

/* When for a variable which is on its upper bound its bound was removed, solve failed or gave wrong solution */
void UnitTest46()
{
	lprec* lp;
	int ret;
	REAL a;

	lp = read_LP("UnitTest46.lp", 4, "");
	assert(lp != NULL);
	if (lp != NULL) {
		set_verbose(lp, 4);

		ret = solve(lp);

		assert(ret == OPTIMAL);

		print_solution(lp, 1);

		set_upbo(lp, 2, 3.5);

		ret = solve(lp);

		assert(ret == OPTIMAL);

		//set_upbo(lp, 2, INF);
		set_bounds(lp, 2, 0.0, INF);

		ret = solve(lp);

		assert(ret == OPTIMAL);

		a = get_objective(lp);
		assert(ISEQUAL(a, 12.4));

		//print_solution(lp, 1);

		delete_lp(lp);
	}
}

extern void UnitTest47();

int main(void)
{
  Init();

  printf("UnitTest1\n"); UnitTest1();
  printf("UnitTest1presolve\n"); UnitTest1presolve();
  printf("UnitTest2presolve\n"); UnitTest2presolve();
  printf("UnitTest2\n"); UnitTest2();
  printf("UnitTest3\n"); UnitTest3();
  printf("UnitTest4\n"); UnitTest4();
  printf("UnitTest5\n"); UnitTest5();
  printf("UnitTest6\n"); UnitTest6();
  printf("UnitTest7\n"); UnitTest7();
  printf("UnitTest8\n"); UnitTest8();
  printf("UnitTest9\n"); UnitTest9();
  printf("UnitTest10\n"); UnitTest10();
  printf("UnitTest11\n"); UnitTest11();
  printf("UnitTest12\n"); UnitTest12();
  printf("UnitTest13\n"); UnitTest13();
  printf("UnitTest14\n"); UnitTest14();
  printf("UnitTest15\n"); UnitTest15();
  printf("UnitTest16\n"); UnitTest16();
  printf("UnitTest17\n"); UnitTest17();
  printf("UnitTest18\n"); UnitTest18();
  printf("UnitTest19\n"); UnitTest19();
  printf("UnitTest20\n"); UnitTest20();
  printf("UnitTest21\n"); UnitTest21();
  printf("UnitTest22\n"); UnitTest22();
  printf("UnitTest23\n"); UnitTest23();
  printf("UnitTest24\n"); UnitTest24();
  printf("UnitTest25\n"); UnitTest25();
  printf("UnitTest26\n"); UnitTest26();
  printf("UnitTest27\n"); UnitTest27();
  printf("UnitTest28\n"); UnitTest28();
  printf("UnitTest29\n"); UnitTest29();
  printf("UnitTest30\n"); UnitTest30();
  printf("UnitTest31\n"); UnitTest31();
  printf("UnitTest32\n"); UnitTest32();
  printf("UnitTest33\n"); UnitTest33();
  printf("UnitTest34\n"); UnitTest34();
  printf("UnitTest35\n"); UnitTest35();
  printf("UnitTest36\n"); UnitTest36();
  printf("UnitTest37\n"); UnitTest37();
  printf("UnitTest38\n"); UnitTest38();
  printf("UnitTest39\n"); UnitTest39();
  printf("UnitTest40\n"); UnitTest40();
  printf("UnitTest41\n"); UnitTest41();
  printf("UnitTest42\n"); UnitTest42();
  printf("UnitTest43\n"); UnitTest43();
  printf("UnitTest44\n"); UnitTest44();
  printf("UnitTest45\n"); UnitTest45();
  printf("UnitTest46\n"); UnitTest46();
  printf("UnitTest47\n"); UnitTest47();

  printf("Done\n");
}
