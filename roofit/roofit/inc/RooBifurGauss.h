/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooBifurGauss.h,v 1.12 2007/07/12 20:30:49 wouter Exp $
 * Authors:                                                                  *
 *   Abi Soffer, Colorado State University, abi@slac.stanford.edu            *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California,         *
 *                          Colorado State University                        *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_BIFUR_GAUSS
#define ROO_BIFUR_GAUSS

#include <RooAbsPdf.h>
#include <RooRealProxy.h>

class RooBifurGauss : public RooAbsPdf {
public:
   RooBifurGauss() {}
   RooBifurGauss(const char *name, const char *title, RooAbsReal &_x, RooAbsReal &_mean, RooAbsReal &_sigmaL,
                 RooAbsReal &_sigmaR);

   RooBifurGauss(const RooBifurGauss &other, const char *name = nullptr);
   TObject *clone(const char *newname) const override { return new RooBifurGauss(*this, newname); }

   Int_t getAnalyticalIntegral(RooArgSet &allVars, RooArgSet &analVars, const char *rangeName = nullptr) const override;
   double analyticalIntegral(Int_t code, const char *rangeName = nullptr) const override;

  /// Get the x variable.
  RooAbsReal const& getX() const { return x.arg(); }

  /// Get the mean parameter.
  RooAbsReal const& getMean() const { return mean.arg(); }

  /// Get the left sigma parameter.
  RooAbsReal const& getSigmaL() const { return sigmaL.arg(); }

  /// Get the right sigma parameter.
  RooAbsReal const& getSigmaR() const { return sigmaR.arg(); }

protected:
   RooRealProxy x;
   RooRealProxy mean;
   RooRealProxy sigmaL;
   RooRealProxy sigmaR;

   double evaluate() const override;
   void doEval(RooFit::EvalContext &) const override;
   inline bool canComputeBatchWithCuda() const override { return true; }

private:
   ClassDefOverride(RooBifurGauss, 1) // Bifurcated Gaussian PDF
};

#endif
