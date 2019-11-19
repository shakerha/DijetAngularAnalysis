#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisTriggerHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;



DijetAngularAnalysisTrigger::DijetAngularAnalysisTrigger(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  // jets
  
  book<TH1F>("JET_320_pT", "PFJet320", 300 ,0 ,3000);  
  book<TH1F>("JET_320_Dijetmasse", "PFJet320", 300 ,0 ,3000);
  book<TH1F>("JET_320_450_pT", "Efficiency of PFJet450", 300 ,0 ,3000);
  book<TH1F>("JET_320_450_Dijetmasse", "Efficiency of PFJet450", 300 ,0 ,3000);
  
  book<TH1F>("HT_650_pT", "PFHT650", 300 ,0 ,3000);  
  book<TH1F>("HT_650_Dijetmasse", "PFHT650", 300 ,0 ,3000);
  book<TH1F>("HT_650_900_pT", "Efficiency of PFHT900", 300 ,0 ,3000);
  book<TH1F>("HT_650_900_Dijetmasse", "Efficiency of PFHT900", 300 ,0 ,3000);
	
  //~ book<TH1F>("HT_650_pT", "pT_{HT650} [GeV/c]", 300 ,0 ,3000);
  //~ book<TH1F>("HT_650_Dijetmasse", "pT_{Jet320||HT650} [GeV/c]", 300 ,0 ,3000);
  book<TH1F>("Jet450||HT900_pT", "Efficiency of PFJet450||PFHT900", 300 ,0 ,3000);
  book<TH1F>("Jet450||HT900_Dijetmasse", "Efficiency of PFJet450||PFHT900", 300 ,0 ,3000);
  
  
  book<TH1F>("JET_400_pT", "PFJet400", 300 ,0 ,3000);  
  book<TH1F>("JET_400_Dijetmasse", "PFJet400", 300 ,0 ,3000); 
  book<TH1F>("JET_400_500_pT", "Efficiency of PFJet500", 300 ,0 ,3000);  
  book<TH1F>("JET_400_500_Dijetmasse", "Efficiency of PFJet500", 300 ,0 ,3000);  
  
  book<TH1F>("HT_680_pT", "PFHT680", 300 ,0 ,3000);  
  book<TH1F>("HT_680_Dijetmasse", "PFHT680", 300 ,0 ,3000);
  book<TH1F>("HT_680_1050_pT", "Efficiency of PFHT1050", 300 ,0 ,3000);  
  book<TH1F>("HT_680_1050_Dijetmasse", "Efficiency of PFHT1050", 300 ,0 ,3000);
  
  
  //~ book<TH1F>("HT_680_pT", "pT_{HT680} [GeV/c]", 300 ,0 ,3000);
  //~ book<TH1F>("HT_680_Dijetmasse", "dijetmass_{HT680}} [GeV/c]", 300 ,0 ,3000);
  book<TH1F>("Jet500||HT1050_pT", "pT_{Jet500||HT1050}", 300 ,0 ,3000);  
  book<TH1F>("Jet500||HT1050_Dijetmasse", "Dijetmasse_{Jet500||HT1050}", 300 ,0 ,3000);  
 

}


void DijetAngularAnalysisTrigger::fill(const Event & event){

  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHLTEffHists.h'
  
  // Don't forget to always use the weight when filling.
  
  auto ersterjet = event.jets->at(0);
  auto zweiterjet= event.jets->at(1);
  int Njets = event.jets->size();
  double Mjj_max=(ersterjet.v4() +zweiterjet.v4()).M();
  //2016
  
   
  
if(event.year=="2016v3"){
	 
	auto PFJET320 = event.get_trigger_index("HLT_PFJet320_v*");
	auto PFJET450 = event.get_trigger_index("HLT_PFJet450_v*");
  
  
	auto PFHT900 = event.get_trigger_index("HLT_PFHT900_v*");							
	auto PFHT650 = event.get_trigger_index("HLT_PFHT650_v*");
  
  
	int Njets = event.jets->size();
  
  	
   if(Njets>=1){ 
	   
	auto ersterjet = event.jets->at(0);
	//cout << "Doing 2016v3 trig hists" << endl;
	  
	 if (event.passes_trigger(PFJET320)){							       			
		hist("JET_320_pT")->Fill(ersterjet.pt(),1);
		if (event.passes_trigger(PFJET450)) {
		hist("JET_320_450_pT")->Fill(ersterjet.pt(),1);
		}
		}

	if (event.passes_trigger(PFHT650)){
		hist("HT_650_pT")->Fill(ersterjet.pt(),1);
		if (event.passes_trigger(PFHT900)) {
		hist("HT_650_900_pT")->Fill(ersterjet.pt(),1);
		}
		if ((event.passes_trigger(PFHT900)) || event.passes_trigger( PFJET450)) {
		hist("Jet450||HT900_pT")->Fill(ersterjet.pt(),1);
		}  
	}

	}  
	
  if(Njets>=2){
  auto ersterjet = event.jets->at(0);
  auto zweiterjet= event.jets->at(1);

   
    if (event.passes_trigger(PFJET320)){							       			
      //~ hist("JET_320_pT")->Fill(ersterjet.pt(),1);
      hist("JET_320_Dijetmasse")->Fill(Mjj_max,1);						//jet1.v4() + jet2.v4() --> Mjj_max
      if (event.passes_trigger(PFJET450)) {
	//~ hist("JET_320_450_pT")->Fill(ersterjet.pt(),1);		//jet1.pt()
	hist("JET_320_450_Dijetmasse")->Fill(Mjj_max,1);		//jet1.v4() + jet2.v4()
				
      }		
			
    }
	
    if (event.passes_trigger(PFHT650)){
	    hist("HT_650_Dijetmasse")->Fill(Mjj_max,1);		//jet1.v4() + jet2.v4()
		if (event.passes_trigger(PFHT900)) {
		hist("HT_650_900_Dijetmasse")->Fill(Mjj_max,1);			//jet1.v4() + jet2.v4()).M()		      						
		}	
		if ((event.passes_trigger(PFHT900)) || event.passes_trigger( PFJET450)) {
		hist("Jet450||HT900_Dijetmasse")->Fill(Mjj_max,1);		//(jet1.v4() + jet2.v4()).M()
		}
    }
  }
}
  
  //2017

if(event.year=="2017v2"){	

	auto ersterjet = event.jets->at(0);
	auto zweiterjet= event.jets->at(1);

	auto PFHT1050 = event.get_trigger_index("HLT_PFHT1050_v*");
	auto PFJET500 = event.get_trigger_index("HLT_PFJet500_v*");
	
	auto PFHT680 = event.get_trigger_index("HLT_PFHT680_v*");
	auto PFJET400 = event.get_trigger_index("HLT_PFJet400_v*");
	
	if(Njets>=1){ 
		

	if (event.passes_trigger(PFJET400)){							       			
		hist("JET_400_pT")->Fill(ersterjet.pt(),1);
		if (event.passes_trigger(PFJET500)) {
		hist("JET_400_500_pT")->Fill(ersterjet.pt(),1);
		}
	}
	
	if (event.passes_trigger(PFHT680)){
		hist("HT_680_pT")->Fill(ersterjet.pt(),1);
		if (event.passes_trigger(PFHT1050)) {
		hist("HT_680_1050_pT")->Fill(ersterjet.pt(),1);
		}
		if ((event.passes_trigger(PFHT1050)) || event.passes_trigger( PFJET500)) {
		hist("Jet500||HT1050_pT")->Fill(ersterjet.pt(),1);
		}  
	}		
		
	}
	
	if(Njets>=2){
		
	if (event.passes_trigger(PFJET400)){							       			
	hist("JET_400_Dijetmasse")->Fill(Mjj_max,1);
	if (event.passes_trigger( PFJET500)) {
	 hist("JET_400_500_Dijetmasse")->Fill(Mjj_max,1);  
	}
	}
	
	if (event.passes_trigger(PFHT680)){
	hist("HT_680_Dijetmasse")->Fill(Mjj_max,1);
		if (event.passes_trigger(PFHT1050)) {
		hist("HT_680_1050_Dijetmasse")->Fill(Mjj_max,1);
		}
		if ((event.passes_trigger(PFHT1050)) || event.passes_trigger( PFJET500)) {
		hist("Jet500||HT1050_Dijetmasse")->Fill(Mjj_max,1);
		}  
	}		
		
}
}
	
	//2018
if(event.year=="2018"){	

	auto ersterjet = event.jets->at(0);
	auto zweiterjet= event.jets->at(1);

	auto PFHT1050 = event.get_trigger_index("HLT_PFHT1050_v*");
	auto PFJET500 = event.get_trigger_index("HLT_PFJet500_v*");
	
	auto PFHT680 = event.get_trigger_index("HLT_PFHT680_v*");
	auto PFJET400 = event.get_trigger_index("HLT_PFJet400_v*");
	
	if(Njets>=1){ 
			
	if (event.passes_trigger(PFJET400)){							       			
		hist("JET_400_pT")->Fill(ersterjet.pt(),1);
		if (event.passes_trigger(PFJET500)) {
		hist("JET_400_500_pT")->Fill(ersterjet.pt(),1);
		}
	}
	
	
	if (event.passes_trigger(PFHT680)){
		hist("HT_680_pT")->Fill(ersterjet.pt(),1);
		if (event.passes_trigger(PFHT1050)) {
		hist("HT_680_1050_pT")->Fill(ersterjet.pt(),1);
		}
		if ((event.passes_trigger(PFHT1050)) || event.passes_trigger( PFJET500)) {
		hist("Jet500||HT1050_pT")->Fill(ersterjet.pt(),1);
		}  
	}		
		
	}
	
	if(Njets>=2){
		
	if (event.passes_trigger(PFJET400)){							       			
	hist("JET_400_Dijetmasse")->Fill(Mjj_max,1);
	if (event.passes_trigger( PFJET500)) {
	 hist("JET_400_500_Dijetmasse")->Fill(Mjj_max,1);
	}
	}
	
	if (event.passes_trigger(PFHT680)){
	hist("HT_680_Dijetmasse")->Fill(Mjj_max,1);
		if (event.passes_trigger(PFHT1050)) {
		hist("HT_680_1050_Dijetmasse")->Fill(Mjj_max,1);
		}
		if ((event.passes_trigger(PFHT1050)) || event.passes_trigger( PFJET500)) {
		hist("Jet500||HT1050_Dijetmasse")->Fill(Mjj_max,1);
		}  
	}		
				
	//~ if ((event.passes_trigger(PFHT1050)) || event.passes_trigger( PFJET500)) {
	//~ hist("Jet500||HT1500_Dijetmasse")->Fill(Mjj_max,1);	
	//~ }
}
}
}

DijetAngularAnalysisTrigger::~DijetAngularAnalysisTrigger(){}
