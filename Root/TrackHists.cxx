#include "xAODAnaHelpers/TrackHists.h"

#include <math.h>

#include "xAODAnaHelpers/HelperFunctions.h"

ANA_MSG_SOURCE(msgTrackHists, "TrackHists")

TrackHists :: TrackHists (std::string name, std::string detailStr) :
  HistogramManager(name, detailStr)
{
}

TrackHists :: ~TrackHists () {}

StatusCode TrackHists::initialize() {

  // These plots are always made
  m_trk_n         = book(m_name, "trk_n",       "trk multiplicity", 10, -0.5, 9.5 );
  m_trk_n_l       = book(m_name, "trk_n_l",     "trk multiplicity", 100, -0.5, 99.5 );

  m_trk_Pt        = book(m_name, "pt",          "trk p_{T} [GeV]", 100, 0, 10 );
  m_trk_Pt_l      = book(m_name, "pt_l",        "trk p_{T} [GeV]", 100, 0, 100 );
  m_trk_P         = book(m_name, "p",           "trk |p| [GeV]", 100, 0, 10 );
  m_trk_P_l       = book(m_name, "p_l",         "trk |p| [GeV]", 100, 0, 100 );
  m_trk_Eta       = book(m_name, "eta",         "trk #eta", 80, -4, 4);
  m_trk_Phi       = book(m_name, "phi",         "trk #phi",120, -TMath::Pi(), TMath::Pi() );
  m_trk_d0        = book(m_name, "d0",          "d0[mm]", 100,-5.0, 5.0 );
  m_trk_d0_s      = book(m_name, "d0_s" ,       "d0[mm]", 100,  -1.0, 1.0 );

  m_trk_z0        = book(m_name, "z0",          "z0[mm]", 100,-5.0, 5.0 );
  m_trk_z0_s      = book(m_name, "z0_s",        "z0[mm]", 100,-1.0, 1.0 );
  m_trk_z0sinT    = book(m_name, "z0sinT",      "z0xsin(#theta)[mm]", 100, -5.0, 5.0 );

  m_trk_chi2Prob  = book(m_name, "chi2Prob",    "chi2Prob", 100,   -0.01,     1.0);
  m_trk_charge    = book(m_name, "charge" ,     "charge",   3,  -1.5,  1.5   );

  //
  //  2D plots
  //
  m_fill2D = false;
  if(m_detailStr.find("2D") != std::string::npos ){
    m_fill2D = true;

    m_trk_Eta_vs_trk_P            = book(m_name, "trk_Eta_vs_trk_P",                "trk |p| [GeV]", 100, 0, 10, "trk #eta", 80, -4, 4);
    m_trk_Eta_vs_trk_P_l          = book(m_name, "trk_Eta_vs_trk_P_l",              "trk |p| [GeV]", 100, 0, 100, "trk #eta", 80, -4, 4);
    m_trk_Phi_vs_trk_P            = book(m_name, "trk_Phi_vs_trk_P",                "trk |p| [GeV]", 100, 0, 10, "trk #phi",120, -TMath::Pi(), TMath::Pi());
    m_trk_Phi_vs_trk_P_l          = book(m_name, "trk_Phi_vs_trk_P_l",              "trk |p| [GeV]", 100, 0, 100, "trk #phi",120, -TMath::Pi(), TMath::Pi());
    m_trk_Eta_vs_trk_Phi          = book(m_name, "trk_Eta_vs_trk_Phi",              "trk #phi", 120, -TMath::Pi(), TMath::Pi(), "trk #eta", 80, -4, 4);

    m_trk_d0_vs_trk_P             = book(m_name, "trk_d0_vs_trk_P",                 "trk |p| [GeV]", 100, 0, 10, "d0[mm]", 100,-5.0, 5.0);
    m_trk_d0_vs_trk_P_l           = book(m_name, "trk_d0_vs_trk_P_l",               "trk |p| [GeV]", 100, 0, 100, "d0[mm]", 100,-5.0, 5.0);
    m_trk_z0_vs_trk_P             = book(m_name, "trk_z0_vs_trk_P",                 "trk |p| [GeV]", 100, 0, 10, "z0[mm]", 100,-5.0, 5.0);
    m_trk_z0_vs_trk_P_l           = book(m_name, "trk_z0_vs_trk_P_l",               "trk |p| [GeV]", 100, 0, 100, "z0[mm]", 100,-5.0, 5.0);
    m_trk_z0sinT_vs_trk_P         = book(m_name, "trk_z0sinT_vs_trk_P",             "trk |p| [GeV]", 100, 0, 10, "z0xsin(#theta)[mm]", 100,-5.0, 5.0);
    m_trk_z0sinT_vs_trk_P_l       = book(m_name, "trk_z0sinT_vs_trk_P_l",           "trk |p| [GeV]", 100, 0, 100, "z0xsin(#theta)[mm]", 100,-5.0, 5.0);
  }

  //
  //  IP Details
  //
  m_fillIPDetails = false;
  if(m_detailStr.find("IPDetails") != std::string::npos ){
    m_fillIPDetails = true;

    m_trk_d0Err        = book(m_name, "d0Err",            "d0Err[mm]",        100,  0, 0.4 );
    m_trk_d0_l         = book(m_name, "d0_l" ,            "d0[mm]",           100,  -10.0, 10.0 );
    m_trk_d0_ss        = book(m_name, "d0_ss" ,           "d0[mm]",           100,  -0.2, 0.2 );

    m_trk_d0Sig        = book(m_name, "d0Sig",            "d0Sig",            240,  -20.0, 40.0 );

    m_trk_z0_l         = book(m_name, "z0_l" ,            "z0[mm]",                         100,  -600.0, 600.0 );
    m_trk_z0sinT_l     = book(m_name, "z0sinT_l",         "z0xsin(#theta)[mm]",             100,  -20.0, 20.0 );
    m_trk_z0Err        = book(m_name, "z0Err",            "z0Err[mm]",                      100,   0, 0.4 );
    m_trk_z0Sig        = book(m_name, "z0Sig",            "z0Sig",                          100,  -25.0, 25.0 );
    m_trk_z0SigsinT    = book(m_name, "z0SigsinT",        "z0 significance x sin(#theta)",  100,  -25.0, 25.0 );

    //m_trk_mc_prob      = book(m_name, "mc_prob",      "mc_prob",     100,  -0.1, 1.1 );
    //m_trk_mc_barcode   = book(m_name, "mc_barcode",   "mc_barcode",  100,  -0.1, 0.5e6 );
    //m_trk_mc_barcode_s = book(m_name, "mc_barcode_s", "mc_barcode",  100,  -0.1, 25e3 );
  }

  //
  //  Fill Hit Counts Details
  //
  m_fillHitCounts = false;
  if(m_detailStr.find("HitCounts") != std::string::npos ){
    m_fillHitCounts = true;
    m_trk_nSi        = book(m_name, "nSi",        "nSi",         30,   -0.5, 29.5 );
    m_trk_nSiAndDead = book(m_name, "nSiAndDead", "nSi(+Dead)",  30,   -0.5, 29.5 );
    m_trk_nSiDead    = book(m_name, "nSiDead",    "nSiDead",     10,   -0.5,  9.5 );
    m_trk_nSCT       = book(m_name, "nSCT",       "nSCTHits",    20,   -0.5, 19.5 );
    m_trk_nPix       = book(m_name, "nPix",       "nPix",        10,   -0.5,  9.5 );
    m_trk_nPixHoles  = book(m_name, "nPixHoles",  "nPixHoles",   10,   -0.5,  9.5 );
    m_trk_nBL        = book(m_name, "nBL",        "nBL",          3,   -0.5,  2.5 );
    m_trk_nTRT       = book(m_name, "nTRT",       "nTRT",        50,   -0.5, 49.5 );
    // m_trk_nTRTHoles  = book(m_name, "nTRTHoles",  "nTRTHoles",   50,   -0.5, 49.5 );
    // m_trk_nTRTDead   = book(m_name, "nTRTDead",   "nTRTDead",    50,   -0.5, 49.5 );
  }

  //
  //  TP Errors Details
  //
  m_fillTPErrors = false;
  if(m_detailStr.find("TPErrors") != std::string::npos ){
    m_fillTPErrors = true;

    //m_chi2ndof TProfile(m_name, "chi2ndofvseta",  "chi2ndofvseta;    eta;       chi2",  20,  -0.1, 2.7, 0, 4, "s" );
    //new TProfile(m_name, "chi2ndofvseta",  "chi2ndofvseta;    eta;       chi2",  20,  -0.1, 2.7, 0, 4, "s" );
    //new TProfile(m_name, "nhitsvseta",  "nhitsvseta;    eta;       nhits",  20,  -0.1, 2.7, 0, 15 , "s" );
    //new TProfile(m_name, "chi2ndofvspt",  "chi2ndofvseta;    pt;       chi2",  50,  -0.1, 20, 0 , 4, "s" );

    //  new TProfile(m_name, "d0Errvseta",      "d0Errvseta;    eta;       d0Err",  20,  -0.1, 2.7, 0, 0.4, "s" );
    //  new TProfile(m_name, "d0ErrvsIpt",      "d0ErrvsIpt;    Ipt;       d0Err",  20,  -6e-4, 6e4, 0, 0.4, "s" );
    //  new TProfile(m_name, "d0Errvsphi",      "d0Errvsphi;    phi;       d0Err",  1000,  -3.2, 3.2, 0, 0.4);
    //

    //  new TH2F(m_name, "z0d0"    ,    "z0d0;     z0[mm];  d0[mm];",  50,  -300.0, 300.0, 50, -4.0, 4.0  );
    //  new TH2F(m_name, "z0sinTd0",    "z0sinTd0;     z0xsin0[mm](signed);  d0[mm](signed);",  50,-2.0, 2.0, 50, -2.0, 2.0  );

    //  new TH2F(m_name, "d0vsPt"    ,    "d0vsPt;     d0[mm] (signed);  Pt[GeV];",  100,  -2,2.0, 50, 0, 10  );
    //  new TH2F(m_name, "d0SigvsPt"    ,    "d0SigvsPt;     d0Sig(signed);  Pt[GeV];",  240, -20, 40.0, 50, 0, 10  );
    m_trk_phiErr       = book(m_name, "phiErr"  ,   "phi Err[rad]",  100,  0, 0.01 );
    m_trk_thetaErr     = book(m_name, "thetaErr",   "theta Err",     100,  0, 0.01 );
    m_trk_qOpErr       = book(m_name, "qOpErr"  ,   "q/p Err",       100,  0, 1.0e-04);
  }

  //
  //  Chi2 Details
  //
  m_fillChi2Details = false;
  if(m_detailStr.find("Chi2Details") != std::string::npos ){
    m_fillChi2Details = true;
    m_trk_chi2Prob_l   = book(m_name, "chi2Prob_l",       "chi2Prob",  100,   -0.1,     1.1);
    m_trk_chi2Prob_s   = book(m_name, "chi2Prob_s",       "chi2Prob",  100,   -0.01,    0.1);
    m_trk_chi2Prob_ss  = book(m_name, "chi2Prob_ss",      "chi2Prob",  100,   -0.001,   0.01);
    m_trk_chi2ndof     = book(m_name, "chi2ndof",         "chi2ndof",  100,    0.0,     8.0 );
    m_trk_chi2ndof_l   = book(m_name, "chi2ndof_l",       "chi2ndof",  100,    0.0,     80.0 );
  }

  //
  // TrkDebugging
  //
  m_fillDebugging = false;
  if(m_detailStr.find("Debugging") != std::string::npos ){
    m_fillDebugging = true;
    m_trk_eta_vl      = book(m_name, "eta_vl",        "eta",       100,  -6,    6     );
    m_trk_z0_vl       = book(m_name, "z0_vl",         "z0[mm]",    100,  -10000.0, 10000.0 );
    m_trk_z0_raw_m    = book(m_name, "z0_raw_m",      "z0[mm]",   100,  -100.0,  100.0 );
    m_trk_z0_atlas_m  = book(m_name, "z0_atlas_m",   "z0[mm]",   100,  -100.0,  100.0 );
    m_trk_vz          = book(m_name, "vz",            "z0[mm]",   100,  -100.0,  100.0 );
    m_trk_z0_m        = book(m_name, "z0_m",         "z0[mm]",   100,  -100.0,  100.0 );
    m_trk_d0_vl       = book(m_name, "d0_vl",         "d0[mm]",    100,  -10000.0, 10000.0 );
    m_trk_pt_ss       = book(m_name, "pt_ss",         "Pt[GeV",    100,  0,     2.0  );
    m_trk_phiManyBins = book(m_name, "phiManyBins" ,  "phi",      1000,  -3.2,  3.2   );

  }

  //
  // vs Lumi Block
  //
  m_fillVsLumi = false;
  if(m_detailStr.find("vsLumiBlock") != std::string::npos ){
    m_fillVsLumi = true;

    m_lBlock                  = book(m_name, "lBlock",                "LumiBlock",  100, 0, 1000);
    m_trk_z0_vs_lBlock        = book(m_name, "z0_vs_lBlock",          "LumiBlock",  100, 0, 1000, "z0",      -100, 100);
    m_trk_z0_raw_vs_lBlock    = book(m_name, "z0_raw_vs_lBlock",      "LumiBlock",  100, 0, 1000, "z0 raw",  -100, 100);
    m_trk_z0_atlas_vs_lBlock  = book(m_name, "z0_atlas_vs_lBlock",    "LumiBlock",  100, 0, 1000, "z0 atlas", -100, 100);

    m_trk_vz_vs_lBlock        = book(m_name, "vz_vs_lBlock",          "LumiBlock",  100, 0, 1000, "vz",       -100, 100);
    m_pvz_vs_lBlock           = book(m_name, "pvz_vs_lBlock",         "LumiBlock",  100, 0, 1000, "pvz",      -100, 100);
    m_pv_valid_vs_lBlock      = book(m_name, "pv_valid_vs_lBlock",    "LumiBlock",  100, 0, 1000, "valid",    -0.1, 1.1);


    m_bsX                     = book(m_name, "bsX",                "beamPos X",  100, -10, 10);
    m_bsY                     = book(m_name, "bsY",                "beamPos Y",  100, -10, 10);
    m_bsZ                     = book(m_name, "bsZ",                "beamPos Z",  100, -10, 10);
    m_bsX_vs_lBlock           = book(m_name, "bsX_vs_lBlock",      "LumiBlock",  100, 0, 1000, "bxX", -1, 1);
    m_bsY_vs_lBlock           = book(m_name, "bsY_vs_lBlock",      "LumiBlock",  100, 0, 1000, "bsY", -1, 1);
    m_bsZ_vs_lBlock           = book(m_name, "bsZ_vs_lBlock",      "LumiBlock",  100, 0, 1000, "bsZ", -10, 10);

    //m_trk_eta_vl      = book(m_name, "eta_vl",        "eta",       100,  -6,    6     );
    //m_trk_z0_vl       = book(m_name, "z0_vl",         "z0[mm]",    100,  -10000.0, 10000.0 );
    //m_trk_z0_m_raw    = book(m_name, "z0_m_raw",         "z0[mm]",   100,  -100.0,  100.0 );
    //m_trk_z0_m        = book(m_name, "z0_m",         "z0[mm]",   100,  -100.0,  100.0 );
    //m_trk_d0_vl       = book(m_name, "d0_vl",         "d0[mm]",    100,  -10000.0, 10000.0 );
    //m_trk_pt_ss       = book(m_name, "pt_ss",         "Pt[GeV",    100,  0,     2.0  );
    //m_trk_phiManyBins = book(m_name, "phiManyBins" ,  "phi",      1000,  -3.2,  3.2   );

  }


  // if worker is passed to the class add histograms to the output
  return StatusCode::SUCCESS;
}

StatusCode TrackHists::execute( const xAOD::TrackParticleContainer* trks, const xAOD::Vertex *pvx, float eventWeight,  const xAOD::EventInfo* eventInfo ) {
  using namespace msgTrackHists;
  xAOD::TrackParticleContainer::const_iterator trk_itr = trks->begin();
  xAOD::TrackParticleContainer::const_iterator trk_end = trks->end();
  for( ; trk_itr != trk_end; ++trk_itr ) {
    ANA_CHECK( this->execute( (*trk_itr), pvx, eventWeight, eventInfo ));
  }

  m_trk_n -> Fill( trks->size(), eventWeight );
  m_trk_n_l -> Fill( trks->size(), eventWeight );

  return StatusCode::SUCCESS;
}

StatusCode TrackHists::execute( const xAOD::TrackParticle* trk, const xAOD::Vertex *pvx, float eventWeight,  const xAOD::EventInfo* eventInfo ) {

  //basic
  float        trkPt       = trk->pt()/1e3;
  float        trkP        = -1;
  if (fabs(trk->qOverP())>0.) trkP = (1./fabs(trk->qOverP()))/1e3;
  float        trkEta      = trk->eta();
  float        trkPhi      = trk->phi();
  float        chi2        = trk->chiSquared();
  float        ndof        = trk->numberDoF();
  float        chi2Prob    = TMath::Prob(chi2,ndof);
  float        d0          = trk->d0();
  float        pvz         = HelperFunctions::getPrimaryVertexZ(pvx);
  float        z0          = trk->z0() + trk->vz() - pvz;

  float        sinT        = sin(trk->theta());

  m_trk_Pt       -> Fill( trkPt,            eventWeight );
  m_trk_Pt_l     -> Fill( trkPt,            eventWeight );
  m_trk_P        -> Fill( trkP,             eventWeight );
  m_trk_P_l      -> Fill( trkP,             eventWeight );
  m_trk_Eta      -> Fill( trkEta,           eventWeight );
  m_trk_Phi      -> Fill( trkPhi,           eventWeight );
  m_trk_d0       -> Fill( d0,               eventWeight );
  m_trk_d0_s     -> Fill( d0,               eventWeight );
  m_trk_z0       -> Fill( z0,               eventWeight );
  m_trk_z0_s     -> Fill( z0,               eventWeight );
  m_trk_z0sinT   -> Fill(z0*sinT,           eventWeight );

  m_trk_chi2Prob -> Fill( chi2Prob ,        eventWeight );
  m_trk_charge   -> Fill( trk->charge() ,   eventWeight );

  if(m_fill2D){

    m_trk_Eta_vs_trk_P       -> Fill( trkP,   trkEta,   eventWeight );
    m_trk_Eta_vs_trk_P_l     -> Fill( trkP,   trkEta,   eventWeight );
    m_trk_Phi_vs_trk_P       -> Fill( trkP,   trkPhi,   eventWeight );
    m_trk_Phi_vs_trk_P_l     -> Fill( trkP,   trkPhi,   eventWeight );
    m_trk_Eta_vs_trk_Phi     -> Fill( trkPhi, trkEta,   eventWeight );
    m_trk_d0_vs_trk_P        -> Fill( trkP,   d0,       eventWeight );
    m_trk_d0_vs_trk_P_l      -> Fill( trkP,   d0,       eventWeight );
    m_trk_z0_vs_trk_P        -> Fill( trkP,   z0,       eventWeight );
    m_trk_z0_vs_trk_P_l      -> Fill( trkP,   z0,       eventWeight );
    m_trk_z0sinT_vs_trk_P    -> Fill( trkP,   z0*sinT,  eventWeight );
    m_trk_z0sinT_vs_trk_P_l  -> Fill( trkP,   z0*sinT,  eventWeight );

  }

  if(m_fillIPDetails){
    float d0Err = sqrt((trk->definingParametersCovMatrixVec().at(0)));
    float d0Sig = (d0Err > 0) ? d0/d0Err : -1 ;
    m_trk_d0_l         -> Fill(d0    , eventWeight );
    m_trk_d0_ss        -> Fill(d0    , eventWeight );
    m_trk_d0Err        -> Fill(d0Err , eventWeight );
    m_trk_d0Sig        -> Fill(d0Sig , eventWeight );

    float z0Err = sqrt((trk->definingParametersCovMatrixVec().at(2)));
    float z0Sig = (z0Err > 0) ? z0/z0Err : -1 ;

    m_trk_z0_l         -> Fill(z0         , eventWeight );
    m_trk_z0sinT_l     -> Fill(z0*sinT,     eventWeight );
    m_trk_z0Err        -> Fill(z0Err      , eventWeight );
    m_trk_z0Sig        -> Fill(z0Sig      , eventWeight );
    m_trk_z0SigsinT    -> Fill(z0Sig*sinT , eventWeight );

  }

  if(m_fillHitCounts){

    uint8_t nBL       = -1;
    uint8_t nPix      = -1;
    uint8_t nPixDead  = -1;
    uint8_t nPixHoles = -1;
    uint8_t nSCT      = -1;
    uint8_t nSCTDead  = -1;
    uint8_t nTRT      = -1;
    //uint8_t nTRTHoles = -1;
    //uint8_t nTRTDead  = -1;

    if(!trk->summaryValue(nBL,       xAOD::numberOfBLayerHits))       ANA_MSG_ERROR("BLayer hits not filled");
    if(!trk->summaryValue(nPix,      xAOD::numberOfPixelHits))        ANA_MSG_ERROR("Pix hits not filled");
    if(!trk->summaryValue(nPixDead,  xAOD::numberOfPixelDeadSensors)) ANA_MSG_ERROR("Pix Dead not filled");
    if(!trk->summaryValue(nPixHoles, xAOD::numberOfPixelHoles))       ANA_MSG_ERROR("Pix holes not filled");
    if(!trk->summaryValue(nSCT,      xAOD::numberOfSCTHits))          ANA_MSG_ERROR("SCT hits not filled");
    if(!trk->summaryValue(nSCTDead,  xAOD::numberOfSCTDeadSensors))   ANA_MSG_ERROR("SCT Dead not filled");
    if(!trk->summaryValue(nTRT,      xAOD::numberOfTRTHits))          ANA_MSG_ERROR("TRT hits not filled");
    // if(!trk->summaryValue(nTRTHoles, xAOD::numberOfTRTHoles))         ANA_MSG_ERROR("TRT holes not filled");
    // if(!trk->summaryValue(nTRTDead,  xAOD::numberOfTRTDeadStraws))    ANA_MSG_ERROR("TRT Dead not filled");

    uint8_t nSi     = nPix     + nSCT;
    uint8_t nSiDead = nPixDead + nSCTDead;
    m_trk_nBL        -> Fill( nBL         , eventWeight );
    m_trk_nSi        -> Fill( nSi         , eventWeight );
    m_trk_nSiAndDead -> Fill( nSi+nSiDead , eventWeight );
    m_trk_nSiDead    -> Fill( nSiDead     , eventWeight );
    m_trk_nSCT       -> Fill( nSCT        , eventWeight );
    m_trk_nPix       -> Fill( nPix        , eventWeight );
    m_trk_nPixHoles  -> Fill( nPixHoles   , eventWeight );
    m_trk_nTRT       -> Fill( nTRT        , eventWeight );
    // m_trk_nTRTHoles  -> Fill( nTRTHoles   , eventWeight );
    // m_trk_nTRTDead   -> Fill( nTRTDead    , eventWeight );

  }

  if(m_fillTPErrors){
    //m_trk_phiErr       -> Fill( sqrt((trk->definingParametersCovMatrixVec().at(6))) , eventWeight );
    //m_trk_thetaErr     -> Fill( sqrt((trk->definingParametersCovMatrixVec().at(10))) , eventWeight );
    //m_trk_qOpErr       -> Fill( sqrt((trk->definingParametersCovMatrixVec().at(15))) , eventWeight );
  }

  if(m_fillChi2Details){
    float chi2NDoF     = (ndof > 0) ? chi2/ndof : -1;
    m_trk_chi2Prob_l   -> Fill(chi2Prob   , eventWeight );
    m_trk_chi2Prob_s   -> Fill(chi2Prob   , eventWeight );
    m_trk_chi2Prob_ss  -> Fill(chi2Prob   , eventWeight );
    m_trk_chi2ndof     -> Fill(chi2NDoF   , eventWeight );
    m_trk_chi2ndof_l   -> Fill(chi2NDoF   , eventWeight );
  }

  if(m_fillDebugging){
    m_trk_eta_vl      -> Fill( trkEta,     eventWeight );
    m_trk_z0_vl       -> Fill( z0,         eventWeight );
    m_trk_z0_m        -> Fill( z0,         eventWeight );
    m_trk_z0_raw_m    -> Fill( trk->z0(),  eventWeight );
    m_trk_z0_atlas_m  -> Fill( trk->z0() + trk->vz(),  eventWeight );
    m_trk_vz          -> Fill( trk->vz(),  eventWeight );
    m_trk_d0_vl       -> Fill( d0,         eventWeight );
    m_trk_pt_ss       -> Fill( trkPt,      eventWeight );
    m_trk_phiManyBins -> Fill( trkPhi,     eventWeight );
  }

  if(m_fillVsLumi && eventInfo){
    uint32_t lumiBlock = eventInfo->lumiBlock();

    m_lBlock                ->Fill(lumiBlock, eventWeight);
    m_trk_z0_vs_lBlock      ->Fill(lumiBlock, z0,                     eventWeight);
    m_trk_z0_raw_vs_lBlock  ->Fill(lumiBlock, trk->z0(),              eventWeight);
    m_trk_z0_atlas_vs_lBlock->Fill(lumiBlock, trk->z0() + trk->vz(),  eventWeight);
    m_trk_vz_vs_lBlock      ->Fill(lumiBlock, trk->vz(),              eventWeight);
    m_pvz_vs_lBlock         ->Fill(lumiBlock, pvz,                    eventWeight);

    m_pv_valid_vs_lBlock    ->Fill(lumiBlock, bool(pvx),              eventWeight);

    m_bsX    ->Fill(eventInfo->beamPosX(),              eventWeight);
    m_bsY    ->Fill(eventInfo->beamPosY(),              eventWeight);
    m_bsZ    ->Fill(eventInfo->beamPosZ(),              eventWeight);

    m_bsX_vs_lBlock    ->Fill(lumiBlock, eventInfo->beamPosX(),              eventWeight);
    m_bsY_vs_lBlock    ->Fill(lumiBlock, eventInfo->beamPosY(),              eventWeight);
    m_bsZ_vs_lBlock    ->Fill(lumiBlock, eventInfo->beamPosZ(),              eventWeight);

  }

  return StatusCode::SUCCESS;

}

