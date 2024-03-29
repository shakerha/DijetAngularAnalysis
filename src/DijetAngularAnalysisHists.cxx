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
  book<TH1F>("eta_jet1", "#eta_{1}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet2", "#eta_{2}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet3", "#eta_{3}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet4", "#eta_{4}", 40, -2.5, 2.5);
  book<TH1F>("PETA", "#eta_{5}", 40, -2.5, 2.5);

  book<TH1F>("EMcharged_jet1", "EMcharged_jet1", 100,0.0,1.0);
  book<TH1F>("EMneutral_jet1", "EMneutral_jet1", 100,0.0,1.0);
  book<TH1F>("HADcharged_jet1", "HADcharged_jet1", 100,0.0,1.0);
  book<TH1F>("HADneutral_jet1", "HADneutral_jet1", 100,0.0,1.0);
  
  book<TH1F>("rapidity_1", "y_{1}", 100,-5,5);
  book<TH1F>("rapidity_2", "y_{2}", 100,-5,5);
  book<TH1F>("rapidity_12", "y_{12}", 100,-5,5);
  
  book<TH1F>("pT1", "p_{T,1} [GeV]", 100,200,5000);
  book<TH1F>("pT2", "p_{T,2} [GeV]", 100,200,5000);
  
  book<TH1F>("mj1j2", "M_{jj} [GeV]", 100,0,8000);
  
  book<TH1F>("chi", "#chi", 20,0,20);
  
  book<TH1F>("yboost", "y_{boost} [GeV]", 100,-5,5);
  
  book<TH1F>("teta*", "#teta^{*}", 100,0,pihalb);
  
  book<TH1F>("deltaphi", "#Delta #phi", 100,-2*pi,2*pi);
  
  book<TH1F>("pT_response_1", "p_{T,1,response,matched genjets}", 100,-2,2);
  book<TH1F>("pT_response_2", "p_{T,2,response,matched genjets} ", 100,-2,2);
  book<TH1F>("Mjj_Response", "M_{jj,response, matched genjets}", 100,-2,3);
  
    
		auto K=yBins.size();
		for (uint j=0; j<=K-2; j++){
		
		float ymin=DijetVars::yBins_[j];
		float ymax=DijetVars::yBins_[j+1];
		
		auto N=ptBins.size();
		for(uint i=0;i<= N-2;i++){
			float ptMin=DijetVars::ptBins_[i];
			float ptMax=DijetVars::ptBins_[i+1];
			TString name = TString::Format("response_pt%.0fto%.0f_y%.2fto%.2f", ptMin, ptMax, ymin, ymax);
			book<TH1F>(name, TString::Format("%.2f < p_{T} < %.2f GeV , %.2f < y < %.2f ;Response;", ptMin, ptMax, ymin, ymax), 100,-2,3); //name aendern
			// cout << "Adding hist " << name << endl;
		
		}
	
	}
		


  // primary vertices
  book<TH1F>("N_pv", "N^{PV}", 100, 0, 100);
  
  is_mc = (ctx.get("dataset_type")=="MC");
	//~ std::cout << "Constructor fertig" << std::endl;
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

  if(!event.isRealData)hist("N_PU")->Fill(event.genInfo->pileup_TrueNumInteractions(), weight);

  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
    hist("EMcharged_jet1")->Fill(jets->at(0).chargedEmEnergyFraction(), weight);
    hist("EMneutral_jet1")->Fill(jets->at(0).neutralEmEnergyFraction(), weight);
    hist("HADcharged_jet1")->Fill(jets->at(0).chargedHadronEnergyFraction(), weight);
    hist("HADneutral_jet1")->Fill(jets->at(0).neutralHadronEnergyFraction(), weight);
    hist("rapidity_1")->Fill(0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz())), weight);
    hist("pT1")->Fill(event.jets->at(0).pt(), weight);
    //if (event.jets->at(0).pt() < 500) {
		//cout << " *** low jet: " << event.jets->at(0).pt() << endl;
	//}
      

    
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

    //is_mc = ctx.get("dataset_type") == "MC";
    
    //~ float DR = 10^6;


	if( is_mc ){
		int a=-1;
		if(event.genjets->size() > 0  && event.jets->size() >0){	
			auto kleinsterAbstand = 100000; 
			auto jet1 = event.jets->at(0);
			auto gjet1 = event.genjets->at(0);

			for(unsigned  int i=0; i < event.genjets->size(); i++){
				if( deltaR( jet1, event.genjets->at(i)) < kleinsterAbstand && deltaR( jet1, event.genjets->at(i)) < 0.2){
				kleinsterAbstand = deltaR( jet1, event.genjets ->at(i));	
				a = i;
				}

		
			}
			if(a >= 0){
				hist("pT_response_1") -> Fill( (jet1.pt()-event.genjets->at(a).pt())/event.genjets->at(a).pt(), weight);			// matched genjet
			
			auto K=yBins.size();
			for (uint j=0; j<=K-2; j++){
		
				float ymin=yBins[j];
				float ymax=yBins[j+1];
				float rap1=0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz()));
			if(ymin < fabs(rap1) && fabs(rap1) < ymax){
				auto N=ptBins.size();
				for(uint i=0;i<= N-2;i++){
					float ptMin=ptBins[i];
					float ptMax=ptBins[i+1];
					
				
					if(ptMin<jet1.pt() && jet1.pt()<ptMax){
						TString name = TString::Format("response_pt%.0fto%.0f_y%.2fto%.2f", ptMin, ptMax, ymin, ymax);	
						hist(name)-> Fill((jet1.pt()-event.genjets->at(a).pt())/event.genjets->at(a).pt(), weight);
					}
				}
			}
		}
		//~ hist("pT_response_1_1") -> Fill((jet1.pt()- gjet1.pt())/gjet1.pt(), weight);										// leading genjet	
			}
	if(event.genjets->size() > 1 && event.jets->size() >1){												
		//std::cout << "B" << std::endl;
		
		auto jet1 = event.jets->at(0);
		auto jet2 = event.jets->at(1);
		auto gjet1 = event.genjets->at(0);
		auto gjet2 = event.genjets->at(1);
		auto zweitkleinsterAbstand = 100000;
		int b=-1;
		auto recojet = jet1.v4() + jet2.v4();
		//~ auto leadinggenjet = event.genjets->at(0).v4() + event.genjets->at(1).v4();
		
		for( unsigned int i=0; i < event.genjets->size(); i++){
			if( deltaR( jet2, event.genjets->at(i)) < zweitkleinsterAbstand && deltaR( jet2, event.genjets->at(i)) < 0.2 ){					// 0.2 bc half of 0.4 (AK4)
				zweitkleinsterAbstand = deltaR( jet2, event.genjets ->at(i));	
				b = i;
			}
			
			
		}
		if(a >= 0 && b >= 0){		
			auto matchedgenjet = event.genjets->at(a).v4()+event.genjets->at(b).v4();
	
			hist("pT_response_2") -> Fill( (jet2.pt()-event.genjets->at(b).pt())/event.genjets->at(b).pt(), weight);		// matched genjets
			

			
			hist("Mjj_Response") -> Fill( ((recojet).M()- (matchedgenjet).M())/(matchedgenjet).M(), weight);				// matched genjets
			
			
			auto K=yBins.size();
			for (uint j=0; j<=K-2; j++){

				float ymin=yBins[j];
				float ymax=yBins[j+1];
				float rap2=0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz()));
			if(ymin < rap2 && rap2 < ymax){
				auto N=ptBins.size();
				for(uint i=0;i<= N-2;i++){
					float ptMin=ptBins[i];
					float ptMax=ptBins[i+1];
					

					if(ptMin<jet2.pt() && jet2.pt()<ptMax){
						TString name = TString::Format("response_pt%.0fto%.0f_y%.2fto%.2f", ptMin, ptMax, ymin, ymax);	
						hist(name)-> Fill((jet2.pt()-event.genjets->at(b).pt())/event.genjets->at(b).pt(), weight);
					}
				}
			}
			}
			
			//~ 
	//~ auto pt= event.jets->at().pt();
	//~ auto y= 0.5*TMath::Log((event.jets->at().energy()+event.jets->at().v4().Pz())/(event.jets->at().energy()-event.jets->at().v4().Pz()))
	//~ for(0.5<y<1){
		//~ if(400<pt<500){
		//~ hist(response1-> Fill(event.jets->at()-event.genjets->at().pt())/event.genjets->at().pt(), weight);
		//~ 
	//~ }
	//~ hist("pT_response_1_2") -> Fill((jet2.pt()- gjet2.pt())/gjet2.pt(), weight);									// leading genjets
	//~ hist("Mjj_2_Response") -> Fill(((recojet).M()- ((leadinggenjet).M()))/((leadinggenjet).M()), weight);			// leading genjets
		}
	
	}
	}
	} // end if mc
 
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
