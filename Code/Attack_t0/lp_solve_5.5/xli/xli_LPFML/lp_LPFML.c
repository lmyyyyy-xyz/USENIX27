
/*  Modularized external language interface module - w/interface for lp_solve v5.0+
    This module is the implementation of the LPFML XML file format.
   ----------------------------------------------------------------------------------
    Author:        Kjell Eikland
    Contact:       kjell.eikland@broadpark.no
    License terms: LGPL.

    Template used: lp_XLI2.c
    Requires:      lp_lib.h

    Release notes:
    v1.0.0  1 August 2004       First implementation.

   ---------------------------------------------------------------------------------- */

/* Generic include libraries */
#include "lp_lib.h"

/* Include libraries for this language system */
#include <iostream>
#include "FMLLPSOLVEToXML.hpp"
#include "FMLLPSOLVEParser.hpp"

#ifdef FORTIFY
# include "lp_fortify.h"
#endif


/* Include routines common to language interface implementations */
#include "lp_XLI1.c"

using namespace std;


/* CAN MODIFY */
char * XLI_CALLMODEL xli_name(void)
{
  return( "XLI_LPFML v1.0" );
}

/* CAN MODIFY */
MYBOOL XLI_CALLMODEL xli_readmodel(lprec *lp, char *model, char *data, char *options, int verbose)
{
  MYBOOL status = FALSE;

  /* instantiate the XML object */
  FMLLPSOLVEParser ParseXML( lp );

  /* read the XML file */
  status = (MYBOOL) (ParseXML.ParseFile( model ) == 0);

  /* clean up and return */
/*  delete ParseXML; */
  return( status );
}

/* CAN MODIFY */
MYBOOL XLI_CALLMODEL xli_writemodel(lprec *lp, char *filename, char *options, MYBOOL results)
{
  /* parse parameter options */
  bool b64 = false, compress = false, canonical = false;
  if((options != NULL) && (strlen(options) > 0)){
    char *target;

    target = strstr(options, "-b64");
    if(target != NULL)
      b64 = true;
    target = strstr(options, "-comp");
    if(target != NULL)
      compress = true;
    target = strstr(options, "-can");
    if(target != NULL)
      canonical = true;
  }

  /* define structures */
  FMLLPSOLVEToXML LPSOLVEtoXML( lp, filename, b64, compress );

  /* convert and write lp data to xml */
  LPSOLVEtoXML.writelinearProgramDescription();
  LPSOLVEtoXML.writelinearProgramData();
  if(results)
    LPSOLVEtoXML.writelinearProgramSolution();
  LPSOLVEtoXML.writelinearProgramFinish( canonical );

  /* clean up and return */
/*  delete LPSOLVEtoXML; */
  return( TRUE );
}

