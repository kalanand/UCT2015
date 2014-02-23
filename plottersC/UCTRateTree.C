#define UCTRateTree_cxx
#include "UCTRateTree.h"
#include <TPaveStats.h>

void UCTRateTree::Loop()
{

  if (fChain == 0) return;
  
  m_debug = false;

  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "data nentries: " << nentries << std::endl;

  Long64_t nbytes = 0, nb = 0;

  TStyle * uctStyle = new TStyle();
  
  L1G_CALIB_FACTOR = 1.0;
  m_ptCut = 0.0;
  
  //...Booking of histograms
  m_output = new Histograms();
  //uctStyle->SetOptStat(0);
  uctStyle->cd();

  std::vector<float> v_sel_pt;
  std::vector<float> v_sel_pt_iso;
  
  int regId_counter = 0;
  int iso_counter = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    
    nb = fChain->GetEntry(jentry);   nbytes += nb;
  
    //--- 1.0 EG (e/gamma/taus)
    float max_pt = *std::max_element(pt->begin(), pt->end());
    
    if( max_pt > m_ptCut ) {
      m_output->m_histograms1D["pt"]->Fill( max_pt );
    } else {
      m_output->m_histograms1D["pt"]->Fill( 0 );
    }
    
    //... bits for regional Id & isolation
    bool regionalId = false;
    bool isoCut = false;
    
    int n_objects = pt->size();
    
    for(int k=0; k < n_objects; ++k) {
      
      float isoCutVar1 = (jetPt->at(k) - regionPt->at(k)) / regionPt->at(k);
      float isoCutVar2 = (jetPt->at(k) - pt->at(k)) / pt->at(k);
      
      regionalId = (!(tauVeto->at(k)) && !( mipBit->at(k)));
      
      if( regionalId ) {
        v_sel_pt.push_back( pt->at(k) );
        ++regId_counter;

        m_output->m_histograms2D["isoCutVar1Var2"]->Fill( isoCutVar1, isoCutVar2 );
	m_output->m_histograms1D["isoCutVar1"]->Fill( isoCutVar1 );
        m_output->m_histograms1D["isoCutVar2"]->Fill( isoCutVar2 );
	m_output->m_histograms1D["ellIsolation"]->Fill( ellIso->at(k) );
	
      }
      
      bool ellIsolation = ellIso->at(k);
      
      isoCut = ( regionalId && ellIsolation );
      
      if( regionalId && isoCut ) { 
        v_sel_pt_iso.push_back( pt->at(k) );
        ++iso_counter;
      }
      
    }//<
    
    //--- 2.0 EG regionalId
    
    if( v_sel_pt.size() != 0 ) {
      max_pt = *std::max_element(v_sel_pt.begin(), v_sel_pt.end() );
      m_output->m_histograms1D["pt_regId"]->Fill( max_pt );
    } else {
      m_output->m_histograms1D["pt_regId"]->Fill( 0 );
    }
    
    //3.0 EG regionalId + Iso
    
    if( v_sel_pt_iso.size() != 0 ) {
      max_pt = *std::max_element(v_sel_pt_iso.begin(), v_sel_pt_iso.end() );
      m_output->m_histograms1D["pt_regId_iso"]->Fill( max_pt );
    } else {
      m_output->m_histograms1D["pt_regId_iso"]->Fill( 0 );
    }
    
    v_sel_pt.clear();
    v_sel_pt_iso.clear();
    
  }
    
  m_output->m_histograms1D["pt"]->Scale( L1G_CALIB_FACTOR );
  m_output->m_histograms1D["pt_regId"]->Scale( L1G_CALIB_FACTOR );
  m_output->m_histograms1D["pt_regId_iso"]->Scale( L1G_CALIB_FACTOR );
  
  //Now do counts -> rates
  h_rate= Make_l1_rate( m_output->m_histograms1D["pt"] );
  
  h_rate->SetLineColor(kBlack);
  h_rate->SetMarkerStyle(22);
  h_rate->SetMarkerColor(kBlack);
  
  h_rate_regId = Make_l1_rate( m_output->m_histograms1D["pt_regId"] );
  
  h_rate_regId->SetLineColor(kGreen);
  h_rate_regId->SetMarkerStyle(22);
  h_rate_regId->SetMarkerColor(kGreen);
  
  h_rate_regId_Iso = Make_l1_rate( m_output->m_histograms1D["pt_regId_iso"] );
  
  h_rate_regId_Iso->SetLineColor(kBlue);
  h_rate_regId_Iso->SetMarkerStyle(22);
  h_rate_regId_Iso->SetMarkerColor(kBlue);
  
  if( m_debug ) {

    std::cout << " pt: " << m_output->m_histograms1D["pt"]->GetEntries() << std::endl;
    std::cout << " pt&regionId: " << m_output->m_histograms1D["pt_regId"]->GetEntries() << std::endl;
    std::cout << " pt&regionId&Iso: " << m_output->m_histograms1D["pt_regId_iso"]->GetEntries() << std::endl;
    std::cout << " h_rate: " << h_rate->GetEntries() << std::endl;
    std::cout << " h_rate_regId: " << h_rate_regId->GetEntries() << std::endl;
    std::cout << " h_rate_regId_iso: " << h_rate_regId_Iso->GetEntries() << std::endl;
    
    TCanvas * c1 = new TCanvas ("c1","c1 plot",800,600);
    c1->SetFillColor(10);
    c1->Divide(2,2);
    
    c1->cd(1);
    m_output->m_histograms1D["isoCutVar1"]->Draw();
    c1->cd(2);
    m_output->m_histograms1D["isoCutVar2"]->Draw();
    c1->cd(3);
    m_output->m_histograms2D["isoCutVar1Var2"]->Draw();
    c1->cd(4);
    m_output->m_histograms1D["ellIsolation"]->Draw();
    
  }
  
}

void UCTRateTree::CombineL1UCT( TH1F * l1Rate ) {
  
  m_canvas = new TCanvas("L1UCTrates", "L1 and UCT rates", 800, 600);
  
  m_canvas->cd();
  m_canvas->SetLogy();
  m_canvas->SetFillColor(10);

  TH1F * uct_rate = h_rate_regId_Iso;
  
  //Get the stat boxes of both histograms
  uct_rate->Draw();
  m_canvas->Update();
    
  TPaveStats *ps1 = (TPaveStats*)gPad->GetPrimitive("stats");
  ps1->SetName("statsh1");
  ps1->SetTextColor(kBlue);
  ps1->SetFillColor(10);
  
  l1Rate->Draw();
  m_canvas->Update();

  TPaveStats *ps2 = (TPaveStats*)gPad->GetPrimitive("stats");
  ps2->SetName("statsh2");
  ps2->SetFillColor(10);
  ps2->SetTextColor(kRed);
  ps2->SetX1NDC( ps1->GetX1NDC() ); 
  ps2->SetX2NDC( ps1->GetX2NDC() );
  ps2->SetY1NDC( ps1->GetY1NDC() - 0.20 ); 
  ps2->SetY2NDC( ps1->GetY2NDC() - 0.20 );

  uct_rate->SetName("UCT");
  l1Rate->SetName("L1");

  m_canvas->Update();

  uct_rate->SetTitle("EG Rate");
  uct_rate->GetXaxis()->SetTitle("L1 p_{T} (GeV)");
  uct_rate->GetXaxis()->CenterTitle(true);
  uct_rate->GetXaxis()->SetTitleOffset(1.2);
  uct_rate->SetMinimum(10);
  
  uct_rate->SetLineColor(kBlue);
  uct_rate->SetMarkerStyle(22);
  uct_rate->SetMarkerColor(kBlue);
  
  uct_rate->Draw("ph");
  
  l1Rate->Draw("phsame");
  
  uct_rate->SetMaximum(2*max(l1Rate->GetMaximum(), uct_rate->GetMaximum()));
  
  m_legend = new TLegend(0.41,0.72,0.57,0.86, "", "brNDC");
  m_legend->SetFillColor(kWhite);
  m_legend->SetBorderSize(1);
  m_legend->AddEntry(uct_rate, "UCT", "p");
  m_legend->AddEntry(l1Rate, "L1", "p");
  m_legend->Draw();
  
  m_canvas->SaveAs("eg_rate.png");

}

void UCTRateTree::CombinePlots( ) {
  
  m_canvas = new TCanvas("CompareUCT", "Compare UCT at each step", 800, 600);
  
  m_canvas->cd();
  m_canvas->SetLogy();
  m_canvas->SetFillColor(10);

  h_rate->SetTitle("EG Rate");
  h_rate->GetXaxis()->SetTitle("L1 p_{T} (GeV)");
  h_rate->GetXaxis()->CenterTitle(true);
  h_rate->GetXaxis()->SetTitleOffset(1.2);
  h_rate->SetMinimum(10);
  
  h_rate->Draw("ph");
  h_rate_regId->Draw("phsame");
  h_rate_regId_Iso->Draw("phsame");

  h_rate->SetMaximum(2*max(h_rate_regId->GetMaximum(), h_rate->GetMaximum()));
  
  m_legend = new TLegend(0.41,0.72,0.71,0.86, "", "brNDC");
  m_legend->SetFillColor(kWhite);
  m_legend->SetBorderSize(1);
  m_legend->AddEntry(h_rate, "2x1 H+E Clusters", "p");
  m_legend->AddEntry(h_rate_regId, "2x1 EG passing regional ID", "p");
  m_legend->AddEntry(h_rate_regId_Iso, "2x1 EG passing regional ID with Iso", "p");
  
  m_legend->Draw();
  
  m_canvas->SaveAs("eg_rate_evolution.png");

}
