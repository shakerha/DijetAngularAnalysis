#include <iostream>
#include <string>
//~ #include "UHH2/core/include/Event.h"

#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TEfficiency.h"
//~ #include "UHH2/core/include/Event.h"
//~ #include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisTriggerHists.h"




using namespace std;
std::string year;

bool IsInString(const std::string & mainStr, const std::string & subStr){
	return mainStr.find(subStr) != std::string::npos;
}

Double_t findFirstXAbove(TEfficiency * efficiency,Double_t threshold);

void TriggerEfficiency(){
	gStyle->SetOptStat(0);
	
	
	TFile * f = new TFile("/nfs/dust/cms/user/shakerha/UHH2Output/data16robin/uhh2.AnalysisModuleRunner.DATA.DATA_JetHT_2016v3.root");  //sframe batch, hadd und dann hier einfügen für 17718
	//~ TFile * f = new TFile("/nfs/dust/cms/user/shakerha/UHH2Output/justdata17/uhh2.AnalysisModuleRunner.DATA.DATA_JetHT2017.root");
	//~ TFile * f = new TFile("/nfs/dust/cms/user/shakerha/UHH2Output/justQCD2018/uhh2.AnalysisModuleRunner.DATA.DATA_JetHTRun2018.root");

	
	//if(std::string(f->GetName()).find("2016") != std::string::npos){ year = "2016";}
	if(IsInString(std::string(f->GetName()), "2016")){ year = "2016";}
	if(IsInString(std::string(f->GetName()), "2017")){ year = "2017";}
	if(IsInString(std::string(f->GetName()), "2018")){ year = "2018";}
	
	
//2016		

		TCanvas *a=new TCanvas("triggEff","triggEff",600,600);
		
		float ht_trig_threshold_lower;
		float ht_trig_threshold_higher;
		
		if(year == "2016") {
			
			 ht_trig_threshold_lower = 320;
			 ht_trig_threshold_higher = 450;
			 			cout << "ht_pt_320450_400500: " << TString::Format("Triggereff/JET_%.0f_%.0f_pT",ht_trig_threshold_lower, ht_trig_threshold_higher) <<endl;
		}
	
			//~ cout << "ht_pt_320450_400500: " << TString::Format("Triggereff/JET_%.0f_%.0f_pT",ht_trig_threshold_lower, ht_trig_threshold_higher) <<endl;
//2017 && 2018

		
		if (year == "2017" || year == "2018" ) {				//|| year == "2018"
			ht_trig_threshold_lower = 400; 
			ht_trig_threshold_higher = 500;
						 			cout << "ht_pt_320450_400500: " << TString::Format("Triggereff/JET_%.0f_%.0f_pT",ht_trig_threshold_lower, ht_trig_threshold_higher) <<endl;

		}
					 			
					 						//~ ht_trig_threshold_lower = 400; 
			//~ ht_trig_threshold_higher = 500;
					 			//~ cout << "ht_pt_320450_400500: " << TString::Format("Triggereff/JET_%.0f_%.0f_pT",ht_trig_threshold_lower, ht_trig_threshold_higher) <<endl;
		
				
// TH1F

		TH1F * h_pT_320_400 = (TH1F*)f->Get(TString::Format("Triggereff/JET_%.0f_pT", ht_trig_threshold_lower));
		TH1F * h_pT_320450_400500 = (TH1F*)f->Get(TString::Format("Triggereff/JET_%.0f_%.0f_pT",ht_trig_threshold_lower, ht_trig_threshold_higher));
		
		
		TH1F * h_Dijetmasse_320_400 = (TH1F*)f->Get(TString::Format("Triggereff/JET_%.0f_Dijetmasse", ht_trig_threshold_lower));
		TH1F * h_Dijetmasse_320450_400500 = (TH1F*)f->Get(TString::Format("Triggereff/JET_%.0f_%.0f_Dijetmasse", ht_trig_threshold_lower, ht_trig_threshold_higher));
		
		

//Fitfunktion

		//~ TString turnOnFunction= "[0]*([1]+0.5*(1-[1])*(1+TMath::Erfc((x-[2])/[3])))";
		//~ 
		//~ TF1 * turnOn1 = new TF1("turnOn1",turnOnFunction,300,3000);
		//~ turnOn1->SetLineStyle(kDashed);
		//~ turnOn1->SetLineColor(kRed);
		//~ 
		//~ if (year == "2016") {
			//~ turnOn1->SetParameter(0,1);
			//~ turnOn1->SetParameter(1,0.340211);
			//~ turnOn1->SetParameter(2,400);
			//~ turnOn1->SetParameter(3,100);
		//~ } else {
			//~ turnOn1->SetParameter(0,1);
			//~ turnOn1->SetParameter(1,0.340211);
			//~ turnOn1->SetParameter(2,400);
			//~ turnOn1->SetParameter(3,100);
		//~ }
		

		
//Effizienz16

		TEfficiency* Eff_pT = new TEfficiency(*h_pT_320450_400500, *h_pT_320_400);
				//~ Eff_pT->SetTitle(TString::Format("Efficiency of PFJet%.0f (%s); leading jet p_{T} [GeV]; trigger efficiency",ht_trig_threshold_higher, year.c_str() ));
		Eff_pT->SetTitle("Efficiency;M_{jj} [GeV]; trigger efficiency");

		
		TEfficiency* Eff_Dijetmasse = new TEfficiency(*h_Dijetmasse_320450_400500, *h_Dijetmasse_320_400);
				Eff_Dijetmasse->SetTitle(TString::Format("Efficiency of PFJet%.0f (%s) ; M_{jj} [GeV]; trigger efficiency", ht_trig_threshold_higher, year.c_str()));

		Eff_pT->Draw();
		//~ Eff_pT->Fit(turnOn1,"R+");
		//~ turnOn1->Draw("SAME");
		a-> SaveAs(TString::Format("trigger%s/TriggereffJET_pt_%.0f.pdf",year.c_str(), ht_trig_threshold_higher));			
		
		Eff_Dijetmasse->Draw();
		a-> SaveAs(TString::Format("trigger%s/TriggereffJET_Dijetmasse_%.0f.pdf",year.c_str(),ht_trig_threshold_higher));
		
		
		cout << "0.99% Efficiency above PFJet0f450500 (pT) " << findFirstXAbove(Eff_pT,0.99) << " GeV!"<<endl;
		cout << "0.99% Efficiency above PFJet450500 (dijetmass) " << findFirstXAbove(Eff_Dijetmasse,0.99) << " GeV!"<<endl;

		
		
		//~ a->SetLogy();					//wenn ich Logy ausschalten moechte: c->SetLogy(0)

		auto legend = new TLegend(0.487858,0.807826,0.748516,0.884348);
		//~ legend-> AddEntry(h_pT_320_400,TString::Format("PFJet%.0f",ht_trig_threshold_lower),"PL");
		//~ legend->AddEntry(h_pT_320450_400500,TString::Format("PFJet%.0f",ht_trig_threshold_higher), "PL");
		
		legend-> AddEntry(h_pT_320_400,"Reference trigger","PL");
		legend->AddEntry(h_pT_320450_400500,"Examined trigger", "PL");
		
		h_pT_320450_400500-> SetLineColor(kRed);
		//~ h_pT_320_400-> SetTitle(TString::Format("Comparing the triggers PFJet%.0f and PFJet%.0f (%s); leading jet p_{T} [GeV]; N", ht_trig_threshold_lower,ht_trig_threshold_higher, year.c_str()));
		
		h_pT_320_400-> SetTitle("Individual triggers; M_{jj} [GeV]; N_{Events}");

		h_pT_320_400->Draw("histE1");
		h_pT_320_400->GetXaxis()->SetRangeUser(0,1500);
		h_pT_320450_400500->Draw("histE1 same");
		a->SetLogy();
		a->RedrawAxis();
		legend-> Draw();
		
		a-> SaveAs(TString::Format("trigger%s/pTsJET_%.0f_%.0f.pdf",year.c_str(),ht_trig_threshold_lower, ht_trig_threshold_higher));		//320 & 320&&450 || 320 & 320&&500
		
		auto legend2 = new TLegend(0.487858,0.807826,0.748516,0.884348);
		legend2-> AddEntry(h_Dijetmasse_320_400, TString::Format("PFJet%.0f",ht_trig_threshold_lower),"PL");
		legend2->AddEntry(h_Dijetmasse_320450_400500, TString::Format("PFJet%.0f", ht_trig_threshold_higher), "PL");
		
		h_Dijetmasse_320450_400500-> SetLineColor(kRed);
		h_Dijetmasse_320_400-> SetTitle(TString::Format("Comparing the triggers PFJet%.0f and PFJet%.0f (%s); M_{jj} [GeV]; N", ht_trig_threshold_lower,ht_trig_threshold_higher, year.c_str()));
		h_Dijetmasse_320_400->Draw("histE1");
		h_Dijetmasse_320450_400500->Draw("histE1 same");
		
		legend2->Draw();
		
		a-> SaveAs(TString::Format("trigger%s/DijetmasssJET_%.0f_%.0f.pdf",year.c_str(),ht_trig_threshold_lower, ht_trig_threshold_higher) ); 			//320 & 320&&450 || 320 & 320&&500
		
//PFHT Trigger

	TCanvas *b=new TCanvas("triggEff1","triggEff1",600,600);	

		float ht_trig_threshold_lower2;
		float ht_trig_threshold_higher2;
		
		if(year == "2016") {
			
			ht_trig_threshold_lower2 = 650;
			ht_trig_threshold_higher2 = 900;
		}
		//~ 
		if (year == "2017" || year == "2018") {
			ht_trig_threshold_lower2 = 680; 
			ht_trig_threshold_higher2 = 1050;
			
		}
		//~ 

		
//TH1F	
		
		TH1F * h_pT_650_680 = (TH1F*)f->Get(TString::Format("Triggereff/HT_%.0f_pT", ht_trig_threshold_lower2));
		TH1F * h_pT_650900_6801050 = (TH1F*)f->Get(TString::Format("Triggereff/HT_%.0f_%.0f_pT", ht_trig_threshold_lower2, ht_trig_threshold_higher2));
		
		
		TH1F * h_Dijetmasse_650_680 = (TH1F*)f->Get(TString::Format("Triggereff/HT_%.0f_Dijetmasse", ht_trig_threshold_lower2));
		TH1F * h_Dijetmasse_650900_6801050 = (TH1F*)f->Get(TString::Format("Triggereff/HT_%.0f_%.0f_Dijetmasse", ht_trig_threshold_lower2, ht_trig_threshold_higher2));
				


		//~ TString turnOnFunction1= "[0]*([1]+0.5*(1-[1])*(1+TMath::Erfc((x-[2])/[3])))";
		//~ 
		//~ TF1 * turnOn2 = new TF1("turnOn2",turnOnFunction,300,3000);
		//~ turnOn2->SetLineStyle(kDashed);
		//~ turnOn2->SetLineColor(kRed);
		//~ 
		//~ if (year == "2016") {
			//~ turnOn2->SetParameter(0,1);
			//~ turnOn2->SetParameter(1,0.340211);
			//~ turnOn2->SetParameter(2,400);
			//~ turnOn2->SetParameter(3,100);
		//~ } else {  
			//~ turnOn2->SetParameter(0,1);
			//~ turnOn2->SetParameter(1,0.340211);
			//~ turnOn2->SetParameter(2,400);
			//~ turnOn2->SetParameter(3,100);
		//~ }

//Efficiency


		TEfficiency* Eff_HTpT = new TEfficiency(*h_pT_650900_6801050, *h_pT_650_680);
				Eff_HTpT->SetTitle(TString::Format("Efficiency of PFHT%.0f (%s); leading jet p_{T} [GeV]; trigger efficiency",ht_trig_threshold_higher2, year.c_str()));
		
		TEfficiency* Eff_HTDijetmasse = new TEfficiency(*h_Dijetmasse_650900_6801050, *h_Dijetmasse_650_680);
				Eff_HTDijetmasse->SetTitle(TString::Format("Efficiency of PFHT%.0f (%s) ; M_{jj} [GeV]; trigger efficiency", ht_trig_threshold_higher2, year.c_str()));

		Eff_HTpT->Draw();
		//~ Eff_HTpT->Fit(turnOn1,"R+");
		//~ turnOn1->Draw("SAME");
		b-> SaveAs(TString::Format("trigger%s/TriggereffJET_pt_%.0f.pdf",year.c_str(), ht_trig_threshold_higher2));			
		
		Eff_HTDijetmasse->Draw();
		b-> SaveAs(TString::Format("trigger%s/TriggereffJET_Dijetmasse_%.0f.pdf",year.c_str(),ht_trig_threshold_higher2));
		
		cout << "0.99% Efficiency above PFHT9001050 (pT) " << findFirstXAbove(Eff_HTpT,0.99) << " GeV!"<<endl;
		cout << "0.99% Efficiency above PFHT9001050 (dijetmass) " << findFirstXAbove(Eff_HTDijetmasse,0.99) << " GeV!"<<endl;

		

		//~ b->SetLogy();					//wenn ich Logy ausschalten moechte: c->SetLogy(0)

		auto legend3 = new TLegend(0.487858,0.807826,0.748516,0.884348);
		legend3-> AddEntry(h_pT_650_680, TString::Format("PFHT%.0f",ht_trig_threshold_lower2 ),"PL");
		legend3->AddEntry(h_pT_650900_6801050, TString::Format("PFHT%.0f", ht_trig_threshold_higher2), "PL");
		
		h_pT_650900_6801050-> SetLineColor(kRed);
		h_pT_650_680-> SetTitle(TString::Format("Comparing the triggers PFHT%.0f and PFHT%.0f (%s); leading jet p_{T} [GeV]; N", ht_trig_threshold_lower2,ht_trig_threshold_higher2, year.c_str()));
		h_pT_650_680->Draw("histE1");
		h_pT_650_680->GetXaxis()->SetRangeUser(0,1500);
		h_pT_650900_6801050->Draw("histE1 same");
		b-> SetLogy();
		b->RedrawAxis();
		legend3-> Draw();
		
		b-> SaveAs(TString::Format("trigger%s/pTsJET_%.0f_%.0f.pdf",year.c_str(), ht_trig_threshold_lower2, ht_trig_threshold_higher2));		//650 & 650&&900 || 680 & 680&&1050
		
		auto legend4 = new TLegend(0.487858,0.807826,0.748516,0.884348);
		legend4-> AddEntry(h_Dijetmasse_650_680, TString::Format("PFHT%.0f",ht_trig_threshold_lower2 ),"PL");
		legend4->AddEntry(h_Dijetmasse_650900_6801050,TString::Format( "PFHT%.0f", ht_trig_threshold_higher2), "PL");
		
		h_Dijetmasse_650900_6801050-> SetLineColor(kRed);
		h_Dijetmasse_650_680-> SetTitle(TString::Format("Comparing the triggers PFHT%.0f and PFHT%.0f (%s); M_{jj} [GeV]; N", ht_trig_threshold_lower2,ht_trig_threshold_higher2, year.c_str()));
		h_Dijetmasse_650_680->Draw("histE1");
		h_Dijetmasse_650900_6801050->Draw("histE1 same");
		
		legend4->Draw();
		
		b-> SaveAs(TString::Format("trigger%s/DijetmasssJET_%.0f_%.0f.pdf",year.c_str(),ht_trig_threshold_lower2, ht_trig_threshold_higher2) ); 			//650 & 650&&900 || 680 & 680&&1050
		






TCanvas *c=new TCanvas("triggEff2","triggEff2",600,600);	

		float ht_trig_threshold_low;
		float ht_trig_threshold_high;
		float ht_trig_threshold_middle;
		
		if(year == "2016") {
			
			ht_trig_threshold_low = 450;
			ht_trig_threshold_middle = 650;
			ht_trig_threshold_high = 900;
		}
		//~ 
		if (year == "2017" || year == "2018") {
			ht_trig_threshold_low = 500; 
			ht_trig_threshold_middle = 680;
			ht_trig_threshold_high = 1050;			
			
		}
		
		
		TH1F * h_Jet450HT900pT_Jet500HT1050pt = (TH1F*)f->Get(TString::Format("Triggereff/Jet%.0f||HT%.0f_pT", ht_trig_threshold_low, ht_trig_threshold_high));
		TH1F * h_Jet450HT900Dijetmasse_Jet500HT1050Dijetmasse = (TH1F*)f->Get(TString::Format("Triggereff/Jet%.0f||HT%.0f_Dijetmasse", ht_trig_threshold_low, ht_trig_threshold_high));

		TH1F * h_HT650pT_HT680pt = (TH1F*)f->Get(TString::Format("Triggereff/HT_%.0f_pT",ht_trig_threshold_middle));
		TH1F * h_HT650Dijetmasse_HT680Dijetmasse = (TH1F*)f->Get(TString::Format("Triggereff/HT_%.0f_Dijetmasse", ht_trig_threshold_middle));
		
	
		
		TEfficiency* Eff_JetHTpT = new TEfficiency(*h_Jet450HT900pT_Jet500HT1050pt, *h_HT650pT_HT680pt);						// Im Nenner nur HT650
		TEfficiency* Eff_JetHTDijetmasse = new TEfficiency(*h_Jet450HT900Dijetmasse_Jet500HT1050Dijetmasse, *h_HT650Dijetmasse_HT680Dijetmasse);
		

		//~ TString turnOnFunction2= "[0]*([1]+0.5*(1-[1])*(1+TMath::Erfc((x-[2])/[3])))";
		//~ 
		//~ TF1 * turnOn3 = new TF1("turnOn3",turnOnFunction,300,3000);
		//~ turnOn3->SetLineStyle(kDashed);
		//~ turnOn3->SetLineColor(kRed);
		//~ 
		//~ if (year == "2016") {
			//~ turnOn3->SetParameter(0,1);
			//~ turnOn3->SetParameter(1,0.340211);
			//~ turnOn3->SetParameter(2,400);
			//~ turnOn3->SetParameter(3,100);
		//~ } else {
			//~ turnOn3->SetParameter(0,1);
			//~ turnOn3->SetParameter(1,0.340211);
			//~ turnOn3->SetParameter(2,400);
			//~ turnOn3->SetParameter(3,100);
		//~ }
		
		
		Eff_JetHTpT->SetTitle(TString::Format("Efficiency of PFJet%.0f || PFHT%.0f (%s); leading jet p_{T} [GeV]; trigger efficiency ", ht_trig_threshold_low, ht_trig_threshold_high, year.c_str()));
		Eff_JetHTDijetmasse->SetTitle(TString::Format("Efficiency of PFJet%.0f || PFHT%.0f  (%s); M_{jj} [GeV]; trigger efficiency)", ht_trig_threshold_low, ht_trig_threshold_high,year.c_str()));
		
		
		Eff_JetHTpT->Draw();
		cout << "0.99% Efficiency above PFJet450500 || PFHT9001050 (pT) " << findFirstXAbove(Eff_JetHTpT,0.99) << " GeV!"<<endl;
		c-> SaveAs(TString::Format("trigger%s/TriggereffJetHT_%.0f_%.0f_pT.pdf",year.c_str(), ht_trig_threshold_low, ht_trig_threshold_high));			
		Eff_JetHTDijetmasse->Draw();
		cout << "0.99% Efficiency above PFJet450500 || PFHT9001050 (dijetmass) " << findFirstXAbove(Eff_JetHTDijetmasse,0.99) << " GeV!"<<endl;

		c-> SaveAs(TString::Format("trigger%s/TriggereffJetHT_%.0f_%.0f_Dijetmasse.pdf",year.c_str(), ht_trig_threshold_low, ht_trig_threshold_high));


							//wenn ich Logy ausschalten moechte: c->SetLogy(0)
		//~ h_HT650pT_HT680pt-> SetLineColor();
		auto legend5 = new TLegend(0.487858,0.807826,0.748516,0.884348);
		legend5-> AddEntry(h_HT650pT_HT680pt, TString::Format("PFHT%.0f", ht_trig_threshold_middle),"PL");
		legend5->AddEntry(h_Jet450HT900pT_Jet500HT1050pt, TString::Format("PFJet%.0f||PFHT%.0f",ht_trig_threshold_high, ht_trig_threshold_low) , "PL");
		
		h_Jet450HT900pT_Jet500HT1050pt-> SetLineColor(kRed);
		h_HT650pT_HT680pt-> SetTitle(TString::Format("Comparing the triggers PFHT%.0f and PFJet%.0f || PFHT%.0f (%s); leading jet p_{T} [GeV] ; N",ht_trig_threshold_middle,ht_trig_threshold_low, ht_trig_threshold_high, year.c_str()));
		h_HT650pT_HT680pt->Draw("H1");
		h_Jet450HT900pT_Jet500HT1050pt->Draw("H1same");
		c->SetLogy();
		c->RedrawAxis();
		
		
		legend5 ->Draw(); ///////////////////////////////////////////		h_pT_320_400->Draw("H1");
		//~ h_pT_320_400->GetXaxis()->SetRangeUser(0,1500);
		//~ h_pT_320450_400500->Draw("H1same");
		//~ a->SetLogy();
		//~ a->RedrawAxis();
		//~ legend-> Draw();
		
		c-> SaveAs(TString::Format("trigger%s/pTsJetHT_HT%.0f_Jet%.0f.pdf",year.c_str(),ht_trig_threshold_high,ht_trig_threshold_low));
		
		auto legend6 = new TLegend(0.487858,0.807826,0.748516,0.884348);
		legend6-> AddEntry(h_HT650Dijetmasse_HT680Dijetmasse, TString::Format("PFHT%.0f", ht_trig_threshold_middle),"PL");
		legend6->AddEntry(h_Jet450HT900Dijetmasse_Jet500HT1050Dijetmasse, TString::Format("PFJet%.0f||PFHT%.0f",ht_trig_threshold_high, ht_trig_threshold_low) , "PL");
		
		h_Jet450HT900Dijetmasse_Jet500HT1050Dijetmasse-> SetLineColor(kRed);
		h_HT650Dijetmasse_HT680Dijetmasse-> SetTitle(TString::Format("Comparing the triggers PFHT%.0f and PFJet%.0f || PFHT%.0f (%s); M_{jj} [GeV] ; N",ht_trig_threshold_middle,ht_trig_threshold_low, ht_trig_threshold_high, year.c_str()));
		h_HT650Dijetmasse_HT680Dijetmasse->Draw();
		h_Jet450HT900Dijetmasse_Jet500HT1050Dijetmasse->Draw("histE1 same");
		
		legend6->Draw();
		
		c-> SaveAs(TString::Format("trigger%s/DijetmassJetHT_%.0f_Jet%.0f.pdf", year.c_str(),ht_trig_threshold_high,ht_trig_threshold_low));



}



Double_t findFirstXAbove(TEfficiency * efficiency,Double_t threshold){
	TGraphAsymmErrors * graph = efficiency->CreateGraph();
	Double_t  x,y;
	Double_t firstXAbove=0;
	for(int k=1;k<graph->GetN();k++){
		graph->GetPoint(k,x,y);
		firstXAbove=x;
		if(y>threshold)break;
	}
	return firstXAbove;
}

