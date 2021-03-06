/*
 * File:          bHYPRE_GMRES_Impl.c
 * Symbol:        bHYPRE.GMRES-v1.0.0
 * Symbol Type:   class
 * Babel Version: 1.0.4
 * Description:   Server-side implementation for bHYPRE.GMRES
 * 
 * WARNING: Automatically generated; only changes within splicers preserved
 * 
 */

/*
 * DEVELOPERS ARE EXPECTED TO PROVIDE IMPLEMENTATIONS
 * FOR THE FOLLOWING METHODS BETWEEN SPLICER PAIRS.
 */

/*
 * Symbol "bHYPRE.GMRES" (version 1.0.0)
 * 
 * GMRES solver.
 * This calls Babel-interface matrix and vector functions, so it will work
 * with any consistent matrix, vector, and preconditioner classes.
 */

#include "bHYPRE_GMRES_Impl.h"
#include "sidl_NotImplementedException.h"
#include "sidl_Exception.h"

/* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES._includes) */
/* Insert-Code-Here {bHYPRE.GMRES._includes} (includes and arbitrary code) */


#include "bHYPRE_MPICommunicator_Impl.h"
#include "bHYPRE_IdentitySolver_Impl.h"
#include "bHYPRE_MatrixVectorView.h"
#include <math.h>

#include "hypre_babel_exception_handler.h"
/* DO-NOT-DELETE splicer.end(bHYPRE.GMRES._includes) */

#define SIDL_IOR_MAJOR_VERSION 1
#define SIDL_IOR_MINOR_VERSION 0
/*
 * Static class initializer called exactly once before any user-defined method is dispatched
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES__load"

#ifdef __cplusplus
extern "C"
#endif
void
impl_bHYPRE_GMRES__load(
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES._load) */
  /* Insert-Code-Here {bHYPRE.GMRES._load} (static class initializer method) */
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES._load) */
  }
}
/*
 * Class constructor called when the class is created.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES__ctor"

#ifdef __cplusplus
extern "C"
#endif
void
impl_bHYPRE_GMRES__ctor(
  /* in */ bHYPRE_GMRES self,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES._ctor) */
  /* Insert-Code-Here {bHYPRE.GMRES._ctor} (constructor method) */

   struct bHYPRE_GMRES__data * data;
   data = hypre_CTAlloc( struct bHYPRE_GMRES__data, 1 );

   /* set defaults */
   data -> bmpicomm      = bHYPRE_MPICommunicator_CreateC( (void *)MPI_COMM_NULL, _ex ); SIDL_CHECK(*_ex);
   data -> matrix = (bHYPRE_Operator)NULL;
   data -> precond = (bHYPRE_Solver)NULL;
   data -> k_dim          = 5;
   data -> min_iter       = 0;
   data -> max_iter       = 1000;
   data -> rel_change     = 0;
   data -> stop_crit      = 0; /* rel. residual norm */
   data -> converged      = 0;
   data -> tol            = 1.0e-06;
   data -> cf_tol         = 0.0;
   data -> rel_residual_norm = 0.0;
   data -> r              = (bHYPRE_Vector)NULL;
   data -> w              = (bHYPRE_Vector)NULL;
   data -> p              = (bHYPRE_Vector *)NULL;
   data -> print_level    = 0;
   data -> logging        = 0;
   data -> norms          = NULL;
   data -> log_file_name  = NULL;

   bHYPRE_GMRES__set_data( self, data );

   return; hypre_babel_exception_no_return(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES._ctor) */
  }
}

/*
 * Special Class constructor called when the user wants to wrap his own private data.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES__ctor2"

#ifdef __cplusplus
extern "C"
#endif
void
impl_bHYPRE_GMRES__ctor2(
  /* in */ bHYPRE_GMRES self,
  /* in */ void* private_data,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES._ctor2) */
    /* Insert-Code-Here {bHYPRE.GMRES._ctor2} (special constructor method) */
    /*
     * This method has not been implemented
     */

    SIDL_THROW(*_ex, sidl_NotImplementedException,     "This method has not been implemented");
  EXIT:;
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES._ctor2) */
  }
}
/*
 * Class destructor called when the class is deleted.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES__dtor"

#ifdef __cplusplus
extern "C"
#endif
void
impl_bHYPRE_GMRES__dtor(
  /* in */ bHYPRE_GMRES self,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES._dtor) */
  /* Insert-Code-Here {bHYPRE.GMRES._dtor} (destructor method) */

   int i;
   struct bHYPRE_GMRES__data * data;
   data = bHYPRE_GMRES__get_data( self );

   if (data)
   {
      if ( (data -> norms) != NULL )
      {
         hypre_TFree( data -> norms );
         data -> norms = NULL;
      } 

      if ( data -> r != (bHYPRE_Vector)NULL )
      {
         bHYPRE_Vector_deleteRef( data->r, _ex ); SIDL_CHECK(*_ex);
      }
      if ( data -> w != (bHYPRE_Vector)NULL )
      {
         bHYPRE_Vector_deleteRef( data->w, _ex ); SIDL_CHECK(*_ex);
      }
      if ( data -> p != (bHYPRE_Vector *)NULL )
      {
         for ( i=0; i<(data->k_dim + 1); ++i )
         {
            bHYPRE_Vector_deleteRef( (data->p)[i], _ex ); SIDL_CHECK(*_ex);
         }
         hypre_TFree( data -> p );
      }

      if ( data -> matrix != (bHYPRE_Operator)NULL )
      {
         bHYPRE_Operator_deleteRef( data->matrix, _ex ); SIDL_CHECK(*_ex);
      }
      if ( data -> precond != (bHYPRE_Solver)NULL )
      {
         bHYPRE_Solver_deleteRef( data->precond, _ex ); SIDL_CHECK(*_ex);
      }

      hypre_TFree( data );
   }

   return; hypre_babel_exception_no_return(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES._dtor) */
  }
}

/*
 *  This function is the preferred way to create a GMRES solver. 
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_Create"

#ifdef __cplusplus
extern "C"
#endif
bHYPRE_GMRES
impl_bHYPRE_GMRES_Create(
  /* in */ bHYPRE_MPICommunicator mpi_comm,
  /* in */ bHYPRE_Operator A,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.Create) */
  /* Insert-Code-Here {bHYPRE.GMRES.Create} (Create method) */

   bHYPRE_GMRES solver = bHYPRE_GMRES__create(_ex); SIDL_CHECK(*_ex);
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( solver );
   bHYPRE_IdentitySolver Id  = bHYPRE_IdentitySolver_Create( mpi_comm, _ex ); SIDL_CHECK(*_ex);
   bHYPRE_Solver IdS = bHYPRE_Solver__cast( Id, _ex ); SIDL_CHECK(*_ex);

   if (data->bmpicomm) {
      bHYPRE_MPICommunicator_deleteRef( data->bmpicomm, _ex ); SIDL_CHECK(*_ex);
   }
   data->bmpicomm = mpi_comm;
   if( data->matrix != (bHYPRE_Operator)NULL )
   {
      bHYPRE_Operator_deleteRef( data->matrix, _ex ); SIDL_CHECK(*_ex);
   }

   data->matrix = A;
   bHYPRE_Operator_addRef( data->matrix, _ex ); SIDL_CHECK(*_ex);

   data->precond = IdS;

   bHYPRE_IdentitySolver_deleteRef( Id, _ex ); SIDL_CHECK(*_ex);
   /* ...Create and cast created 2 references, we're keeping only one (data->precond) */

   return solver;

   hypre_babel_exception_no_return(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.Create) */
  }
}

/*
 * Set the preconditioner.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetPreconditioner"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetPreconditioner(
  /* in */ bHYPRE_GMRES self,
  /* in */ bHYPRE_Solver s,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetPreconditioner) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetPreconditioner} (SetPreconditioner method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );
   if( data->precond != (bHYPRE_Solver)NULL )
   {
      bHYPRE_Solver_deleteRef( data->precond, _ex ); SIDL_CHECK(*_ex);
   }

   data->precond = s;
   bHYPRE_Solver_addRef( data->precond, _ex ); SIDL_CHECK(*_ex);

   return ierr;

   hypre_babel_exception_return_error(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetPreconditioner) */
  }
}

/*
 * Method:  GetPreconditioner[]
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_GetPreconditioner"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_GetPreconditioner(
  /* in */ bHYPRE_GMRES self,
  /* out */ bHYPRE_Solver* s,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.GetPreconditioner) */
  /* Insert-Code-Here {bHYPRE.GMRES.GetPreconditioner} (GetPreconditioner method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   *s = data->precond;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.GetPreconditioner) */
  }
}

/*
 * Method:  Clone[]
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_Clone"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_Clone(
  /* in */ bHYPRE_GMRES self,
  /* out */ bHYPRE_PreconditionedSolver* x,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.Clone) */
  /* Insert-Code-Here {bHYPRE.GMRES.Clone} (Clone method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );
   struct bHYPRE_GMRES__data * datax;
   bHYPRE_GMRES GMRES_x;

   GMRES_x = bHYPRE_GMRES_Create( data->bmpicomm, data->matrix, _ex ); SIDL_CHECK(*_ex);


   /* Copy most data members.
      The preconditioner copy will be a shallow copy (just the pointer);
      it is likely to be replaced later.
      But don't copy anything created in Setup (r,w,p,norms,log_file_name).
      The user will call Setup on x, later.
      Also don't copy the end-of-solve diagnostics (converged,num_iterations,
      rel_residual_norm) */

   datax = bHYPRE_GMRES__get_data( GMRES_x );
   datax->tol               = data->tol;
   datax->cf_tol            = data->cf_tol;
   datax->max_iter          = data->max_iter;
   datax->min_iter          = data->min_iter;
   datax->k_dim             = data->k_dim;
   datax->rel_change        = data->rel_change;
   datax->stop_crit         = data->stop_crit;
   datax->print_level       = data->print_level;
   datax->logging           = data->logging;

   bHYPRE_GMRES_SetPreconditioner( GMRES_x, data->precond, _ex ); SIDL_CHECK(*_ex);

   *x = bHYPRE_PreconditionedSolver__cast( GMRES_x, _ex ); SIDL_CHECK(*_ex);

   bHYPRE_GMRES_deleteRef( GMRES_x,_ex ); SIDL_CHECK(*_ex);
   return ierr;

   hypre_babel_exception_return_error(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.Clone) */
  }
}

/*
 * Set the operator for the linear system being solved.
 * DEPRECATED.  use Create
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetOperator"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetOperator(
  /* in */ bHYPRE_GMRES self,
  /* in */ bHYPRE_Operator A,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetOperator) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetOperator} (SetOperator method) */

   /* DEPRECATED  the second argument in Create does the same thing */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data;

   data = bHYPRE_GMRES__get_data( self );
   if( data->matrix != (bHYPRE_Operator)NULL )
   {
      bHYPRE_Operator_deleteRef( data->matrix, _ex ); SIDL_CHECK(*_ex);
   }

   data->matrix = A;
   bHYPRE_Operator_addRef( data->matrix, _ex ); SIDL_CHECK(*_ex);

   return ierr;

   hypre_babel_exception_return_error(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetOperator) */
  }
}

/*
 * (Optional) Set the convergence tolerance.
 * DEPRECATED.  use SetDoubleParameter
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetTolerance"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetTolerance(
  /* in */ bHYPRE_GMRES self,
  /* in */ double tolerance,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetTolerance) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetTolerance} (SetTolerance method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   data -> tol = tolerance;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetTolerance) */
  }
}

/*
 * (Optional) Set maximum number of iterations.
 * DEPRECATED   use SetIntParameter
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetMaxIterations"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetMaxIterations(
  /* in */ bHYPRE_GMRES self,
  /* in */ int32_t max_iterations,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetMaxIterations) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetMaxIterations} (SetMaxIterations method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   data -> max_iter = max_iterations;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetMaxIterations) */
  }
}

/*
 * (Optional) Set the {\it logging level}, specifying the degree
 * of additional informational data to be accumulated.  Does
 * nothing by default (level = 0).  Other levels (if any) are
 * implementation-specific.  Must be called before {\tt Setup}
 * and {\tt Apply}.
 * DEPRECATED   use SetIntParameter
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetLogging"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetLogging(
  /* in */ bHYPRE_GMRES self,
  /* in */ int32_t level,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetLogging) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetLogging} (SetLogging method) */
 
   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   data -> logging = level;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetLogging) */
  }
}

/*
 * (Optional) Set the {\it print level}, specifying the degree
 * of informational data to be printed either to the screen or
 * to a file.  Does nothing by default (level=0).  Other levels
 * (if any) are implementation-specific.  Must be called before
 * {\tt Setup} and {\tt Apply}.
 * DEPRECATED   use SetIntParameter
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetPrintLevel"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetPrintLevel(
  /* in */ bHYPRE_GMRES self,
  /* in */ int32_t level,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetPrintLevel) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetPrintLevel} (SetPrintLevel method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   data -> print_level = level;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetPrintLevel) */
  }
}

/*
 * (Optional) Return the number of iterations taken.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_GetNumIterations"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_GetNumIterations(
  /* in */ bHYPRE_GMRES self,
  /* out */ int32_t* num_iterations,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.GetNumIterations) */
  /* Insert-Code-Here {bHYPRE.GMRES.GetNumIterations} (GetNumIterations method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   *num_iterations = data->num_iterations;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.GetNumIterations) */
  }
}

/*
 * (Optional) Return the norm of the relative residual.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_GetRelResidualNorm"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_GetRelResidualNorm(
  /* in */ bHYPRE_GMRES self,
  /* out */ double* norm,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.GetRelResidualNorm) */
  /* Insert-Code-Here {bHYPRE.GMRES.GetRelResidualNorm} (GetRelResidualNorm method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   *norm = data->rel_residual_norm;

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.GetRelResidualNorm) */
  }
}

/*
 * Set the MPI Communicator.
 * DEPRECATED, use Create:
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetCommunicator"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetCommunicator(
  /* in */ bHYPRE_GMRES self,
  /* in */ bHYPRE_MPICommunicator mpi_comm,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetCommunicator) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetCommunicator} (SetCommunicator method) */
   return 1;  /* DEPRECATED and will never be implemented */
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetCommunicator) */
  }
}

/*
 * The Destroy function doesn't necessarily destroy anything.
 * It is just another name for deleteRef.  Thus it decrements the
 * object's reference count.  The Babel memory management system will
 * destroy the object if the reference count goes to zero.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_Destroy"

#ifdef __cplusplus
extern "C"
#endif
void
impl_bHYPRE_GMRES_Destroy(
  /* in */ bHYPRE_GMRES self,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.Destroy) */
    /* Insert-Code-Here {bHYPRE.GMRES.Destroy} (Destroy method) */
     bHYPRE_GMRES_deleteRef(self,_ex);
     return;
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.Destroy) */
  }
}

/*
 * Set the int parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetIntParameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetIntParameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in */ int32_t value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetIntParameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetIntParameter} (SetIntParameter method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   if ( strcmp(name,"KDim")==0 )
   {
      data -> k_dim = value;
   }
   else if ( strcmp(name,"MaxIter")==0 || strcmp(name,"MaxIterations")==0 )
   {
      data -> max_iter = value;
   }
   else if ( strcmp(name,"MinIter")==0 || strcmp(name,"MinIterations")==0 )
   {
      data -> min_iter = value;
   }
   else if ( strcmp(name,"RelChange")==0 || strcmp(name,"relative change test")==0 )
   {
      data -> rel_change = value;
   }
   else if ( strcmp(name,"StopCrit")==0 )
   {
      data -> stop_crit = value;
   }
   else if ( strcmp(name,"Logging")==0 )
   {
      data -> logging = value;
   }
   else if ( strcmp(name,"PrintLevel")==0 )
   {
      data -> print_level = value;
   }
   else
   {
      ierr=1;
   }

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetIntParameter) */
  }
}

/*
 * Set the double parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetDoubleParameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetDoubleParameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in */ double value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetDoubleParameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetDoubleParameter} (SetDoubleParameter method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   if ( strcmp(name,"Tolerance")==0  || strcmp(name,"Tol")==0 )
   {
      data -> tol = value;
   }
   else if ( strcmp(name,"CF_Tol")==0 )
   {
      data -> cf_tol = value;
   }
   else
   {
      ierr=1;
   }

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetDoubleParameter) */
  }
}

/*
 * Set the string parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetStringParameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetStringParameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in */ const char* value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetStringParameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetStringParameter} (SetStringParameter method) */

   return 1;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetStringParameter) */
  }
}

/*
 * Set the int 1-D array parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetIntArray1Parameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetIntArray1Parameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in rarray[nvalues] */ int32_t* value,
  /* in */ int32_t nvalues,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetIntArray1Parameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetIntArray1Parameter} (SetIntArray1Parameter method) */

   return 1;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetIntArray1Parameter) */
  }
}

/*
 * Set the int 2-D array parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetIntArray2Parameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetIntArray2Parameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in array<int,2,column-major> */ struct sidl_int__array* value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetIntArray2Parameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetIntArray2Parameter} (SetIntArray2Parameter method) */

   return 1;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetIntArray2Parameter) */
  }
}

/*
 * Set the double 1-D array parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetDoubleArray1Parameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetDoubleArray1Parameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in rarray[nvalues] */ double* value,
  /* in */ int32_t nvalues,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetDoubleArray1Parameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetDoubleArray1Parameter} (SetDoubleArray1Parameter method) */

   return 1;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetDoubleArray1Parameter) */
  }
}

/*
 * Set the double 2-D array parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_SetDoubleArray2Parameter"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_SetDoubleArray2Parameter(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* in array<double,2,column-major> */ struct sidl_double__array* value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.SetDoubleArray2Parameter) */
  /* Insert-Code-Here {bHYPRE.GMRES.SetDoubleArray2Parameter} (SetDoubleArray2Parameter method) */

   return 1;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.SetDoubleArray2Parameter) */
  }
}

/*
 * Set the int parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_GetIntValue"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_GetIntValue(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* out */ int32_t* value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.GetIntValue) */
  /* Insert-Code-Here {bHYPRE.GMRES.GetIntValue} (GetIntValue method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   if ( strcmp(name,"NumIterations")==0 )
   {
      *value = data -> num_iterations;
   }
   else if ( strcmp(name,"Converged")==0 )
   {
      *value = data -> converged;
   }
   else if ( strcmp(name,"KDim")==0 )
   {
      *value = data -> k_dim;
   }
   else if ( strcmp(name,"MaxIter")==0 || strcmp(name,"MaxIterations")==0 )
   {
      *value = data -> max_iter;
   }
   else if ( strcmp(name,"MinIter")==0 || strcmp(name,"MinIterations")==0 )
   {
      *value = data -> min_iter;
   }
   else if ( strcmp(name,"RelChange")==0 || strcmp(name,"relative change test")==0 )
   {
      *value = data -> rel_change;
   }
   else if ( strcmp(name,"StopCrit")==0 )
   {
      *value = data -> stop_crit;
   }
   else if ( strcmp(name,"Logging")==0 )
   {
      *value = data -> logging;
   }
   else if ( strcmp(name,"PrintLevel")==0 )
   {
      *value = data -> print_level;
   }
   else
   {
      ierr=1;
   }

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.GetIntValue) */
  }
}

/*
 * Get the double parameter associated with {\tt name}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_GetDoubleValue"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_GetDoubleValue(
  /* in */ bHYPRE_GMRES self,
  /* in */ const char* name,
  /* out */ double* value,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.GetDoubleValue) */
  /* Insert-Code-Here {bHYPRE.GMRES.GetDoubleValue} (GetDoubleValue method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );

   if ( strcmp(name,"Final Relative Residual Norm")==0 ||
        strcmp(name,"FinalRelativeResidualNorm")==0 ||
        strcmp(name,"RelResidualNorm")==0 ||
        strcmp(name,"RelativeResidualNorm")==0 )
   {
      *value = data -> rel_residual_norm;
   }
   else if ( strcmp(name,"Tolerance")==0  || strcmp(name,"Tol")==0 )
   {
      *value = data -> tol;
   }
   else if ( strcmp(name,"CF_Tol")==0 )
   {
      *value = data -> cf_tol;
   }
   else
   {
      ierr=1;
   }

   return ierr;

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.GetDoubleValue) */
  }
}

/*
 * (Optional) Do any preprocessing that may be necessary in
 * order to execute {\tt Apply}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_Setup"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_Setup(
  /* in */ bHYPRE_GMRES self,
  /* in */ bHYPRE_Vector b,
  /* in */ bHYPRE_Vector x,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.Setup) */
  /* Insert-Code-Here {bHYPRE.GMRES.Setup} (Setup method) */

   int ierr = 0;
   int i;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );
   bHYPRE_MatrixVectorView Vp, Vr, Vw;

   int            k_dim            = data -> k_dim;
   int            max_iter         = data -> max_iter;
 
   /* Setup should not be called more than once. */
   hypre_assert( data->p == (bHYPRE_Vector*)NULL );
   hypre_assert( data->r == (bHYPRE_Vector)NULL );
   hypre_assert( data->w == (bHYPRE_Vector)NULL );

   /*--------------------------------------------------
    * The arguments for NewVector are important to
    * maintain consistency between the setup and
    * compute phases of matvec and the preconditioner.
    *--------------------------------------------------*/
 
   data -> p = hypre_CTAlloc( bHYPRE_Vector, k_dim + 1 );
   for ( i=0; i<(k_dim+1); ++i )
   {
      ierr += bHYPRE_Vector_Clone( x, &((data->p)[i]), _ex ); SIDL_CHECK(*_ex);
      Vp = (bHYPRE_MatrixVectorView) bHYPRE_Vector__cast2( (data->p)[i], "bHYPRE.MatrixVectorView", _ex );
      SIDL_CHECK(*_ex);
      if ( Vp )
      {
         ierr += bHYPRE_MatrixVectorView_Assemble( Vp, _ex ); SIDL_CHECK(*_ex);
         bHYPRE_MatrixVectorView_deleteRef( Vp, _ex ); SIDL_CHECK(*_ex);
      }
   }
   ierr += bHYPRE_Vector_Clone( b, &(data->r), _ex ); SIDL_CHECK(*_ex);
   ierr += bHYPRE_Vector_Clone( b, &(data->w), _ex ); SIDL_CHECK(*_ex);
   Vr = (bHYPRE_MatrixVectorView) bHYPRE_Vector__cast2( data->r, "bHYPRE.MatrixVectorView", _ex );
   SIDL_CHECK(*_ex);
   if ( Vr )
   {
      ierr += bHYPRE_MatrixVectorView_Assemble( Vr, _ex ); SIDL_CHECK(*_ex);
      bHYPRE_MatrixVectorView_deleteRef( Vr, _ex ); SIDL_CHECK(*_ex);
   }
   Vw = (bHYPRE_MatrixVectorView) bHYPRE_Vector__cast2( data->w, "bHYPRE.MatrixVectorView", _ex );
   SIDL_CHECK(*_ex);
   if ( Vw )
   {
      ierr += bHYPRE_MatrixVectorView_Assemble( Vw, _ex ); SIDL_CHECK(*_ex);
      bHYPRE_MatrixVectorView_deleteRef( Vw, _ex ); SIDL_CHECK(*_ex);
   }


   ierr += bHYPRE_Solver_Setup( data->precond, b, x, _ex ); SIDL_CHECK(*_ex);

   /*-----------------------------------------------------
    * Allocate space for log info
    *-----------------------------------------------------*/
 
   if ( data->logging>0  || data->print_level>0 ) 
   {  /* arrays needed for logging */
      if ( data->norms != NULL )
         hypre_TFree( data->norms );
      data->norms = hypre_CTAlloc( double, max_iter + 1 );
   }
   if ( data->print_level > 0 ) {
      if ( data -> log_file_name == NULL )
         data -> log_file_name = "gmres.out.log";
   }
 
   return ierr;

   hypre_babel_exception_return_error(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.Setup) */
  }
}

/*
 * Apply the operator to {\tt b}, returning {\tt x}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_Apply"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_Apply(
  /* in */ bHYPRE_GMRES self,
  /* in */ bHYPRE_Vector b,
  /* inout */ bHYPRE_Vector* x,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.Apply) */
   /* Insert-Code-Here {bHYPRE.GMRES.Apply} (Apply method) */

   int ierr = 0;
   struct bHYPRE_GMRES__data * data = bHYPRE_GMRES__get_data( self );
   bHYPRE_Operator A = data->matrix;
   bHYPRE_Solver   precond      = data -> precond;

   int 		     k_dim        = data -> k_dim;
   int               min_iter     = data -> min_iter;
   int 		     max_iter     = data -> max_iter;
   int               rel_change   = data -> rel_change;
   int 		     stop_crit    = data -> stop_crit;
   double 	     accuracy     = data -> tol;
   double 	     cf_tol       = data -> cf_tol;

   bHYPRE_Vector     r            = data -> r;
   bHYPRE_Vector     w            = data -> w;
   bHYPRE_Vector   * p            = data -> p;

   int             print_level    = data -> print_level;
   int             logging        = data -> logging;

   double         *norms          = data -> norms;
/* not used yet   char           *log_file_name  = data -> log_file_name);*/
/*   FILE           *fp; */
   
   int        break_value = 0;
   int	      i, j, k;
   double     *rs, **hh, *c, *s;
   int        iter; 
   double     epsilon, gamma, t, r_norm, b_norm, x_norm;
   double     epsmac = 1.e-16; 
   double     ieee_check = 0.;

   double     guard_zero_residual; 
   double     cf_ave_0 = 0.0;
   double     cf_ave_1 = 0.0;
   double     weight;
   double     r_norm_0;

   bHYPRE_MPICommunicator  bmpicomm = data -> bmpicomm;
   MPI_Comm        comm;
   int        my_id, num_procs;

   comm = bHYPRE_MPICommunicator__get_data(bmpicomm)->mpi_comm;
   MPI_Comm_size( comm, &num_procs );
   MPI_Comm_rank( comm, &my_id );

   /*-----------------------------------------------------------------------
    * With relative change convergence test on, it is possible to attempt
    * another iteration with a zero residual. This causes the parameter
    * alpha to go NaN. The guard_zero_residual parameter is to circumvent
    * this. Perhaps it should be set to something non-zero (but small).
    *-----------------------------------------------------------------------*/
   guard_zero_residual = 0.0;

   if ( logging>0 || print_level>0 )
   {
      norms          = data -> norms;
      /* not used yet      log_file_name  = data -> log_file_name;*/
      /* fp = fopen(log_file_name,"w"); */
   }

   /* initialize work arrays */
   rs = hypre_CTAlloc(double,k_dim+1); 
   c = hypre_CTAlloc(double,k_dim); 
   s = hypre_CTAlloc(double,k_dim); 

   hh = hypre_CTAlloc(double*,k_dim+1); 
   for (i=0; i < k_dim+1; i++)
   {	
      hh[i] = hypre_CTAlloc(double,k_dim); 
   }

   /* compute initial residual,  p[0] = b - Ax */
   ierr += bHYPRE_Operator_Apply( A, *x, &(p[0]), _ex );/* p[0] = Ax */
   SIDL_CHECK(*_ex);
   ierr += bHYPRE_Vector_Axpy( p[0], -1.0, b, _ex );    /* p[0] = p[0] - b = Ax - b */
   SIDL_CHECK(*_ex);
   ierr += bHYPRE_Vector_Scale( p[0], -1.0, _ex );      /* p[0] = -p[0] = b - Ax */
   SIDL_CHECK(*_ex);

   ierr += bHYPRE_Vector_Dot( b, b, &b_norm, _ex );  /* b_norm = <b,b > */
   SIDL_CHECK(*_ex);
   b_norm = sqrt( b_norm );                     /* b_norm = L2 norm of b */

   /* Since it is does not diminish performance, attempt to return an error flag
      and notify users when they supply bad input. */
   if (b_norm != 0.) ieee_check = b_norm/b_norm; /* INF -> NaN conversion */
   if (ieee_check != ieee_check)
   {
      /* ...INFs or NaNs in input can make ieee_check a NaN.  This test
         for ieee_check self-equality works on all IEEE-compliant compilers/
         machines, c.f. page 8 of "Lecture Notes on the Status of IEEE 754"
         by W. Kahan, May 31, 1996.  Currently (July 2002) this paper may be
         found at http://HTTP.CS.Berkeley.EDU/~wkahan/ieee754status/IEEE754.PDF */
      if (logging > 0 || print_level > 0)
      {
         printf("\n\nERROR detected by Hypre ... BEGIN\n");
         printf("ERROR -- hypre_GMRESSolve: INFs and/or NaNs detected in input.\n");
         printf("User probably placed non-numerics in supplied b.\n");
         printf("Returning error flag += 101.  Program not terminated.\n");
         printf("ERROR detected by Hypre ... END\n\n\n");
      }
      ierr += 101;
      return ierr;
   }

   ierr += bHYPRE_Vector_Dot( p[0], p[0], &r_norm, _ex ); /* r_norm = <p[0],p[0]> */
   SIDL_CHECK(*_ex);
   r_norm = sqrt( r_norm );                   /* r_norm = L2 norm of p[0] */
   r_norm_0 = r_norm;

   /* Since it is does not diminish performance, attempt to return an error flag
      and notify users when they supply bad input. */
   if (r_norm != 0.) ieee_check = r_norm/r_norm; /* INF -> NaN conversion */
   if (ieee_check != ieee_check)
   {
      /* ...INFs or NaNs in input can make ieee_check a NaN.  This test
         for ieee_check self-equality works on all IEEE-compliant compilers/
         machines, c.f. page 8 of "Lecture Notes on the Status of IEEE 754"
         by W. Kahan, May 31, 1996.  Currently (July 2002) this paper may be
         found at http://HTTP.CS.Berkeley.EDU/~wkahan/ieee754status/IEEE754.PDF */
      if (logging > 0 || print_level > 0)
      {
         printf("\n\nERROR detected by Hypre ... BEGIN\n");
         printf("ERROR -- hypre_GMRESSolve: INFs and/or NaNs detected in input.\n");
         printf("User probably placed non-numerics in supplied A or x_0.\n");
         printf("Returning error flag += 101.  Program not terminated.\n");
         printf("ERROR detected by Hypre ... END\n\n\n");
      }
      ierr += 101;
      return ierr;
   }

   if ( logging>0 || print_level > 0)
   {
      norms[0] = r_norm;
      if ( print_level>1 && my_id == 0 )
      {
  	 printf("L2 norm of b: %e\n", b_norm);
         if (b_norm == 0.0)
            printf("Rel_resid_norm actually contains the residual norm\n");
         printf("Initial L2 norm of residual: %e\n", r_norm);
      
      }
   }
   iter = 0;

   if (b_norm > 0.0)
   {
/* convergence criterion |r_i| <= accuracy*|b| if |b| > 0 */
      epsilon = accuracy * b_norm;
   }
   else
   {
/* convergence criterion |r_i| <= accuracy*|r0| if |b| = 0 */
      epsilon = accuracy * r_norm;
   };

/* convergence criterion |r_i| <= accuracy , absolute residual norm*/
   if ( stop_crit && !rel_change )
      epsilon = accuracy;

   if ( print_level>1 && my_id == 0 )
   {
      if (b_norm > 0.0)
      {printf("=============================================\n\n");
         printf("Iters     resid.norm     conv.rate  rel.res.norm\n");
         printf("-----    ------------    ---------- ------------\n");
      
      }

      else
      {printf("=============================================\n\n");
         printf("Iters     resid.norm     conv.rate\n");
         printf("-----    ------------    ----------\n");
      
      };
   }

   /* *******************************************************
    *
    *  main iteration loop
    *
    * ******************************************************* */

   while (iter < max_iter)
   {
      /* initialize first term of hessenberg system */

      rs[0] = r_norm;
      if (r_norm == 0.0)
      {
         hypre_TFree(c); 
         hypre_TFree(s); 
         hypre_TFree(rs);
         for (i=0; i < k_dim+1; i++) hypre_TFree(hh[i]);
         hypre_TFree(hh); 
         data -> converged = 1;
         ierr = 0;
         return ierr;
      }

      if (r_norm <= epsilon && iter >= min_iter) 
      {
         /* r = r - Ax = b - Ax */
         ierr += bHYPRE_Operator_Apply( A, *x, &r, _ex ); /* r = Ax */
         SIDL_CHECK(*_ex);
         ierr += bHYPRE_Vector_Axpy( r, -1.0, b, _ex );   /* r = r - b = Ax - b */
         SIDL_CHECK(*_ex);
         ierr += bHYPRE_Vector_Scale( r, -1.0, _ex );     /* r = -r = b - Ax */
         SIDL_CHECK(*_ex);
         ierr += bHYPRE_Vector_Dot( r, r, &r_norm, _ex ); /* r_norm = <r,r> */
         SIDL_CHECK(*_ex);
         r_norm = sqrt( r_norm );                    /* r_norm = L2 norm of r */
         if (r_norm <= epsilon)
         {
            if ( print_level>1 && my_id == 0)
            {
               printf("\n\n");
               printf("Final L2 norm of residual: %e\n\n", r_norm);
            }
            data -> converged = 1;
            break;
         }
         else
            if ( print_level>0 && my_id == 0)
               printf("false convergence 1\n");
      }

      t = 1.0 / r_norm;
      ierr += bHYPRE_Vector_Scale( p[0], t, _ex ); SIDL_CHECK(*_ex);
      i = 0;
      while (i < k_dim && (r_norm > epsilon || iter < min_iter)
             && iter < max_iter)
      {
         i++;
         iter++;
         ierr += bHYPRE_Vector_Clear( r, _ex ); SIDL_CHECK(*_ex);
         ierr += bHYPRE_Solver_Apply( precond, p[i-1], &r, _ex ); SIDL_CHECK(*_ex);
         ierr += bHYPRE_Operator_Apply( A, r, &(p[i]), _ex );  /* p[i] = Ar */
         SIDL_CHECK(*_ex);

         /* modified Gram_Schmidt */
         for (j=0; j < i; j++)
         {
            /* hh[j][i-1] = < p[j], p[i] >
               p[i] = p[i] - hh[j][i-1] * p[j] */
            ierr += bHYPRE_Vector_Dot( p[j], p[i], &( hh[j][i-1] ), _ex ); SIDL_CHECK(*_ex);
            ierr += bHYPRE_Vector_Axpy( p[i], -hh[j][i-1], p[j], _ex ); SIDL_CHECK(*_ex);
         }
         ierr += bHYPRE_Vector_Dot( p[i], p[i], &t, _ex ); SIDL_CHECK(*_ex);
         t = sqrt(t);            /* t = L2 norm of p[i] */
         hh[i][i-1] = t;	
         if (t != 0.0)
         {
            t = 1.0/t;
            ierr += bHYPRE_Vector_Scale( p[i], t, _ex ); SIDL_CHECK(*_ex);
         }
         /* done with modified Gram_schmidt and Arnoldi step.
            update factorization of hh */
         for (j = 1; j < i; j++)
         {
            t = hh[j-1][i-1];
            hh[j-1][i-1] = c[j-1]*t + s[j-1]*hh[j][i-1];		
            hh[j][i-1] = -s[j-1]*t + c[j-1]*hh[j][i-1];
         }
         gamma = sqrt(hh[i-1][i-1]*hh[i-1][i-1] + hh[i][i-1]*hh[i][i-1]);
         if (gamma == 0.0) gamma = epsmac;
         c[i-1] = hh[i-1][i-1]/gamma;
         s[i-1] = hh[i][i-1]/gamma;
         rs[i] = -s[i-1]*rs[i-1];
         rs[i-1] = c[i-1]*rs[i-1];
         /* determine residual norm */
         hh[i-1][i-1] = c[i-1]*hh[i-1][i-1] + s[i-1]*hh[i][i-1];
         r_norm = fabs(rs[i]);
         if ( print_level>0 )
         {
            norms[iter] = r_norm;
            if ( print_level>1 && my_id == 0 )
            {
               if (b_norm > 0.0)
                  printf("% 5d    %e    %f   %e\n", iter, 
                         norms[iter],norms[iter]/norms[iter-1],
                         norms[iter]/b_norm);
               else
                  printf("% 5d    %e    %f\n", iter, norms[iter],
                         norms[iter]/norms[iter-1]);
            }
         }
         if (cf_tol > 0.0)
         {
            cf_ave_0 = cf_ave_1;
            cf_ave_1 = pow( r_norm / r_norm_0, 1.0/(2.0*iter));

            weight   = fabs(cf_ave_1 - cf_ave_0);
            weight   = weight / hypre_max(cf_ave_1, cf_ave_0);
            weight   = 1.0 - weight;
#if 0
            printf("I = %d: cf_new = %e, cf_old = %e, weight = %e\n",
                   i, cf_ave_1, cf_ave_0, weight );
#endif
            if (weight * cf_ave_1 > cf_tol) 
            {
               break_value = 1;
               break;
            }
         }

      }
      /* now compute solution, first solve upper triangular system */

      if (break_value) break;
	
      rs[i-1] = rs[i-1]/hh[i-1][i-1];
      for (k = i-2; k >= 0; k--)
      {
         t = rs[k];
         for (j = k+1; j < i; j++)
         {
            t -= hh[k][j]*rs[j];
         }
         rs[k] = t/hh[k][k];
      }
      /* w = sum( rs[j]*p[j], 0<=j<i ) */
      ierr += bHYPRE_Vector_Copy( w, p[0], _ex ); SIDL_CHECK(*_ex);
      ierr += bHYPRE_Vector_Scale( w, rs[0], _ex ); SIDL_CHECK(*_ex);
      for (j = 1; j < i; j++)
         ierr += bHYPRE_Vector_Axpy( w, rs[j], p[j], _ex ); SIDL_CHECK(*_ex);

      ierr += bHYPRE_Vector_Clear( r, _ex );  /* maybe not needed */
      SIDL_CHECK(*_ex);
      ierr += bHYPRE_Solver_Apply( precond, w, &r, _ex );  /* r = Cw */
      SIDL_CHECK(*_ex);

      ierr += bHYPRE_Vector_Axpy( *x, 1.0, r, _ex ); /* x = x + r = x + Cw */
      SIDL_CHECK(*_ex);
      /* note: w isn't used outside this section, except for workspace */

      /* check for convergence, evaluate actual residual */
      if (r_norm <= epsilon && iter >= min_iter) 
      {
         ierr += bHYPRE_Vector_Copy( r, b, _ex ); SIDL_CHECK(*_ex);
         /* r = r - Ax */
         ierr += bHYPRE_Operator_Apply( A, *x, &w, _ex ); /* w = Ax */
         SIDL_CHECK(*_ex);
         ierr += bHYPRE_Vector_Axpy( r, -1.0, w, _ex );   /* r = r - w = r - Ax */
         SIDL_CHECK(*_ex);
         ierr += bHYPRE_Vector_Dot( r, r, &r_norm, _ex ); SIDL_CHECK(*_ex);
         r_norm = sqrt( r_norm );    /* r_norm = L2 norm of r */
         if (r_norm <= epsilon)
         {
            if ( print_level>1 && my_id == 0 )
            {
               printf("\n\n");
               printf("Final L2 norm of residual: %e\n\n", r_norm);
            }
            if (rel_change && r_norm > guard_zero_residual)
               /* Also test on relative change of iterates, x_i - x_(i-1) */
            {  /* At this point r = x_i - x_(i-1) */
               ierr += bHYPRE_Vector_Dot( *x, *x, &x_norm, _ex ); SIDL_CHECK(*_ex);
               x_norm = sqrt( x_norm );    /* x_norm = L2 norm of x */
               if ( x_norm<=guard_zero_residual ) break; /* don't divide by 0 */
               if ( r_norm/x_norm < epsilon )
               {
                  data -> converged = 1;
                  break;
               }
            }
            else
            {
               data -> converged = 1;
               break;
            }
         }
         else 
         {
            if ( print_level>0 && my_id == 0)
               printf("false convergence 2\n");
            ierr += bHYPRE_Vector_Copy( p[0], r, _ex ); SIDL_CHECK(*_ex);
            i = 0;
         }
      }

/* compute residual vector and continue loop */

      for (j=i ; j > 0; j--)
      {
         rs[j-1] = -s[j-1]*rs[j];
         rs[j] = c[j-1]*rs[j];
      }

      if ( i )
         ierr += bHYPRE_Vector_Scale( p[0], rs[0], _ex ); SIDL_CHECK(*_ex);
      for (j=1; j < i+1; j++)
         ierr += bHYPRE_Vector_Axpy( p[0], rs[j], p[j], _ex ); SIDL_CHECK(*_ex);
   }

   if ( print_level>1 && my_id == 0 )
      printf("\n\n"); 

   data -> num_iterations = iter;
   if (b_norm > 0.0)
      data -> rel_residual_norm = r_norm/b_norm;
   if (b_norm == 0.0)
      data -> rel_residual_norm = r_norm;

   if (iter >= max_iter && r_norm > epsilon) ierr = 1;

   hypre_TFree(c); 
   hypre_TFree(s); 
   hypre_TFree(rs);
 
   for (i=0; i < k_dim+1; i++)
   {	
      hypre_TFree(hh[i]);
   }
   hypre_TFree(hh); 

   return ierr;

   hypre_babel_exception_return_error(_ex);
    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.Apply) */
  }
}

/*
 * Apply the adjoint of the operator to {\tt b}, returning {\tt x}.
 */

#undef __FUNC__
#define __FUNC__ "impl_bHYPRE_GMRES_ApplyAdjoint"

#ifdef __cplusplus
extern "C"
#endif
int32_t
impl_bHYPRE_GMRES_ApplyAdjoint(
  /* in */ bHYPRE_GMRES self,
  /* in */ bHYPRE_Vector b,
  /* inout */ bHYPRE_Vector* x,
  /* out */ sidl_BaseInterface *_ex)
{
  *_ex = 0;
  {
    /* DO-NOT-DELETE splicer.begin(bHYPRE.GMRES.ApplyAdjoint) */
  /* Insert-Code-Here {bHYPRE.GMRES.ApplyAdjoint} (ApplyAdjoint method) */

   return 1; /* not implemented */

    /* DO-NOT-DELETE splicer.end(bHYPRE.GMRES.ApplyAdjoint) */
  }
}
/* Babel internal methods, Users should not edit below this line. */
struct bHYPRE_GMRES__object* impl_bHYPRE_GMRES_fconnect_bHYPRE_GMRES(const 
  char* url, sidl_bool ar, sidl_BaseInterface *_ex) {
  return bHYPRE_GMRES__connectI(url, ar, _ex);
}
struct bHYPRE_GMRES__object* impl_bHYPRE_GMRES_fcast_bHYPRE_GMRES(void* bi, 
  sidl_BaseInterface* _ex) {
  return bHYPRE_GMRES__cast(bi, _ex);
}
struct bHYPRE_MPICommunicator__object* 
  impl_bHYPRE_GMRES_fconnect_bHYPRE_MPICommunicator(const char* url, sidl_bool 
  ar, sidl_BaseInterface *_ex) {
  return bHYPRE_MPICommunicator__connectI(url, ar, _ex);
}
struct bHYPRE_MPICommunicator__object* 
  impl_bHYPRE_GMRES_fcast_bHYPRE_MPICommunicator(void* bi, sidl_BaseInterface* 
  _ex) {
  return bHYPRE_MPICommunicator__cast(bi, _ex);
}
struct bHYPRE_Operator__object* impl_bHYPRE_GMRES_fconnect_bHYPRE_Operator(
  const char* url, sidl_bool ar, sidl_BaseInterface *_ex) {
  return bHYPRE_Operator__connectI(url, ar, _ex);
}
struct bHYPRE_Operator__object* impl_bHYPRE_GMRES_fcast_bHYPRE_Operator(void* 
  bi, sidl_BaseInterface* _ex) {
  return bHYPRE_Operator__cast(bi, _ex);
}
struct bHYPRE_PreconditionedSolver__object* 
  impl_bHYPRE_GMRES_fconnect_bHYPRE_PreconditionedSolver(const char* url, 
  sidl_bool ar, sidl_BaseInterface *_ex) {
  return bHYPRE_PreconditionedSolver__connectI(url, ar, _ex);
}
struct bHYPRE_PreconditionedSolver__object* 
  impl_bHYPRE_GMRES_fcast_bHYPRE_PreconditionedSolver(void* bi, 
  sidl_BaseInterface* _ex) {
  return bHYPRE_PreconditionedSolver__cast(bi, _ex);
}
struct bHYPRE_Solver__object* impl_bHYPRE_GMRES_fconnect_bHYPRE_Solver(const 
  char* url, sidl_bool ar, sidl_BaseInterface *_ex) {
  return bHYPRE_Solver__connectI(url, ar, _ex);
}
struct bHYPRE_Solver__object* impl_bHYPRE_GMRES_fcast_bHYPRE_Solver(void* bi, 
  sidl_BaseInterface* _ex) {
  return bHYPRE_Solver__cast(bi, _ex);
}
struct bHYPRE_Vector__object* impl_bHYPRE_GMRES_fconnect_bHYPRE_Vector(const 
  char* url, sidl_bool ar, sidl_BaseInterface *_ex) {
  return bHYPRE_Vector__connectI(url, ar, _ex);
}
struct bHYPRE_Vector__object* impl_bHYPRE_GMRES_fcast_bHYPRE_Vector(void* bi, 
  sidl_BaseInterface* _ex) {
  return bHYPRE_Vector__cast(bi, _ex);
}
struct sidl_BaseClass__object* impl_bHYPRE_GMRES_fconnect_sidl_BaseClass(const 
  char* url, sidl_bool ar, sidl_BaseInterface *_ex) {
  return sidl_BaseClass__connectI(url, ar, _ex);
}
struct sidl_BaseClass__object* impl_bHYPRE_GMRES_fcast_sidl_BaseClass(void* bi, 
  sidl_BaseInterface* _ex) {
  return sidl_BaseClass__cast(bi, _ex);
}
struct sidl_BaseInterface__object* 
  impl_bHYPRE_GMRES_fconnect_sidl_BaseInterface(const char* url, sidl_bool ar, 
  sidl_BaseInterface *_ex) {
  return sidl_BaseInterface__connectI(url, ar, _ex);
}
struct sidl_BaseInterface__object* impl_bHYPRE_GMRES_fcast_sidl_BaseInterface(
  void* bi, sidl_BaseInterface* _ex) {
  return sidl_BaseInterface__cast(bi, _ex);
}
struct sidl_ClassInfo__object* impl_bHYPRE_GMRES_fconnect_sidl_ClassInfo(const 
  char* url, sidl_bool ar, sidl_BaseInterface *_ex) {
  return sidl_ClassInfo__connectI(url, ar, _ex);
}
struct sidl_ClassInfo__object* impl_bHYPRE_GMRES_fcast_sidl_ClassInfo(void* bi, 
  sidl_BaseInterface* _ex) {
  return sidl_ClassInfo__cast(bi, _ex);
}
struct sidl_RuntimeException__object* 
  impl_bHYPRE_GMRES_fconnect_sidl_RuntimeException(const char* url, sidl_bool 
  ar, sidl_BaseInterface *_ex) {
  return sidl_RuntimeException__connectI(url, ar, _ex);
}
struct sidl_RuntimeException__object* 
  impl_bHYPRE_GMRES_fcast_sidl_RuntimeException(void* bi, sidl_BaseInterface* 
  _ex) {
  return sidl_RuntimeException__cast(bi, _ex);
}

