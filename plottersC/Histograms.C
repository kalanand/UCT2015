// $Id: Histograms.C,v 1.1 2012/11/15 21:09:46 aosorio Exp $
// Include files 



// local
#include "Histograms.h"

//-----------------------------------------------------------------------------
// Implementation file for class : Histograms
//
// All histograms can go here
//
// 2012-11-14 : Andres Osorio
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Histograms::Histograms(  ) {

  int mbins  = 20;
  float minx = 0.0;
  float maxx = 100.0;
  
  //... Book histograms
  m_histograms1D["pt"] =  new TH1F("pt","pt plot", mbins, minx, maxx);
  m_histograms1D["pt_regId"] =  new TH1F("pt_regId","pt plot", mbins, minx, maxx);
  m_histograms1D["pt_regId_iso"] =  new TH1F("pt_regId_iso","pt plot", mbins, minx, maxx);
  
  //Just for some understanding
  m_histograms1D["isoCutVar1"] = new TH1F("isoCutVar1","Var1=(jetPt[0]-regionPt[0])/regionPt[0]", 50, -10.0, 10.0);
  m_histograms1D["isoCutVar2"] = new TH1F("isoCutVar2","Var2=(jetPt[0]-pt[0])/pt[0]", 50, -10.0,10.0);
  m_histograms1D["ellIsolation"] = new TH1F("ellIsolation","L-isolation bit", 10, 0.0,10.0);
  m_histograms2D["isoCutVar1Var2"] = new TH2F("isoCutVar1Var2","x=Var1 ; y=Var2", 50, -10.0, 20.0, 50, -10.0, 20.0);
  
}
//=============================================================================
// Destructor
//=============================================================================
Histograms::~Histograms() {} 

//=============================================================================
