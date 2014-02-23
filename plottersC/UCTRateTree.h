//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 12 15:24:20 2012 by ROOT version 5.32/00
// from TTree Ntuple/Ntuple
// found on file: ../uct_rates_zerob3_B.root
//////////////////////////////////////////////////////////

#ifndef UCTRateTree_h
#define UCTRateTree_h

#include <L1RateTree.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class UCTRateTree : public L1RateTree {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  //UCT trees have additional branches
  
  vector<float>   *jetPt;
  vector<float>   *regionPt;
  vector<int>     *ellIso;
  vector<int>     *pu;
  vector<bool>    *tauVeto;
  vector<bool>    *mipBit;
  
  // List of branches
  TBranch        *b_jetPt;   //!
  TBranch        *b_regionPt;  //!
  TBranch        *b_ellIso;    //!
  TBranch        *b_pu;        //!
  TBranch        *b_tauVeto;   //!
  TBranch        *b_mipBit;    //!

  UCTRateTree(const char * infile, const char * path);
  virtual ~UCTRateTree();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree*);
  virtual void     Loop();
  virtual void     Show(Long64_t entry = -1);

  void  CombinePlots( );

  void  CombineL1UCT(TH1F * );
  
  //Additional histograms
  TH1F * h_rate_regId;
  TH1F * h_rate_regId_Iso;

  TLegend * m_legend;
  TCanvas * m_canvas;

  float L1G_CALIB_FACTOR;
  

};

#endif

#ifdef UCTRateTree_cxx
UCTRateTree::UCTRateTree(const char * infile, const char * path) 
{
  
  TTree *tree;
  TFile * f1 = TFile::Open(infile);
  if( !f1 ) {
    std::cout << "Cannot open file: " << std::string(infile) << std::endl;
    exit(1);
  }
  tree = (TTree*)gDirectory->Get(path);
  
  Init(tree);
  
}

UCTRateTree::~UCTRateTree()
{

  std::cout << "delete UCTL1Rate" << std::endl;

}

Int_t UCTRateTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t UCTRateTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

void UCTRateTree::Init(TTree * tree)
{

  // Set object pointer
  pt = 0;
  eta = 0;
  phi = 0;
  jetPt = 0;
  regionPt = 0;
  ellIso = 0;
  pu = 0;
  tauVeto = 0;
  mipBit = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("pt", &pt, &b_pt);
  fChain->SetBranchAddress("eta", &eta, &b_eta);
  fChain->SetBranchAddress("phi", &phi, &b_phi);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
  fChain->SetBranchAddress("evt", &evt, &b_evt);
  
  fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
  fChain->SetBranchAddress("regionPt", &regionPt, &b_regionPt);
  fChain->SetBranchAddress("ellIso", &ellIso, &b_ellIso);
  fChain->SetBranchAddress("pu", &pu, &b_pu);
  fChain->SetBranchAddress("tauVeto", &tauVeto, &b_tauVeto);
  fChain->SetBranchAddress("mipBit", &mipBit, &b_mipBit);
  
}

void UCTRateTree::Show(Long64_t entry)
{
  
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
  
}


#endif // #ifdef UCTRateTree_cxx
