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
* $Id: FMLLPSOLVEToXML.hpp,v 1.1 2004/07/16 18:41:57 leo Exp $
*/
#include "lp_lib.h"
#include "FMLLPToXML.hpp"
/*
This class works with the LPSOLVE API and the class FMLLPToXML.  It calls the methods
of class FMLLPToXML to write and XML file that validates agains the FML schema.
*/
/** \file FMLLPSOLVEToXML.hpp
\brief This class takes MPS or LPSOLVE formatted files and converts to XML
*/

/// This class works with the LPSOLVE API and the class FMLLPToXML.  It calls the methods
///of class FMLLPToXML to write an XML file that validates against the FML schema.
class FMLLPSOLVEToXML
{
public:
   FMLLPSOLVEToXML( lprec *lp, string filename, bool b64, bool compress);
   ~FMLLPSOLVEToXML(void);
   void writelinearProgramDescription( );
   void writelinearProgramData( );
   void writelinearProgramSolution( );
   void writelinearProgramFinish( bool canonical);
   protected:
   lprec *lp_;
   FMLLPToXML *lptoxml_;
   int nNonz;
   int nVars;
   int nRows;
   char* filename_;
   // some lp_solve variables
   char **colNames ;
   // set constraint name arrays
   char **rowNames;
   // LP data
   double *nonz, *objVal, *rowLB, *rowUB, *colLB, *colUB;
   int *pntANonz, *idx, *numNonz;
   char *colType;
   //
    /** The direction of optimization */
  int nDir_;
  bool isColMajor_,useB64_,compress_;
  /** The title/source of the linear program -- in this case the MPS file*/
  char *lpsource_, *XMLFileName_;
  /** the name of the file we wish to convert to XML */
  string targetfilename_;
};
