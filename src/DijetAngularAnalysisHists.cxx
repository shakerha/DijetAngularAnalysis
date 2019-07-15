#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

DijetAngularAnalysisHists::DijetAngularAnalysisHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  // jets
  Double_t pihalb= TMath::Pi()/2;
  Double_t pi= TMath::Pi();
  
  book<TH1F>("N_jets", "N_{jets}", 20, 0, 20);  
  book<TH1F>("N_PU", "N_{PU}", 100, 0, 100);  
  book<TH1F>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  book<TH1F>("pt_jet1", "p_{T}^{jet 1}", 100, 10, 500);
  book<TH1F>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);
  book<TH1F>("PETA", "#eta^{jet 5}", 40, -2.5, 2.5);

  book<TH1F>("EMcharged_jet1", "EMcharged_jet1", 100,0.0,1.0);
  book<TH1F>("EMneutral_jet1", "EMneutral_jet1", 100,0.0,1.0);
  book<TH1F>("HADcharged_jet1", "HADcharged_jet1", 100,0.0,1.0);
  book<TH1F>("HADneutral_jet1", "HADneutral_jet1", 100,0.0,1.0);
  
  book<TH1F>("rapidity_1", "rapidity1", 100,-5,5);
  book<TH1F>("rapidity_2", "rapidity2", 100,-5,5);
  book<TH1F>("rapidity_12", "rapidity12", 100,-5,5);
  
  book<TH1F>("pT1", "p_{T,1}", 100,0,1000);
  book<TH1F>("pT2", "p_{T,2}", 100,0,1000);
  
  book<TH1F>("mj1j2", "M_{jj}", 100,0,6000);
  
  book<TH1F>("chi", "#chi", 20,0,20);
  
  book<TH1F>("yboost", "yboost", 100,-5,5);
  
  book<TH1F>("teta*", "#teta^{*}", 100,0,pihalb);
  
  book<TH1F>("deltaphi", "#Delta #phi", 100,-2*pi,2*pi);
  
  

  //~ book<TH2D>("EMcharged_vs_eta_jet1","EMcharged vs #eta; #eta; EMcharged",100,-6,6,100,0.0,1.0);   
  //~ book<TH2D>("EMneutral_vs_eta_jet1","EMneutral vs #eta; #eta; EMneutral",100,-6,6,100,0.0,1.0);   
  //~ book<TH2D>("HADcharged_vs_eta_jet1","HADcharged vs #eta; #eta; HADcharged",100,-6,6,100,0.0,1.0);   
  //~ book<TH2D>("HADneutral_vs_eta_jet1","HADneutral vs #eta; #eta; HADneutral",100,-6,6,100,0.0,1.0);   
  //~ book<TH2D>("EMcharged_vs_PU_jet1","EMcharged vs PU; PU; EMcharged",100,0,100,100,0.0,1.0);   
  //~ book<TH2D>("EMneutral_vs_PU_jet1","EMneutral vs PU; PU; EMneutral",100,0,100,100,0.0,1.0);   
  //~ book<TH2D>("HADcharged_vs_PU_jet1","HADcharged vs PU; PU; HADcharged",100,0,100,100,0.0,1.0);   
  //~ book<TH2D>("HADneutral_vs_PU_jet1","HADneutral vs PU; PU; HADneutral",100,0,100,100,0.0,1.0);   


  // leptons
  //~ book<TH1F>("N_mu", "N^{#mu}", 10, 0, 10);
  //~ book<TH1F>("pt_mu", "p_{T}^{#mu} [GeV/c]", 40, 0, 200);
  //~ book<TH1F>("eta_mu", "#eta^{#mu}", 40, -2.1, 2.1);
  //~ book<TH1F>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  // primary vertices
  book<TH1F>("N_pv", "N^{PV}", 100, 0, 100);
}


void DijetAngularAnalysisHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  
  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  hist("N_jets")->Fill(Njets, weight);
  if(!event.isRealData)  hist("N_PU")->Fill(event.genInfo->pileup_TrueNumInteractions(), weight);

  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
    hist("pt_jet1")->Fill(jets->at(0).pt(), weight);
    hist("EMcharged_jet1")->Fill(jets->at(0).chargedEmEnergyFraction(), weight);
    hist("EMneutral_jet1")->Fill(jets->at(0).neutralEmEnergyFraction(), weight);
    hist("HADcharged_jet1")->Fill(jets->at(0).chargedHadronEnergyFraction(), weight);
    hist("HADneutral_jet1")->Fill(jets->at(0).neutralHadronEnergyFraction(), weight);
    hist("rapidity_1")->Fill(0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz())), weight);
    hist("pT1")->Fill(event.jets->at(0).pt(), weight);
    
    
    
    //~ ((TH2D*)hist("EMcharged_vs_eta_jet1"))->Fill(jets->at(0).eta(),jets->at(0).chargedEmEnergyFraction(), weight);
    //~ ((TH2D*)hist("EMneutral_vs_eta_jet1"))->Fill(jets->at(0).eta(),jets->at(0).neutralEmEnergyFraction(), weight);
    //~ ((TH2D*)hist("HADcharged_vs_eta_jet1"))->Fill(jets->at(0).eta(),jets->at(0).chargedHadronEnergyFraction(), weight);
    //~ ((TH2D*)hist("HADneutral_vs_eta_jet1"))->Fill(jets->at(0).eta(),jets->at(0).neutralHadronEnergyFraction(), weight);
    //~ if(!event.isRealData){
      //~ ((TH2D*)hist("EMcharged_vs_PU_jet1"))->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).chargedEmEnergyFraction(), weight);
      //~ ((TH2D*)hist("EMneutral_vs_PU_jet1"))->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).neutralEmEnergyFraction(), weight);
      //~ ((TH2D*)hist("HADcharged_vs_PU_jet1"))->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).chargedHadronEnergyFraction(), weight);
      //~ ((TH2D*)hist("HADneutral_vs_PU_jet1"))->Fill(event.genInfo->pileup_TrueNumInteractions(),jets->at(0).neutralHadronEnergyFraction(), weight);
    //~ }
  }
  
    if(Njets>=2){
	hist("rapidity_2")->Fill(0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz())), weight);
	auto rapidity1 = 0.5*TMath::Log( (event.jets->at(0).energy()+event.jets->at(0).v4().Pz()) / (event.jets->at(0).energy()-event.jets->at(0).v4().Pz()) );
	auto rapidity2 = 0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz()));
	
	auto chi = TMath::Exp(abs((rapidity1)-(rapidity2)));
	
	auto jet1 = event.jets->at(0);
	auto jet2 = event.jets->at(1);
	
    hist("rapidity_12")->Fill(0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz())), weight);
    hist("rapidity_12")->Fill(0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz())), weight);

	hist("pT2")->Fill(event.jets->at(1).pt(), weight);
	hist("mj1j2")->Fill((event.jets->at(0).v4()+event.jets->at(1).v4()).M(), weight); 
	hist("chi")->Fill(TMath::Exp(abs((rapidity1)-(rapidity2))),weight);
	hist("yboost")->Fill(0.5*((rapidity1)+(rapidity2)), weight);
	hist("teta*")->Fill((TMath::ACos(((chi-1))/(1+chi))), weight);
	hist("deltaphi")->Fill(jet1.phi() - jet2.phi(), weight);
	}
	
  if(Njets>=2){
    hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
  }
  if(Njets>=3){
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
  }
  if(Njets>=4){
    hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
  }

  if(Njets>=5){
    hist("PETA")->Fill(jets->at(4).eta(), weight);
  }
  
  //~ int Nmuons = event.muons->size();
  //~ hist("N_mu")->Fill(Nmuons, weight);
  //~ for (const Muon & thismu : *event.muons){
      //~ hist("pt_mu")->Fill(thismu.pt(), weight);
      //~ hist("eta_mu")->Fill(thismu.eta(), weight);
      //~ hist("reliso_mu")->Fill(thismu.relIso(), weight);
  //~ }
  
  int Npvs = event.pvs->size();
  hist("N_pv")->Fill(Npvs, weight);
}

DijetAngularAnalysisHists::~DijetAngularAnalysisHists(){}
