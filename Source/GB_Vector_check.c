//------------------------------------------------------------------------------
// GB_Vector_check: print a GraphBLAS GrB_Vector and check if it is valid
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2020, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// GrB_Vector: same as GrB_Matrix, except it has exactly one column

#include "GB.h"

GB_PUBLIC   // accessed by the MATLAB tests in GraphBLAS/Test only
GrB_Info GB_Vector_check    // check a GraphBLAS vector
(
    const GrB_Vector v,     // GraphBLAS vector to print and check
    const char *name,       // name of the vector
    int pr,                 // 0: print nothing, 1: print header and errors,
                            // 2: print brief, 3: print all
    FILE *f,                // file for output
    GB_Context Context
)
{

    //--------------------------------------------------------------------------
    // check GrB_Matrix conditions
    //--------------------------------------------------------------------------

    GrB_Info info = GB_matvec_check ((GrB_Matrix) v, name, pr, f, "vector",
        Context) ;
    if (! (info == GrB_INDEX_OUT_OF_BOUNDS || info == GrB_SUCCESS))
    { 
        // GrB_Matrix form is invalid already
        return (info) ;
    }

    //--------------------------------------------------------------------------
    // check GrB_Vector specific conditions
    //--------------------------------------------------------------------------

    if (!GB_VECTOR_OK (v))
    { 
        GBPR0 ("    GrB_Vector is invalid [%s]\n", name) ;
        return (GB_ERROR (GrB_INVALID_OBJECT, (GB_LOG,
            "GrB_Vector is invalid [%s]", name))) ;
    }

    return (info) ; // pass info directly from GB_matvec_check (jumbled case)
}

