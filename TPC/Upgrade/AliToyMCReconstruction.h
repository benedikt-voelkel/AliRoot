#ifndef AliToyMCReconstruction_H
#define AliToyMCReconstruction_H

#include <TObject.h>

class TTree;

class TTreeSRedirector;
class AliExternalTrackParam;
class AliTPCtrackerSector;
class AliToyMCEvent;

class AliToyMCReconstruction : public TObject {
public:
  AliToyMCReconstruction();
  virtual ~AliToyMCReconstruction();
  
  enum ECorrType {
    kNoCorrection = 0,
    kTPCCenter,
    kAverageEta,
    kIdeal
  };

  void RunReco(const char* file, Int_t nmaxEv=-1);
  void RunRecoAllClusters(const char* file, Int_t nmaxEv=-1);
  void RunRecoAllClustersStandardTracking(const char* file, Int_t nmaxEv=-1);
  
  // reconstruction settings
  void      SetRecoSettings(Bool_t idealTracking, Int_t clusterType, ECorrType correctionType, Int_t seedingRow=140, Int_t seedingDist=10)
                           { fIdealTracking=idealTracking; fClusterType=clusterType; fSeedingRow=seedingRow, fSeedingDist=seedingDist, fCorrectionType=correctionType; }
  
  void      SetClusterType(Int_t type)  { fClusterType = type;    }
  Int_t     GetClusterType()  const     { return fClusterType;    }
  
  void      SetSeedingRow(Int_t row)    { fSeedingRow = row;      }
  Int_t     GetSeedingRow()  const      { return fSeedingRow;     }
  
  void      SetSeedingDist(Int_t dist)  { fSeedingDist = dist;    }
  Int_t     GetSeedingDist()  const     { return fSeedingDist;    }
  
  void      SetCorrType(ECorrType type) { fCorrectionType = type; }
  ECorrType GetCorrectionType() const   { return fCorrectionType; }

  void   SetUseMaterialBudget(Bool_t mat) { fUseMaterial = mat;   }
  Bool_t GetUseMaterialBudget() const   { return fUseMaterial;    }

  void   SetIdealTracking(Bool_t tr)    { fIdealTracking = tr;    }
  Bool_t GetIdealTracking()  const      { return fIdealTracking;  }
  
  void   SetTree(TTree *tree) { fTree=tree; }
  TTree* GetTree() const { return fTree; }

  AliExternalTrackParam* GetSeedFromTrack(const AliToyMCTrack * const tr);
  AliExternalTrackParam* GetFittedTrackFromSeed(const AliToyMCTrack *tr, const AliExternalTrackParam *seed);
  AliExternalTrackParam* GetFittedTrackFromSeedAllClusters(const AliToyMCTrack *tr, const AliExternalTrackParam *seed, Int_t &nClus);
  
  void InitSpaceCharge();

  static TTree* ConnectTrees(const char* files);
  
  Double_t GetVDrift() const;
  Double_t GetZLength(Int_t roc) const;


private:
  AliToyMCReconstruction(const AliToyMCReconstruction &rec);
  AliToyMCReconstruction& operator= (AliToyMCReconstruction& rec);

  void SetTrackPointFromCluster(const AliTPCclusterMI *cl, AliTrackPoint &p);
  void ClusterToSpacePoint(const AliTPCclusterMI *cl, Float_t xyz[3]);

  Int_t LoadInnerSectors();
  Int_t LoadOuterSectors();
  
  Int_t GetSector(AliExternalTrackParam *track);
  void FillSectorStructure(Int_t maxev);
  
  // reco settings
  Int_t  fSeedingRow;            // first row used for seeding
  Int_t  fSeedingDist;           // distance of seeds
  Int_t  fClusterType;           // cluster type to use
  ECorrType fCorrectionType;     // type of space point correction
  Bool_t fDoTrackFit;            // do track fitting
  Bool_t fUseMaterial;           // use material budget in tracking
  Bool_t fIdealTracking;         // use ideal coordinates for tracking

  // current reconstruction info
  Double_t fTime0;               // current time0 used for reconstruction
  Bool_t   fCreateT0seed;        // if current seed is the T0 seed
  
  TTreeSRedirector *fStreamer;   // debug streamer
  TTree *fTree;                  // input tree with ToyMC info
  AliToyMCEvent *fEvent;         // input event

  AliTPCParam *fTPCParam;            // tpc reco parameters
  AliTPCSpaceCharge3D *fSpaceCharge; // space charge 

   const Int_t fkNSectorInner;        //number of inner sectors
   AliTPCtrackerSector *fInnerSectorArray;  //array of inner sectors;
   const Int_t fkNSectorOuter;        //number of outer sectors
   AliTPCtrackerSector *fOuterSectorArray;  //array of outer sectors;
  
  ClassDef(AliToyMCReconstruction,0)
};


#endif
