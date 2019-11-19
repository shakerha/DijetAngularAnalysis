//~ #include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisHists.h"
#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisCommon.h"
#include <iostream>
#include <vector>

#include "TH1.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TFile.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TCanvas.h"
#include "TLegend.h"


using namespace std;
void PlotResolution(TH1F * h_resolution16,TH1F * h_resolution17,TH1F * h_resolution18, float sigma16, float sigma17, float sigma18, float mean16, float mean17, float mean18, TString OutputName);
//~ wenn data 17,18 da, dann TH1F h_resolution17,TH1F h_resolution18
//~ vector<float> fitResolution(TH1F h_resolution16);  	//WAS IST DAS?
//~ vector<float> fitResolution(TH1F h_resolution17);
//~ vector<float> fitResolution(TH1F h_resolution18);


TFitResultPtr fitResolution(TH1F * h_resolution);							
void PlotResolutionGraph(TGraphErrors * graph16,TGraphErrors * graph17,TGraphErrors * graph18, TString OutputName);




void Resolution(){
	   //~ gStyle->SetOptFit(1);
	   gStyle->SetOptStat(0);
	   
TString dir = "pT";			//Mjj
TFile *File_2016 = new TFile("/nfs/dust/cms/user/shakerha/UHH2Output/2016/reso.root");
TFile *File_2017= new TFile("/nfs/dust/cms/user/shakerha/UHH2Output/2017/reso.root");
TFile *File_2018 = new TFile("/nfs/dust/cms/user/shakerha/UHH2Output/2018/reso.root");


	//~ auto jet2 = event.jets->at(1);
	auto K=DijetVars::yBins_.size();
	cout << K << endl;
	for (uint j=0; j<=K-2; j++)
	{
		float ymin=DijetVars::yBins_[j]; //ymin=yBins_[j];
		float ymax=DijetVars::yBins_[j+1]; //ymax=yBins_[j+1];
	
		auto N=DijetVars::ptBins_.size();
	
		std::vector<float> sigma16Values;
		std::vector<float> sigmaError16Values;
		std::vector<float> pt16Values;
		std::vector<float> ptError16Values;
		std::vector<float> sigma17Values;
		std::vector<float> sigmaError17Values;
		std::vector<float> pt17Values;
		std::vector<float> ptError17Values;
		std::vector<float> sigma18Values;
		std::vector<float> sigmaError18Values;
		std::vector<float> pt18Values;
		std::vector<float> ptError18Values;
		
	
		for(uint i=0;i <= N-2 ;i++)
		{
		   float sigma16=0;
		   float sigma17=0;
		   float sigma18=0;
		   
		   float mean16=0;
		   float mean17=0;
		   float mean18=0;
		   
	       float ptMin=DijetVars::ptBins_[i]; //ptMin=ptBins_[i];
	       float ptMax=DijetVars::ptBins_[i+1]; //ptMax=ptBins_[i+1];

			//~ if(ptMin<jet2.pt() && jet2.pt()<ptMax){																	//no need
			TString  name = TString::Format("response_pt%.0fto%.0f_y%.2fto%.2f", ptMin, ptMax, ymin, ymax);
			TString histName = dir + "/" + name;
	
			cout << "histname: " << histName << endl;
	
			TString OutputName = dir + "_" + name;										//"MjjBin2p4To3p0_response_pt%.0fto%.0f_y%.2fto%.2f"
	
			TH1F * h_resolution16 = (TH1F*)File_2016->Get(histName);
			TH1F * h_resolution17 = (TH1F*)File_2017->Get(histName);						
			TH1F * h_resolution18 = (TH1F*)File_2018->Get(histName);				
		
		
			if (h_resolution16 == nullptr) 
			{
				cout << "Could not get h_resolution16 from file" << endl;
				continue;
			}
						if (h_resolution17 == nullptr) 
			{
				cout << "Could not get h_resolution17 from file" << endl;
				continue;
			}
						if (h_resolution18 == nullptr) 
			{
				cout << "Could not get h_resolution18 from file" << endl;
				continue;
			}

			h_resolution16->SetTitle(TString::Format("%.0f < p_{T} < %.0f GeV, %.2f < y < %.2f; response; A.U.", ptMin, ptMax, ymin, ymax));
			if(h_resolution16->Integral() > 0) h_resolution16->Scale(1./h_resolution16->Integral());
			if(h_resolution17->Integral() > 0) h_resolution17->Scale(1./h_resolution17->Integral());
			if(h_resolution18->Integral() > 0) h_resolution18->Scale(1./h_resolution18->Integral());
	
			
			int minEntries = 100;
			if (h_resolution16->GetEntries() > minEntries){
				cout << "Fitting 16" << endl;
				TFitResultPtr fitResult16 = fitResolution(h_resolution16);
				if (fitResult16.Get()) {
					sigma16 = fitResult16->Parameter(2);
					float sigmaErr16 = fitResult16->ParError(2);
					
					mean16 = fitResult16->Parameter(1);
		
					sigma16Values.push_back(sigma16);
					sigmaError16Values.push_back(sigmaErr16);
					pt16Values.push_back((ptMin+ptMax)/2);
					ptError16Values.push_back((ptMax-ptMin)/2);
				}
			}
			
						
			if (h_resolution17->GetEntries() > minEntries){
								cout << "Fitting 17" << endl;

				TFitResultPtr fitResult17 = fitResolution(h_resolution17);
				if (fitResult17.Get()) {
					 sigma17 = fitResult17->Parameter(2);
					float sigmaErr17 = fitResult17->ParError(2);
					
					mean17 = fitResult17->Parameter(1);
				
					sigma17Values.push_back(sigma17);
					sigmaError17Values.push_back(sigmaErr17);
					pt17Values.push_back((ptMin+ptMax)/2);
					ptError17Values.push_back((ptMax-ptMin)/2);
				}
			}
			
			
			if (h_resolution18->GetEntries() > minEntries){
								cout << "Fitting 18" << endl;

				TFitResultPtr fitResult18 = fitResolution(h_resolution18);
				if (fitResult18.Get()) {

					 sigma18 = fitResult18->Parameter(2);
					float sigmaErr18 = fitResult18->ParError(2);
		
					mean18 = fitResult18->Parameter(1);	
					
					sigma18Values.push_back(sigma18);
					sigmaError18Values.push_back(sigmaErr18);
					pt18Values.push_back((ptMin+ptMax)/2);
					ptError18Values.push_back((ptMax-ptMin)/2);
				}
			}
			
			//~ PlotResolution(h_resolution16,OutputName);																		//HERE IS THE PROBLEM
			//~ PlotResolution(h_resolution16,h_resolution17,h_resolution18, OutputName);				//was ist mit OutputName?
			PlotResolution(h_resolution16,h_resolution17,h_resolution18, sigma16,sigma17, sigma18, mean16, mean17, mean18,OutputName);	
			
	

	
			//~ fitResolution(h_resolution16,h_resolution17,h_resolution18);
		

			//}
		}
		
		
		TGraphErrors * graph16 = new TGraphErrors(sigma16Values.size(), &pt16Values[0], &sigma16Values[0], &ptError16Values[0], &sigmaError16Values[0]);
		TGraphErrors * graph17 = new TGraphErrors(sigma17Values.size(), &pt17Values[0], &sigma17Values[0], &ptError17Values[0], &sigmaError17Values[0]);
		TGraphErrors * graph18 = new TGraphErrors(sigma18Values.size(), &pt18Values[0], &sigma18Values[0], &ptError18Values[0], &sigmaError18Values[0]);
		graph16->SetTitle(TString::Format("%.2f < y < %.2f", ymin, ymax));
		TString  graphname = TString::Format("sigmaplot_y%.2f_to_y_%.2f",  ymin, ymax);
		TString GraphOutputName = dir + "_" + graphname;
		cout << "Making graph " << GraphOutputName << endl;
		PlotResolutionGraph(graph16, graph17, graph18, GraphOutputName);
		


			}
}

//~ void PlotResolution(TH1F * h_resolution16,TString OutputName){
void PlotResolution(TH1F * h_resolution16,TH1F * h_resolution17,TH1F * h_resolution18, float sigma16, float sigma17, float sigma18, float mean16, float mean17, float mean18,TString OutputName){


	TCanvas *c=new TCanvas("Resolution","Resolution",600,600);

	h_resolution16-> SetLineColor(kBlack);
	h_resolution16->GetXaxis()->SetRangeUser(-1,1);
	h_resolution16->GetYaxis()->SetRangeUser(0.001,0.45);													// PROBLEME BEI LOGYYYYYYY

	h_resolution16-> Draw("hist");
	TF1 * fit16 = h_resolution16->GetFunction("gausfunc");
	if (fit16) {
		fit16->SetLineColor(kBlack);
		fit16->Draw("SAME");
	}
	
	
	h_resolution17-> SetLineColor(kBlue);
	h_resolution17->Draw("histSAME");
	TF1 * fit17 = h_resolution17->GetFunction("gausfunc");
	if (fit17) {
		fit17->SetLineColor(kBlue);
		fit17->Draw("SAME");
	}
	
	
	h_resolution18->SetLineColor(kPink);
	h_resolution18->Draw("histSAME");
	TF1 * fit18 = h_resolution18->GetFunction("gausfunc");
	if (fit18) {
		fit18->SetLineColor(kPink);
		fit18->Draw("SAME");
	}

	
	//LEGEND ALLE KKOMPONENTEN WIE LINIE,SIGMA etc.
	
	//~ TFitResultPtr fitresult18 = fitResolution(h_resolution);
	
	auto legend7 = new TLegend(0.150000,0.550000,0.500000,0.884348);
	legend7->SetBorderSize(0);
	legend7->SetFillStyle(0);
	legend7->SetNColumns(1);
	legend7-> AddEntry(h_resolution16, "2016 ", "PL");
	legend7->AddEntry((TObject*)0, TString::Format("#sigma_{16} = %.4f",sigma16), "");
	legend7->AddEntry((TObject*)0, TString::Format("#mu_{16} = %.4f",mean16), "");
	legend7->AddEntry((TObject*)0, "", "");
	legend7-> AddEntry(h_resolution17, "2017 ", "PL");
	legend7->AddEntry((TObject*)0, TString::Format("#sigma_{17} = %.4f",sigma17), "");
	legend7->AddEntry((TObject*)0, TString::Format("#mu_{17} = %.4f",mean17), "");	
	legend7->AddEntry((TObject*)0, "", "");
	legend7-> AddEntry(h_resolution18, "2018 ", "PL");
	legend7->AddEntry((TObject*)0, TString::Format("#sigma_{18} = %.4f",sigma18), "");
	legend7->AddEntry((TObject*)0, TString::Format("#mu_{18} = %.4f",mean18), "");
	
	legend7 ->Draw();
	
	cout <<OutputName<< endl;
	c->SetLeftMargin(0.15);
	c->SaveAs(OutputName+".pdf");

	c->SetLogy(1);
	c->SaveAs(OutputName+"_logY.pdf");

	delete c;

}


TFitResultPtr fitResolution(TH1F * h_resolution){
	TString gaus = "[p0]*TMath::Exp((-0.5*((x-[mean])/[sigma])**(2)))";
	
	TF1 *gausfunc = new TF1("gausfunc", gaus , -2,3);
	//gausfunc->SetLineStyle(kDashed);
	//gausfunc->SetLineColor(kYellow);
	gausfunc->SetNpx(500);

	
		
		float GetMean = h_resolution-> GetMean();
		float GetRMS = h_resolution-> GetRMS();
		gausfunc ->SetRange(GetMean - 2*GetRMS, GetMean + 2*GetRMS);
		
		gausfunc->SetParameter(0, h_resolution->GetMaximum());
		gausfunc->SetParameter(1, h_resolution->GetMean());
		gausfunc->SetParameter(2, h_resolution->GetRMS());
		
		TFitResultPtr fitResult = h_resolution-> Fit(gausfunc,"RS");
	
		std::cout << "p0 "<< gausfunc->GetParameter(0)<< std::endl; 
		std::cout << "mean "<< gausfunc->GetParameter(1)<< std::endl; 
		std::cout << "sigma "<< gausfunc->GetParameter(2) << std::endl;
		
		

	
	return fitResult;
	
}
	

//~ void PlotResolutionGraph(TGraphErrors * graph16, TString GraphOutputName){
void PlotResolutionGraph(TGraphErrors * graph16,TGraphErrors * graph17,TGraphErrors * graph18, TString GraphOutputName){
	
	TCanvas *d=new TCanvas("SigmaPlot","SigmaPlot",600,600);
	d->SetLeftMargin(0.15);
	auto yaxis = graph16->GetYaxis();
    //~ yaxis->SetLimits(0.0001, 0.45);
    graph16->GetHistogram()->SetMinimum(0);
    graph16->GetHistogram()->SetMaximum(0.2);
    yaxis->SetTitle("relative #sigma");
    auto xaxis = graph16->GetXaxis();
    //~ xaxis->SetLimits(-1, 1);
    xaxis->SetTitle("p_{T} [GeV]");
    graph16->SetLineColor(kBlack);

	graph16->Draw("ALP");
	 
	graph17->SetLineColor(kBlue);
	graph18->SetLineColor(kPink);
	graph17->Draw("LPsame");
	
	graph18->Draw("LPsame");																			
	
	
	auto legend6 = new TLegend(0.150000,0.650000,0.300000,0.884348); //0.600000,0.780000,0.900500,0.884348
	legend6-> AddEntry(graph16, "#sigma- fit 2016 ", "PL");
	legend6-> AddEntry(graph17, "#sigma- fit 2017 ", "PL");
	legend6-> AddEntry(graph18, "#sigma- fit 2018 ", "PL");
	
	legend6->Draw();
	
	d->SaveAs(GraphOutputName + ".pdf");
	
	delete d;
	
	
}
		
