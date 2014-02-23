#define L1RateTree_cxx
#include "L1RateTree.h"

void L1RateTree::Loop()
{

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "data nentries: " << nentries << std::endl;

  Long64_t nbytes = 0, nb = 0;

  m_debug = false;
  L1_CALIB_FACTOR = 1.0;
  m_ptCut = 0.0;

  m_output = new Histograms();

  int fillOne = 0;
  int fillTwo = 0;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    float max_pt = pt->at(0);
    
    //only one entry per event
    if( max_pt > m_ptCut ) {
      m_output->m_histograms1D["pt"]->Fill( max_pt );
      ++fillOne;
    }
    else {
      m_output->m_histograms1D["pt"]->Fill( 0 );
      ++fillTwo;
    }    
    
  }
    
  if (m_debug) {
    std::cout << " fillOne: "   << fillOne << std::endl;
    std::cout << " fillTwo: "   << fillTwo << std::endl;
    std::cout << "     Sum: "   << (fillOne+fillTwo) << std::endl;
    std::cout << "L1 entries: " << m_output->m_histograms1D["pt"]->GetEntries() << std::endl;
  }
  
  m_output->m_histograms1D["pt"]->Scale( L1_CALIB_FACTOR );
  
  h_rate = Make_l1_rate( m_output->m_histograms1D["pt"] );
  
  h_rate->SetLineColor(kRed);
  h_rate->SetMarkerStyle(20);
  h_rate->SetMarkerColor(kRed);
  
  h_rate->Draw();
}


TH1F *  L1RateTree::Make_l1_rate(TH1F * h_in) {

  // This is same as it is done in the Wisconsin scripts
  
  int numBins = h_in->GetNbinsX();
  TH1F * h_out = (TH1F*)h_in->Clone();
  
  for (int i = 0; i < numBins; ++i)
    h_out->SetBinContent(i+1, h_in->Integral(i+1, numBins));
  
  return h_out;
  
}

