#ifndef ALIITSRECONSTRUCTOR_H
#define ALIITSRECONSTRUCTOR_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// class for ITS reconstruction                                              //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "AliReconstructor.h"
#include "AliITSRecoParam.h"
#include "AliITSDetTypeRec.h"
#include "AliITSRecPointContainer.h"
#include <TVectorF.h>
class AliESDpid;
class AliITSgeom;
class AliTracker;
class AliTrackleter;
class AliITStrackerMI;


class AliITSReconstructor: public AliReconstructor {
public:
  AliITSReconstructor();
  virtual ~AliITSReconstructor();
  virtual void         Init();
  virtual void         GetPidSettings(AliESDpid *ESDpid);
  virtual void         Reconstruct(AliRawReader* rawReader, TTree* clustersTree) const;
  virtual void         Reconstruct(TTree* digitsTree, TTree* clustersTree) const;

  virtual AliTracker*  CreateTracker() const;
  virtual AliVertexer* CreateVertexer() const;
  virtual AliTrackleter* CreateMultFinder() const;

  virtual void         FillESD(TTree* /*digitsTree*/, TTree* clustersTree, 
			       AliESDEvent* /* esd */) const; 
  virtual void         FillESD(AliRawReader* /*rawReader*/, TTree* clustersTree, 
			       AliESDEvent* esd) const
  {FillESD((TTree*)NULL, clustersTree, esd);}
  virtual void Terminate() const {AliITSRecPointContainer::Destroy();}

  static const AliITSRecoParam* GetRecoParam() { return dynamic_cast<const AliITSRecoParam*>(AliReconstructor::GetRecoParam(0)); }

  static void   SetCheckInvariant(Bool_t v) {fgkCheckInvariant = v;}
  static Bool_t GetCheckInvariant()         {return fgkCheckInvariant;}

  static TVectorF* GetExtraErrorY2() {return fgExtraErrorY2;}
  static TVectorF* GetExtraErrorZ2() {return fgExtraErrorZ2;}  
  static void      SetExtraErrorY2(TVectorF* v) {fgExtraErrorY2=v;}
  static void      SetExtraErrorZ2(TVectorF* v) {fgExtraErrorZ2=v;}  
  
private:
  AliITSReconstructor(const AliITSReconstructor &); //Not implemented
  AliITSReconstructor& operator=(const AliITSReconstructor &); //Not implemented

  //data
  AliITSDetTypeRec       *fDetTypeRec;  // reconstructor

  static Bool_t fgkCheckInvariant;   // allow or forbid AliITStrackV2::CheckInvariant

  static TVectorF* fgExtraErrorY2;   // additional errors^2 in Y
  static TVectorF* fgExtraErrorZ2;   // additional errirs^2 in Z
  
  ClassDef(AliITSReconstructor, 6)   // class for the ITS reconstruction
};

#endif
