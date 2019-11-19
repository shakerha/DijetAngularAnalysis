#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisSelections.h"
#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisCommon.h"

#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisHists.h"

#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisTriggerHists.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/MCLargeWeightKiller.h"

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   * 
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class DijetAngularAnalysisModule: public AnalysisModule {
  public:
    
    explicit DijetAngularAnalysisModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    
    std::unique_ptr<CommonModules> common;
    
    
    std::unique_ptr<MCLargeWeightKiller> mcSpikeKiller;
    std::unique_ptr<JetCleaner> jetcleaner;
   
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    std::unique_ptr<Selection> njet_sel, dijet_sel, test_sel, h_rapidity_sel, h_pT_sel, h_chi_sel, h_yboost_sel, h_triggerJET450_sel, h_triggerHT900_sel, h_mjj_sel, h_triggerJET500_sel, h_triggerHT1050_sel;
                                                                                                                                                                   
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_nocuts,h_nocuts_preCommon, h_njet, h_dijet,h_test, h_ele, h_MjjBin1p9To2p4, h_MjjBin2p4To3p0, h_MjjBin3p0To3p6, h_MjjBin3p6To4p2, h_MjjBin4p2To4p8, h_MjjBin4p8To7p0, h_MjjBin7p0ToInf, h_rapidity, h_pT, h_chi, h_yboost, h_mjj, h_triggerJET450HT900, h_triggerHT900, h_triggerJET500HT1050, h_triggerHT1050, h_triggereff;   
    
    
  };


  DijetAngularAnalysisModule::DijetAngularAnalysisModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from DijetAngulartyAnalysisModule!" << endl;
    
    // If needed, access the configuration of the module here, e.g.:h_triggerJET450HT900
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;
    
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }
    
    // 1. setup other modules. CommonModules and the JetCleaner:
    common.reset(new CommonModules());
    
    mcSpikeKiller.reset(new MCLargeWeightKiller(
								 ctx,
								 2, // maximum allowed ratio of leading reco jet pT / generator HT
                                 2, // maximum allowed ratio of leading gen jet pT / generator HT
                                 2, // maximum allowed ratio of leading reco jet pT / Q scale
                                 2, // maximum allowed ratio of PU maximum pTHat / gen HT (ensures scale of PU < scale of hard interaction)
                                 2, // maximum allowed ratio of leading reco jet pT / pTHat
                                 2 // maximum allowed ratio of leading gen jet pT / pTHat
	));
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    common->switch_jetPtSorter(true);
    common->disable_jec();
    common->disable_jersmear();
    common->init(ctx);
    jetcleaner.reset(new JetCleaner(ctx, 30.0, 2.4)); 
    
    // note that the JetCleaner is only kept for the sake of example;
    // instead of constructing a jetcleaner explicitly,
    // the cleaning can also be achieved with less code via CommonModules with:
    // common->set_jet_id(PtEtaCut(30.0, 2.4));
    // before the 'common->init(ctx)' line.

    // 2. set up selections
    //~ njet_sel.reset(new NJetSelection(2)); // see common/include/NSelections.h
    //~ dijet_sel.reset(new DijetSelection()); // see DijetAngularAnalysisSelections
    //test_sel.reset(new DijetSelection2());// see DijetAngularAnalysisSelections
	
    h_rapidity_sel.reset(new Rapidity_sel());
    h_mjj_sel.reset(new mjj_sel());
    h_pT_sel.reset(new pT_sel(550));
    h_chi_sel.reset(new chi_sel());
    h_yboost_sel.reset(new yboost_sel());
    h_triggerJET450_sel.reset(new TriggerSelection("HLT_PFJet450_v*"));																						//ABBRUCH
    h_triggerHT900_sel.reset(new TriggerSelection("HLT_PFHT900_v*"));
    h_triggerJET500_sel.reset(new TriggerSelection("HLT_PFJet500_v*"));	
    h_triggerHT1050_sel.reset(new TriggerSelection("HLT_PFHT1050_v*"));
	
	
    // 3. Set up Hists classes1
    h_ele.reset(new ElectronHists(ctx, "ele_nocuts"));
    h_nocuts_preCommon.reset(new DijetAngularAnalysisHists(ctx, "NoCutsPreCommon"));
    h_nocuts.reset(new DijetAngularAnalysisHists(ctx, "NoCuts"));
    h_triggereff.reset(new DijetAngularAnalysisTrigger(ctx, "Triggereff"));
    h_njet.reset(new DijetAngularAnalysisHists(ctx, "Njet"));
    //h_dijet.reset(new DijetAngularAnalysisHists(ctx, "Dijet"));
    //h_test.reset(new DijetAngularAnalysisHists(ctx, "test"));
    h_triggerJET450HT900.reset(new DijetAngularAnalysisHists(ctx, "Trigger16"));
    h_triggerJET500HT1050.reset(new DijetAngularAnalysisHists(ctx, "Trigger17/18"));
    h_rapidity.reset(new DijetAngularAnalysisHists(ctx, "Rapidity"));
    h_pT.reset(new DijetAngularAnalysisHists(ctx, "pT"));
    h_chi.reset(new DijetAngularAnalysisHists(ctx, "#chi"));
    h_yboost.reset(new DijetAngularAnalysisHists(ctx, "y_boost"));
    h_mjj.reset(new DijetAngularAnalysisHists(ctx, "Mjj"));
    //~ h_MjjBin1p9To2p4.reset(new DijetAngularAnalysisHists(ctx, "MjjBin1p9To2p4"));
    h_MjjBin2p4To3p0.reset(new DijetAngularAnalysisHists(ctx, "MjjBin2p4To3p0"));
    h_MjjBin3p0To3p6.reset(new DijetAngularAnalysisHists(ctx, "MjjBin3p0To3p6"));
    h_MjjBin3p6To4p2.reset(new DijetAngularAnalysisHists(ctx, "MjjBin3p6To4p2"));
    h_MjjBin4p2To4p8.reset(new DijetAngularAnalysisHists(ctx, "MjjBin4p2To4p8"));
    h_MjjBin4p8To7p0.reset(new DijetAngularAnalysisHists(ctx, "MjjBin4p8To7p0"));
    h_MjjBin7p0ToInf.reset(new DijetAngularAnalysisHists(ctx, "MjjBin7p0ToInf"));
	
	
  }


  bool DijetAngularAnalysisModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    //cout << "DijetAngularAnalysisModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
    //if (event.event != 13600103) return false;
 
    //~ cout << "PRE COMMONMODULES Found bad event in event: " << event.event << endl;
	//~ auto jet1 = event.jets->at(0);
	//~ cout << "jet1: " << jet1.pt() << " : " << jet1.eta() << " : " << jet1.phi() << endl;
 	//~ auto jet2 = event.jets->at(1);
	//~ cout << "jet2: " << jet2.pt() << " : " << jet2.eta() << " : " << jet2.phi() << endl;


    // 1. run all modules other modules.
    h_nocuts_preCommon->fill(event);
    bool commonPass = common->process(event);
    if (!commonPass) return false;
    if (!event.isRealData) {
		if (!mcSpikeKiller->passes(event)) return false;
	}
	
    jetcleaner->process(event);
    
    // 2. test selections and fill histograms
    h_ele->fill(event);
    h_nocuts->fill(event);
    
    //~ bool njet_selection = njet_sel->passes(event);
    //~ if(njet_selection){
    //~ h_njet->fill(event);
    //~ }
    //~ bool dijet_selection = dijet_sel->passes(event);
    //~ if(dijet_selection){
    //~ h_dijet->fill(event);
    //~ }
    //bool dijet_selection2 = test_sel->passes(event);
    bool passTrigger = true;
    //~ if(event.isRealData){												// nur fuer DATA, nicht MC							
    
    if(event.year == "2016v3"){ 
      bool triggJET450_selection = h_triggerJET450_sel->passes(event);
      bool triggHT900_selection = h_triggerHT900_sel->passes(event);
      passTrigger = (triggJET450_selection || triggHT900_selection);
      h_triggerJET450HT900->fill(event);
    
    }
    
    if(event.year == "2017v2" || event.year == "2018"){ 
      bool triggJET500_selection = h_triggerJET500_sel->passes(event);
      bool triggHT1050_selection = h_triggerHT1050_sel->passes(event);
      passTrigger = (triggJET500_selection || triggHT1050_selection);
      h_triggerJET500HT1050->fill(event);
    
    }
    

    
    
	

    bool dijet_selection3 = h_rapidity_sel->passes(event);
	bool dijet_selection5 = h_chi_sel->passes(event);
	bool dijet_selection6 = h_yboost_sel->passes(event);
	bool dijet_selection4 = h_pT_sel->passes(event);
	bool dijet_selection7 = h_mjj_sel->passes(event);

    
	if(event.isRealData && dijet_selection3 && dijet_selection5 && dijet_selection6){
		h_triggereff->fill(event);
	}
	
	if(event.isRealData && !passTrigger) return false;
	
	if(!dijet_selection3) return false;
    h_rapidity->fill(event);
	
	if(!dijet_selection5) return false;
    h_chi->fill(event);
    
    if(!dijet_selection6) return false;
    h_yboost->fill(event);
    
    //~ if(!dijet_selection4) return false;
    //~ h_pT->fill(event);
    
    if(!dijet_selection7) return false;
    h_mjj->fill(event);
	
	//~ cout << "POST COMMONMODULES Found bad event in event: " << event.event << endl;
	 //~ jet1 = event.jets->at(0);
	//~ cout << "jet1: " << jet1.pt() << " : " << jet1.eta() << " : " << jet1.phi() << endl;
 	 //~ jet2 = event.jets->at(1);
	//~ cout << "jet2: " << jet2.pt() << " : " << jet2.eta() << " : " << jet2.phi() << endl;
 //~ 
	//~ auto gjet1 = event.genjets->at(0);
	//~ cout << "gjet1: " << gjet1.pt() << " : " << gjet1.eta() << " : " << gjet1.phi() << endl;
 	//~ auto gjet2 = event.genjets->at(1);
	//~ cout << "gjet2: " << gjet2.pt() << " : " << gjet2.eta() << " : " << gjet2.phi() << endl;
 
 
    //if(!dijet_selection2) return false;
    ////~ if(dijet_selection2){
    //h_test->fill(event);
    ////~ }
    //if(!dijet_selection3) return false;
    ////~ if(dijet_selection2){
    //h_test1->fill(event);
    //if(!dijet_selection4) return false;
    ////~ if(dijet_selection2){
    //h_test2->fill(event);
	
    Double_t Mjj=(event.jets->at(0).v4()+event.jets->at(1).v4()).M();
	
    if(Mjj < 2400)return false;
    //~ else if((Mjj>1900)&&(Mjj<2400)){
      //~ h_MjjBin1p9To2p4->fill(event);
    //~ }
    else if((Mjj>2400)&&(Mjj<3000)){
      h_MjjBin2p4To3p0->fill(event);
    }else if((Mjj>3000)&&(Mjj<3600)){
      h_MjjBin3p0To3p6->fill(event);
    }else if((Mjj>3600)&&(Mjj<4200)){
      h_MjjBin3p6To4p2->fill(event);
    }else if((Mjj>4200)&&(Mjj<4800)){
      h_MjjBin4p2To4p8->fill(event);
    }else if((Mjj>4800)&&(Mjj<7000)){
      h_MjjBin4p8To7p0->fill(event);      
      }else{
      h_MjjBin7p0ToInf->fill(event);			
    }
		
    // 3. decide whether or not to keep the current event in the output:
    //~ return njet_selection && dijet_selection;
    return true;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the DijetAngularAnalysisModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(DijetAngularAnalysisModule)

}
