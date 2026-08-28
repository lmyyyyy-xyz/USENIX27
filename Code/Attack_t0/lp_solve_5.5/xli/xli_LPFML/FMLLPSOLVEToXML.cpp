/*
 * Copyright (c) 2003 Robert Fourer and Leonardo Lopes of
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
* $Id: FMLLPSOLVEToXML.cpp,v 1.1 2004/07/16 18:41:57 leo Exp $
*/
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include "FMLLPSOLVEToXML.hpp"
#include "FMLHandler.hpp"
#include <iostream>
//
#include "commonlib.h"
//
using namespace std;

FMLLPSOLVEToXML::FMLLPSOLVEToXML( lprec *lp, string filename, bool b64, bool compress) :
  useB64_(b64), compress_(compress)
{
  useB64_ = b64;
  compress_ = compress;
  lp_ = lp;
  targetfilename_ = filename;
}

FMLLPSOLVEToXML::~FMLLPSOLVEToXML(void)
{
   for (int i = 0; i < nVars; i++)
   {
      //why doesn't this work
      //delete colNames[ i];
   }
   /*delete[] colNames ;
   delete[] colNameData;   delete[] rowNames;
   delete[] rowNameData;
   delete[] pntANonz;
   delete[] nonz;
   delete[] objVal;
   delete[] rowLB;
   delete[] rowUB;
   delete[] colLB;
   delete[] colUB;
   delete[] idx;
   delete[] numNonz;
   delete[] colType;
   */
}

void FMLLPSOLVEToXML::writelinearProgramDescription( )
{
   // now get all the lp_solve information
   // get some key lp_solve parameters
   // the direction of the objective function
   int i, i1, nDir, *nzrow;
   // constant added to the objective function is
   double objConst, *column;
   int totalNonz, rownr, colnr, n;
   char lpSource[255];

   nVars = lp_->get_Ncolumns(lp_);
   nRows = lp_->get_Nrows(lp_);
   totalNonz = lp_->get_nonzeros(lp_);
   nDir  = (lp_->is_maxim(lp_) ? -1 : 1);

   objConst = lp_->get_rh(lp_, 0);
   strcpy(lpSource, lp_->get_lp_name(lp_));

// create local copies of the row and column names
   colNames = new char*[nVars + 1];
   for(i = 1; i <= nVars; i++)
     STRALLOCCOPY(colNames[i-1], lp_->get_col_name(lp_, i));
   rowNames = new char*[nRows];
   for(i = 1; i <= nRows; i++)
     STRALLOCCOPY(rowNames[i-1], lp_->get_row_name(lp_, i));

// create local copies of rown and column definitions
   colLB = new double[nVars];
   colUB = new double[nVars];
   colType = new char[nVars];
   for(i = 0, i1 = 1; i < nVars; i++, i1++) {
     if(lp_->is_binary(lp_, i1))
       colType[i] = 'B';
     else if(lp_->is_semicont(lp_, i1)) {
       if(lp_->is_int(lp_, i1))
         colType[i] = 'S';
       else
         colType[i] = 's';
     }
     else if(lp_->is_int(lp_, i1))
       colType[i] = 'I';
     else
       colType[i] = 'C';
     colLB[i] = lp_->get_lowbo(lp_, i1);
     colUB[i] = lp_->get_upbo(lp_, i1);
   }
   rowLB = new double[nRows];
   rowUB = new double[nRows];
   for(i = 0, i1 = 1; i < nRows; i++, i1++) {
     if(lp_->get_constr_type(lp_, i1) == EQ) {
       rowLB[i] = lp_->get_rh(lp_, i1);
       rowUB[i] = rowLB[i];
     }
     else if(lp_->get_constr_type(lp_, i1) == GE) {
       rowLB[i] = lp_->get_rh(lp_, i1);
       if(lp_->is_infinite(lp_, rowLB[i])) {
         rowLB[i] = -INFTY;
         rowUB[i] = INFTY;
       }
       else {
         rowUB[i] = lp_->get_rh_range(lp_, i1);
         if(lp_->is_infinite(lp_, rowUB[i]))
           rowUB[i] = INFTY;
         else
           rowUB[i] += rowLB[i];
       }
     }
     else /* LE */ {
       rowUB[i] = lp_->get_rh(lp_, i1);
       if(lp_->is_infinite(lp_, rowLB[i])) {
         rowUB[i] = INFTY;
         rowLB[i] = INFTY;
       }
       else {
         rowLB[i] = -lp_->get_rh_range(lp_, i1);
         if(lp_->is_infinite(lp_, rowLB[i]))
           rowLB[i] = -INFTY;
         else
           rowLB[i] += rowUB[i];
       }
     }
   }

// create local copies of the matrix data
   objVal = new double[nVars];
   nonz = new double[totalNonz];
   idx = new int[totalNonz];
   pntANonz = new int[nVars];
   numNonz = 0;                // This is optional and can be NULL

// first initialize matrix data
   for(i = 0; i < nVars; i++) {
     objVal[i] = 0;
     pntANonz[i] = 0;
   }
   nNonz = 0;

   column = new double[1 + nRows];
   nzrow = new int[1 + nRows];

   for(colnr = 1; colnr <= nVars; colnr++) {
     n = lp_->get_columnex(lp_, colnr, column, nzrow);
     for(i = 0; i < n; i++) {
       rownr = nzrow[i];
       if(rownr == 0)
         objVal[colnr-1] = column[i];
       else {
         nonz[nNonz] = column[i];
         idx[nNonz] = rownr-1;
         pntANonz[colnr-1]++;
         nNonz++;
       }
     }
   }
   delete[] column;
   delete[] nzrow;

// adjust start of column indeces
   for(i = 1; i < nVars; i++)
     pntANonz[i] += pntANonz[i-1];

// create an FMLLPToXML object
   lptoxml_ = new FMLLPToXML( nVars, nRows, nNonz);
//  create the output file
   lptoxml_ ->createDOM( );
// now write the description of the linear program
   bool isMin = true;
   if(nDir == -1)
     isMin = false;
   lptoxml_ ->setLPDescription(lpSource, isMin, objConst);
}

void FMLLPSOLVEToXML::writelinearProgramData( )
{
   lptoxml_ ->setRows(rowNames, rowLB, rowUB);
   lptoxml_ ->setColumns(colNames, colType, objVal, colLB, colUB);
   // we need to re-adjust some parameters
   // do we want base64 or not?
   lptoxml_->useBase64( useB64_);
   // compression or not
   lptoxml_->useCompress( compress_);
   // do we store by row or column
   //
   bool isColMajor=true;
   lptoxml_ ->setAMatrix(isColMajor, nonz, idx, pntANonz, numNonz);
}

void FMLLPSOLVEToXML::writelinearProgramSolution( )
{
   /* Perform the optimization */
   int i;
   double optValue;
   int *primalIdx = new int[nVars];
   int *dualIdx = new int[nRows];
   int solStatus = lp_->get_status(lp_);

   if((solStatus == OPTIMAL) || (solStatus == SUBOPTIMAL)) {
      // We return dense vectors
      for (i = 0; i < nVars; i++)
         primalIdx[i] = i;
      for (i = 0; i < nRows; i++)
         dualIdx[i] = i;
   }
   else
   {
#ifdef DEBUG
     //cout << "Optimal solution was not found -- status: ", solStatus << endl;
#endif
   }
   optValue = lp_->get_objective(lp_);

   int majorversion, minorversion, release, build;
   char solverMessage[256];

   lp_->lp_solve_version(&majorversion, &minorversion, &release, &build);
   sprintf(solverMessage, "Solved using lp_solve v%d.%d", majorversion, minorversion);

   double *primSol, *dualSol;
   lp_->get_ptr_primal_solution(lp_, &primSol);
   lp_->get_ptr_dual_solution(lp_, &dualSol);
   lptoxml_ ->setlinearProgramSolution(nVars, primSol+1, primalIdx,
                                       nRows, dualSol+1, dualIdx,
                                       optValue, lp_->get_statustext(lp_, solStatus), solverMessage,
                                       colNames, rowNames);
}

void FMLLPSOLVEToXML::writelinearProgramFinish(bool canonical )
{
  string tmp = targetfilename_;
  int posdot, posdelimiter;

#ifdef DEBUG
  cout << "the filename is   " << tmp << endl;
#endif
  posdelimiter = tmp.rfind( '\\');
  posdot = tmp.rfind( '.');
  if((posdelimiter >= 0) && (posdot >= 0) && (posdot < posdelimiter))
    posdot = -1;
  if(posdot < 0)
    posdot = tmp.length();
  if(canonical) tmp.insert(posdot, "_can");
  if(compress_) tmp.insert(posdot, "_comp");
  if(useB64_) tmp.insert(posdot, "_b64");
  lptoxml_->write( &tmp[0],!canonical);
  delete lptoxml_;
}

