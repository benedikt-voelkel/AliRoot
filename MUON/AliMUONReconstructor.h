#ifndef ALIMUONRECONSTRUCTOR_H
#define ALIMUONRECONSTRUCTOR_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
* See cxx source for full Copyright notice                               */

// $Id$

/// \ingroup rec
/// \class AliMUONReconstructor
/// \brief Implementation of AliReconstructor for MUON (both tracker and trigger)
/// 
// Author Laurent Aphecetche, Subatech

#ifndef ALIRECONSTRUCTOR_H
#  include "AliReconstructor.h"
#endif

class AliMUONCalibrationData;
class AliMUONDigitCalibrator;
class AliMUONDigitMaker;
class AliMUONGeometryTransformer;
class AliMUONRecoParam;
class AliMUONTracker;
class AliMUONTriggerCircuit;
class AliMUONVClusterFinder;
class AliMUONVClusterServer;
class AliMUONVClusterStore;
class AliMUONVDigitStore;
class AliMUONVTrackStore;
class AliMUONVTriggerStore;
class AliMUONVTriggerStore;
class TClonesArray;

class AliMUONReconstructor : public AliReconstructor
{
public:
  AliMUONReconstructor();
  virtual ~AliMUONReconstructor();
  
  virtual Bool_t HasDigitConversion() const;

  virtual void ConvertDigits(AliRawReader* rawReader, TTree* digitsTree) const;
  
  virtual void Reconstruct(AliRawReader* rawReader, TTree* clustersTree) const;
  
  virtual void Reconstruct(TTree* digitsTree, TTree* clustersTree) const;
  
  virtual AliTracker* CreateTracker() const;
  
  static const AliMUONRecoParam* GetRecoParam();
  
  static AliMUONVClusterFinder* CreateClusterFinder(const char* clusterFinderType);

private:
  /// Not implemented
  AliMUONReconstructor(const AliMUONReconstructor&);
  /// Not implemented
  AliMUONReconstructor& operator=(const AliMUONReconstructor&);
  
  void ConvertDigits(AliRawReader* rawReader, 
                     AliMUONVDigitStore* digitStore,
                     AliMUONVTriggerStore* triggerStore) const;
  void Calibrate(AliMUONVDigitStore& digitStore) const;
  void CreateCalibrator() const;
  void CreateDigitMaker() const;
  void CreateTriggerCircuit() const;
  void CreateClusterServer() const;
  void FillTreeR(AliMUONVTriggerStore* triggerStore,
                 TTree& clustersTree) const;
  
  AliMUONVDigitStore* DigitStore() const;
  AliMUONVTriggerStore* TriggerStore() const;
  
private:

  mutable AliMUONDigitMaker* fDigitMaker; //!< Raw to Digits converter
  AliMUONGeometryTransformer* fTransformer; //!< Geometry transformer (local<->global)
  mutable AliMUONVDigitStore* fDigitStore; //!< Digit container
  mutable AliMUONTriggerCircuit* fTriggerCircuit; //!< Trigger Circuit
  mutable AliMUONCalibrationData* fCalibrationData; //!< Calibration data
  mutable AliMUONDigitCalibrator* fDigitCalibrator; //!<  Digit to calibrate digit converter
  mutable AliMUONVClusterServer* fClusterServer; //!<  Clusterizer
  mutable AliMUONVTriggerStore* fTriggerStore; //!< Trigger container
  mutable AliMUONVTrackStore* fTrackStore; //!< Track container
  mutable AliMUONVClusterStore* fClusterStore; //!< cluster store (when not in combined tracking mode)
  
  static AliMUONRecoParam* fgRecoParam; //!< parameters used to tune the MUON reconstruction
    
  ClassDef(AliMUONReconstructor,7) // Implementation of AliReconstructor
};

#endif
