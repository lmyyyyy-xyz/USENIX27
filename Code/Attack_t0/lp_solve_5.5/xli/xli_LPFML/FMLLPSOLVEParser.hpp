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
* $Id: FMLLPSOLVEParser.hpp,v 1.1 2004/07/16 18:41:57 leo Exp $
*/
#ifndef LPSOLVE_PARSER_H
#define LPSOLVE_PARSER_H
#include <xercesc/util/Base64.hpp>
//#include <xercesc/framework/MemoryManager.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>

#include "lp_lib.h"
#include "FMLLPToXML.hpp"
#include "FMLParser.hpp"
//#include "SAXCountHandlers.hpp"
#include<string>
using namespace std;
/** \file FMLLPSOLVEParser.hpp
\brief Contains a parser class that connects to the LPSOLVE API solver.
*/


/// This class inherits from FMLParser.  It overrides some of the on* methods
/// of its base class and uses that information to fill in the LPSOLVE data
/// structures.
class FMLLPSOLVEParser : public FMLParser{
protected:
   /** declare an instance of the lp_solve environment object */
   lprec *lp_;
   bool  isNativelp_;
   int   nDir_;
public:
   FMLLPSOLVEParser(lprec *lp);
   ~FMLLPSOLVEParser();
   virtual void onVariableCount( int const count);
   virtual void onConstraintCount( int const count);
   virtual void onObjectiveConstant(const double objConstant);
   virtual void onObjectiveSense( bool const isMin) ;
   virtual void onSource(const string &source);
   virtual int onConstraints(vector<std::string> const &label,
         vector<double> const &lhs, vector<double> const &rhs );
   virtual int onVariables(vector<std::string> const &label,
         vector<double> const &lb, vector<double> const &ub,
         vector<char> const &domain, vector<double> const &val );
   virtual int onAMatrix(bool columnMajor, vector<double> const &val,
         vector<int> const &idx, vector<int> const &head,
         vector<int> const &size ) ;
   virtual int solve();
   virtual void write( bool outputLPdata, bool isB64, bool isCompress,
      const char* xmlFile);
   virtual char* write(bool outputLPdata, bool isB64, bool isCompress);
};

#endif
