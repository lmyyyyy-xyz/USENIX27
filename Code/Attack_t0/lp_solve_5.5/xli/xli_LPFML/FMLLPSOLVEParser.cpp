/*
 * Copyright (c) 2003 Robert Fourer and Leonardo Lope of
 * Northwestern University and Kipp Martin of The University of Chicago.
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (with the exception given in Condition 7)
 * provided that the following conditions are met:

 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the DISCLAIMER below.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the DISCLAIMER below in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the names of Northwestern or the University of Chicago
 * nor the names of its contributors (Robert Fourer, Leo Lopes, and
 * Kipp Martin) may be used to endorse or promote
 * products derived from this software.
 *
 * 4. This software includes software developed by the
 * Apache Software Foundation (http://www.apache.org/)
 * Copyright (c) 1999-2000 The Apache Software Foundation.
 * All rights reserved.
 *
 * 5. The names "Xerces" and "Apache Software Foundation" must
 * not be used to endorse or promote products derived from this
 * software without prior written permission. For written
 * permission, please contact apache\@apache.org.
 *
 * 6. Products derived from this software may not be called "Apache",
 * nor may "Apache" appear in their name, without prior written
 * permission of the Apache Software Foundation.
 *
 ====================================================================
 *
 * DISCLAIMER:
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL NORTHWESTERN UNIVERSITY, THE
 * UNIVERSITY OF CHICAGO, THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 ====================================================================
 *
 */
/*
* $Id: FMLLPSOLVEParser.cpp,v 1.1 2004/07/16 18:41:57 leo Exp $
*/
#include "FMLLPSOLVEParser.hpp"
#include "FMLParser.hpp"
#include "FMLLPToXML.hpp"
#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <stdlib.h>
//
#include "commonlib.h"


using namespace std;
FMLLPSOLVEParser::FMLLPSOLVEParser(lprec *lp)              // 0.
{
  nVars_ = nRows_ = -1;
  if(lp == 0) {
    isNativelp_ = true;
//    lp_ = make_lp(0,0);
  }
  else {
    isNativelp_ = false;
    lp_ = lp;
  }
#ifdef DEBUG
   cout << "Inside FMLLPSOLVEParser constructor" << endl;
#endif
}
void writeXMLModel();

void FMLLPSOLVEParser::onVariableCount(const int count)                           // 4.
{
   nVars_ = count;
#ifdef DEBUG
   cout << "number of variables = " << nVars_ << endl;
#endif
}
void FMLLPSOLVEParser::onConstraintCount(const int count)                         // 3.
{
   nRows_ = count;
#ifdef DEBUG
   cout << "number of Rows = " << nRows_ << endl;
#endif

}
void FMLLPSOLVEParser::onObjectiveConstant(const double objConstant)
{
   objConstant_ = objConstant;
}
void FMLLPSOLVEParser::onObjectiveSense(const bool isMin)                         // 2.
{
   lp_->set_sense(lp_, (MYBOOL) (isMin == false));
   objConstant_ = 0.0;
   if(isMin)
     nDir_ = 1;
   else
     nDir_ = -1;
}
void FMLLPSOLVEParser::onSource(const string &source)                             // 1.
{
   lpsource_ = source;
}
int FMLLPSOLVEParser::onConstraints(vector<std::string> const &label,             // 5.
         vector<double> const &lhs, vector<double> const &rhs )
{
  double SOLVER_FEASTOL = 1.0e-7;
  int i, i1;

  lhs_ = new double[ nRows_];
  rhs_ = new double[ nRows_];
  copy(lhs.begin(), lhs.end(), lhs_);
  copy(rhs.begin(), rhs.end(), rhs_);

  for(i = 0, i1 = 1; i < nRows_; i++, i1++) {
    if((rhs_[ i] >= INFTY) && (lhs_[ i] <= -INFTY)) {       // free row
      lp_->set_constr_type(lp_, i1, LE);
      lp_->set_rh(lp_, i1, lp_->get_infinite(lp_));
      lp_->set_rh_range(lp_, i1, lp_->get_infinite(lp_));
    }
    else if(rhs_[ i]-lhs_[ i] < SOLVER_FEASTOL) {           // equality
      lp_->set_constr_type(lp_, i1, EQ);
      lp_->set_rh(lp_, i1, rhs_[ i]);
    }
    else if((rhs_[ i] >= INFTY)  && (lhs_[ i] > -INFTY)) {  // simple > row
      // todo - throw a flag if both are infinity
      lp_->set_constr_type(lp_, i1, GE);
      lp_->set_rh(lp_, i1, lhs_[ i]);
    }
    else {                                                  // < or ranged row
      lp_->set_constr_type(lp_, i1, LE);
      lp_->set_rh(lp_, i1, rhs_[ i]);
      if(lhs_[ i] > -INFTY)
        lp_->set_rh_range(lp_, i1, rhs_[i]-lhs_[i]);
    }
  }

  /* define row names */
  rowNames_ = new char*[ nRows_];
  vector<string>::const_iterator iConNameLabel = label.begin();
  for(i = 0, i1 = 1; i < nRows_; i++, i1++) {
    STRALLOCCOPY(rowNames_[i], iConNameLabel->c_str());
    lp_->set_row_name(lp_, i1, rowNames_[i]);
    iConNameLabel++;
  }
  return 0;
}
int FMLLPSOLVEParser::onVariables(vector<std::string> const &label,               // 6.
         vector<double> const &lb, vector<double> const &ub,
         vector<char> const &domain,  vector<double> const &val)
{
  // lp_solve expects a dense objective function
  int i = 0, i1 = 0;
  if(val.size() < (unsigned)nVars_) cout << "Warning: objective function not dense" << endl;

  // copy and adjust variable bounds
  lb_ = new double[ nVars_];
  copy(lb.begin(), lb.end(), lb_);
  ub_ = new double[ nVars_];
  copy(ub.begin(), ub.end(), ub_);
  // need to use lp_solve infinity here instead of INFTY
  for (i = 0; i < nVars_; i++){
    if(ub_[ i] >= INFTY) ub_[ i] = lp_->get_infinite(lp_);
    if(lb_[ i] <= -INFTY) lb_[ i] = -lp_->get_infinite(lp_);
  }

  // define the variables in lp_solve
  colType_ = new char[ nVars_];
  copy(domain.begin(), domain.end(), colType_);

  obj_ = new double[ nVars_];
  copy(val.begin(), val.end(), obj_); // Handle this in onAMatrix

  colNames_ = new char*[ nVars_];
  vector<string>::const_iterator iVarNameLabel = label.begin();
  for(i = 0, i1 = 1; i < nVars_; i++, i1++) {
    STRALLOCCOPY(colNames_[i], iVarNameLabel->c_str());
#if 0    // Handle in onAMatrix
    lp_->set_col_name(lp_, i1, colNames_[i]);
    if(colType_[i] == 'B')
      lp_->set_binary(lp_, i1);
    else {
      lp_->set_bounds(lp_, i1, lb_[i], ub_[i]);
      if((colType_[i] == 'I') || (colType_[i] == 'S'))
        lp_->set_int(lp_, i1);
      if((colType_[i] == 's') || (colType_[i] == 'S'))
        lp_->set_semicont(lp_, i1);
    }
#endif
    iVarNameLabel++;
  }

  return 0;
}
int FMLLPSOLVEParser::onAMatrix(bool columnMajor, vector<double> const &val,
         vector<int> const &idx, vector<int> const &head,
         vector<int> const &size )
{
   int i = 0, i1, n = 0, nx = 0, ne = 0;

   // We can only handle column major form at this point
   isColMajor_ = columnMajor;
   if( !columnMajor) {
#ifdef DEBUG
      cout << "error -- we need column major form" << endl;
#endif
      return 0;
   }

   // create temporary sparse column storage arrays
   int *index = new int[ nRows_+1];
   double *value = new double[ nRows_+1];

   // define the nonzeros
   nNonz_ = (int)idx.size();
   idx_ = new int[ nNonz_];
   copy(idx.begin(), idx.end(), idx_);
   nonz_ = new double[ nNonz_];
   copy(val.begin(), val.end(), nonz_);

   // lp_solve wants the last pointer to the number of nonzeros and the first to zero
   pntANonz_ = new int[ head.size()+1];
   pntANonz_[ 0] = 0;
   // fill in the rest of the pointers
   vector<int>::const_iterator headLabel = head.begin();
   for(i = 1; i <= nVars_; i++) {
      pntANonz_[ i] = *headLabel;
#ifdef DEBUG
      cout << pntANonz_[ i] << "Head Index " << i << " numnonz = " <<pntANonz_[ i] <<endl;
#endif
      *headLabel++;
   }

   // add the data column-by-column
   ne = pntANonz_[0];
   for(i = 0, i1 = 1; i < nVars_; i++, i1++) {
     n = 0;
     if(obj_[i] != 0) {
       index[n] = 0;
//       value[n] = obj_[i]*nDir_;  // Why on earth is this the case???
       value[n] = obj_[i];
       n++;
     }
     nx = ne;
     ne = pntANonz_[i1];
     while(nx < ne) {
       index[n] = idx_[nx]+1;
       value[n] = nonz_[nx];
       n++;
       nx++;
     }
/*     sortREALByINT(value, index, n, 0, TRUE);  Not necessary after v5.1.1 */
     lp_->add_columnex(lp_, n, value, index);
     if(colType_[i] == 'B')
       lp_->set_binary(lp_, i1, TRUE);
     else {
       lp_->set_bounds(lp_, i1, lb_[i], ub_[i]);
       if(colType_[i] == 'I')
         lp_->set_int(lp_, i1, TRUE);
       if((colType_[i] == 's') || (colType_[i] == 'S'))
         lp_->set_semicont(lp_, i1, TRUE);
     }
     lp_->set_col_name(lp_, i1, colNames_[i]);
   }

   // set the of constant
   lp_->set_rh(lp_, 0, objConstant_);

   return 0;
}
int FMLLPSOLVEParser::solve()
{
   int i = 0, majorversion, minorversion, release, build;
   char solverMessage__[256];

   optValue_ = 0.0;
   solStatus_ = "optimal";
   lp_->lp_solve_version(&majorversion, &minorversion, &release, &build);
   sprintf(solverMessage__, "Solved using lp_solve v%d.%d", majorversion, minorversion);
   solverMessage_ = solverMessage__;
   primalVal_ = new double[ nVars_];
   primalIdx_ = new int[ nVars_];
   dualVal_ = new double[ nRows_];
   dualIdx_ = new int[ nRows_];

   int nSolStatus = lp_->solve(lp_);
   if (nSolStatus == OPTIMAL || nSolStatus == SUBOPTIMAL) {
      solStatus_ = lp_->get_statustext(lp_, nSolStatus);
      /* Retrieve the solution */
      /* Get the value of the objective */

     optValue_ = lp_->get_objective(lp_);
     lp_->get_primal_solution(lp_, primalVal_-1);
     lp_->get_dual_solution(lp_, dualVal_-1);

      /* Get the variable values */
      // Create a dense vector
      for (i = 0; i < nVars_; i++) {
         primalIdx_[ i] = i;
      }
      for (i = 0; i < nRows_; i++) {
         dualIdx_[ i] = i;
      }
   }
   else {
#ifdef DEBUG
     cout << "Optimal solution was not found -- status: " ;
#endif
   }
   return 0;
}
void FMLLPSOLVEParser::write(bool outputLPdata, bool isB64, bool isCompress,
      const char* xmlFile)
{
   isMin_ = true;
   if(nDir_ == -1)
     isMin_ = false;
#ifdef DEBUG
   cout << "write to file " << xmlFile << endl;
   cout << "nDir_ =  " << nDir_ << endl;
   cout << " Here is the optimal value to the LP  " << optValue_ << endl;
#endif
   //
   outputlinearProgramData( outputLPdata, isB64, isCompress, xmlFile);
   // optionally destroy the lp_solve environment
   if(isNativelp_)
     lp_->delete_lp(lp_);
}
char* FMLLPSOLVEParser::write(bool outputLPdata, bool isB64, bool isCompress)
{
   char *status = 0;
   isMin_ = true;
   if(nDir_ == -1)
     isMin_ = false;
#ifdef DEBUG
   cout << "nDir_ =  " << nDir_ << endl;
   cout << " Here is the optimal value to the LP  " << optValue_ << endl;
#endif
   //
   status = outputlinearProgramData( outputLPdata, isB64, isCompress, 0, true);
   // optionally destroy the lp_solve environment
   if(isNativelp_)
     lp_->delete_lp(lp_);

   return(status);
}
FMLLPSOLVEParser::~FMLLPSOLVEParser()
{
#ifdef DEBUG
   cout << "FMLLPSOLVEParser destructor called " << endl;
#endif
   if(nRows_ >= 0) {
     delete [] rhs_;
     delete [] lhs_;
     delete [] pntANonz_;
     delete [] rowNames_;
     delete [] idx_;
     delete [] nonz_;
   }

   if(nVars_ >= 0) {
     delete [] obj_;
     delete [] lb_;
     delete [] ub_;
     delete [] colNames_;
   }
}
