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
 *               Copyright (C) 1993 - 2013   Borek Patzak
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

#ifndef quad1_ht_h
#define quad1_ht_h

#include "transportelement.h"
#include "spatiallocalizer.h"
#include "zznodalrecoverymodel.h"
#include "fei2dquadlin.h"

#define _IFT_Quad1_ht_Name "quad1ht"
#define _IFT_Quad1_hmt_Name "quad1hmt"
#define _IFT_Quad1_mt_Name "quad1mt"

namespace oofem {
/**
 * Quadratic (2d) element with linear approximation for heat transfer.
 */
class Quad1_ht : public TransportElement, public SpatialLocalizerInterface, public ZZNodalRecoveryModelInterface
{
protected:
    int numberOfGaussPoints;
    static FEI2dQuadLin interpolation;

public:
    Quad1_ht(int n, Domain *d);
    virtual ~Quad1_ht();

    virtual double computeVolumeAround(GaussPoint *gp);

    virtual const char *giveInputRecordName() const { return _IFT_Quad1_ht_Name; }
    virtual const char *giveClassName() const { return "Quad1_ht"; }
    virtual classType giveClassID() const { return Quad1_htClass; }

    //    virtual int computeNumberOfDofs(EquationID ut) { return ( emode == HeatTransferEM ) ? 4 : 8; }    
    virtual int computeNumberOfDofs(EquationID ut) { return 4; }
    virtual IRResultType initializeFrom(InputRecord *ir);
    virtual FEInterpolation *giveInterpolation() const { return & interpolation; }
    virtual MaterialMode giveMaterialMode() { return _2dHeat; }

    virtual Interface *giveInterface(InterfaceType t);

    virtual Element *ZZNodalRecoveryMI_giveElement() { return this; }

    virtual Element *SpatialLocalizerI_giveElement() { return this; }
    virtual int SpatialLocalizerI_containsPoint(const FloatArray &coords);
    virtual double SpatialLocalizerI_giveDistanceFromParametricCenter(const FloatArray &coords);

#ifdef __OOFEG
    // Graphics output
    void drawRawGeometry(oofegGraphicContext &);
    virtual void drawScalar(oofegGraphicContext &context);
    //void drawYourself(oofegGraphicContext&);
    //virtual void drawRawGeometry(oofegGraphicContext&) {}
    //virtual void drawDeformedGeometry(oofegGraphicContext&, UnknownType) {}
#endif

protected:
    virtual void computeGaussPoints();
    virtual double computeEdgeVolumeAround(GaussPoint *gp, int iEdge);
};

/**
 * Class for heat and mass transfer.
 */
class Quad1_hmt : public Quad1_ht
{
public:
    Quad1_hmt(int n, Domain *d);

    virtual const char *giveInputRecordName() const { return _IFT_Quad1_hmt_Name; }
    virtual const char *giveClassName() const { return "Quad1_hmt"; }
    virtual classType giveClassID() const { return Quad1_hmtClass; }
    virtual int computeNumberOfDofs(EquationID ut) { return 8; }
    virtual MaterialMode giveMaterialMode() { return _2dHeMo; }
};

/**
 * Class for mass transfer.
 */
class Quad1_mt : public Quad1_ht
{
public:
    Quad1_mt(int n, Domain *d);

    virtual const char *giveInputRecordName() const { return _IFT_Quad1_mt_Name; }
    virtual const char *giveClassName() const { return "Quad1_mt"; }
    virtual classType giveClassID() const { return Quad1_mtClass; }
    virtual int computeNumberOfDofs(EquationID ut) { return 4; }
    virtual MaterialMode giveMaterialMode() { return _2dHeat; }
};
} // end namespace oofem
#endif // quad1_ht_h
