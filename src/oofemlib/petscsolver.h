/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2011   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef petscsolver_h
#define petscsolver_h

#ifndef __MAKEDEPEND
 #include <stdio.h>
#endif
#include "sparselinsystemnm.h"
#include "sparsemtrx.h"
#include "petscsparsemtrx.h"
#include "flotarry.h"

#ifdef __PETSC_MODULE
 #ifndef __MAKEDEPEND
  #include <petscksp.h>
 #endif
#endif

namespace oofem {
class Domain;
class EngngModel;
class FloatMatrix;

/**
 * Implements the solution of linear system of equation in the form @f$A\cdot x=b@f$ using solvers
 * from PETSc library. Only works with the PETSc sparse matrix implementation.
 */
class PetscSolver : public SparseLinearSystemNM
{
private:
#ifdef __PETSC_MODULE
    /// Last mapped Lhs matrix
    //PetscSparseMtrx *Lhs;
    /// Last mapped matrix version.
    //SparseMtrx :: SparseMtrxVersionType lhsVersion;

    /// Linear solver context.
    //KSP ksp;
    /// Flag if context initialized.
    //bool kspInit;

#endif

public:
    /**
     * Constructor.
     * @param i Solver number.
     * @param d Domain which solver belongs to.
     * @param m Engineering model which solver belongs to.
     */
    PetscSolver(int i, Domain *d, EngngModel *m);

    /// Destructor.
    ~PetscSolver();

    NM_Status solve(SparseMtrx *A, FloatArray *b, FloatArray *x);
//#ifndef __PARALLEL_MODE
#if 0
    NM_Status solve(SparseMtrx *A, FloatMatrix &B, FloatMatrix &X);
#endif
#ifdef __PETSC_MODULE
    /**
     * Solves the given linear system.
     * @param A Coefficient matrix.
     * @param b Right hand side (PETSC Vec(tor)).
     * @param x Solution array(PETSC Vec(tor)).
     * @return NM_Status value.
     */
    NM_Status petsc_solve(PetscSparseMtrx *A, Vec b, Vec x);
#endif

    /// Initializes receiver from given record. Empty implementation.
    IRResultType initializeFrom(InputRecord *ir);
    void reinitialize();

    // Identification
    const char *giveClassName() const { return "PetscSolver"; }
    classType giveClassID() const { return PetscSolverClass; }
    LinSystSolverType giveLinSystSolverType() const { return ST_Petsc; }
};
} // end namespace oofem
#endif // petscsolver_h
