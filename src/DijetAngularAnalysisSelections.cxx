#include "UHH2/DijetAngularAnalysis/include/DijetAngularAnalysisSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;


DijetSelection::DijetSelection(float dphi_min_, float third_frac_max_): dphi_min(dphi_min_), third_frac_max(third_frac_max_){}
    
bool DijetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1); 
    auto dphi = deltaPhi(jet0, jet1);
    if(dphi < dphi_min) return false;
    if(event.jets->size() == 2) return true;
    const auto & jet2 = event.jets->at(2);
    auto third_jet_frac = jet2.pt() / (0.5 * (jet0.pt() + jet1.pt()));
    return third_jet_frac < third_frac_max;
}

//DijetSelection2::DijetSelection2(float rapi0_, float rapi1_, float pt, float chi_mini, float chi_maxi, float yboost_): rapi0_max(rapi0_), rapi1_max(rapi1_), pt_min(pt), chi_min(chi_mini), chi_max(chi_maxi), yboost_min(yboost_){}

//bool DijetSelection2::passes(const Event & event){
	//assert(event.jets);
	//if(event.jets->size() < 2) return false;
	//const auto & rapi0 = 0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz()));
	//const auto & rapi1 = 0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz()));
	//if(abs(rapi0) > rapi0_max) return false;
	//if(abs(rapi1) > rapi1_max) return false;
	//const auto & jet0 = event.jets->at(0);
	//const auto & jet1 = event.jets->at(1); 
	//auto pt1 = jet0.pt();
	//auto pt2 = jet1.pt();
	//if(pt1 < pt_min) return false;
	//if(pt2 < pt_min) return false;
	//auto chi_ = TMath::Exp(abs((rapi0)-(rapi1)));
	//if((chi_ < chi_min) && (chi_ > chi_max)) return false;
	//auto yboost_ = 0.5*((rapi0)+(rapi1)); 
	//if(yboost_ > yboost_min) return false;
	//return true;
//}




Rapidity_sel::Rapidity_sel(float rapi0_, float rapi1_): rapi0_max(rapi0_), rapi1_max(rapi1_){}

bool Rapidity_sel::passes(const Event & event){
	assert(event.jets);
	if(event.jets->size() < 2) return false;
	const auto & rapi0 = 0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz()));
	const auto & rapi1 = 0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz()));
	if(fabs(rapi0) > rapi0_max) return false;
	if(fabs(rapi1) > rapi1_max) return false;

	return true;
}

pT_sel::pT_sel(float pt):  pt_min(pt){}

bool pT_sel::passes(const Event & event){
	assert(event.jets);
	if(event.jets->size() < 2) return false;
	const auto & jet0 = event.jets->at(0);
	const auto & jet1 = event.jets->at(1); 
	auto pt1 = jet0.pt();
	auto pt2 = jet1.pt();
	if(pt1 < pt_min) return false;
	if(pt2 < pt_min) return false;
	return true;
}

chi_sel::chi_sel(float chi_mini, float chi_maxi): chi_min(chi_mini), chi_max(chi_maxi){}

bool chi_sel::passes(const Event & event){
	assert(event.jets);
	if(event.jets->size() < 2) return false;
	const auto & rapi0 = 0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz()));
	const auto & rapi1 = 0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz()));
	auto chi_ = TMath::Exp(fabs((rapi0)-(rapi1)));
	if((chi_ < chi_min) || (chi_ > chi_max)) return false;  // (chi_ >= chi_max) ?
	return true;
}


yboost_sel::yboost_sel(float yboost): yboost_min(yboost){}

bool yboost_sel::passes(const Event & event){
	assert(event.jets);
	if(event.jets->size() < 2) return false;
	const auto & rapi0 = 0.5*TMath::Log((event.jets->at(0).energy()+event.jets->at(0).v4().Pz())/(event.jets->at(0).energy()-event.jets->at(0).v4().Pz()));
	const auto & rapi1 = 0.5*TMath::Log((event.jets->at(1).energy()+event.jets->at(1).v4().Pz())/(event.jets->at(1).energy()-event.jets->at(1).v4().Pz()));
	auto yboost_ = 0.5*((rapi0)+(rapi1)); 
	if(fabs(yboost_) > fabs(yboost_min)) return false;		//fabs(yboost_) >= fabs(yboost_min)?
	return true;
}

mjj_sel::mjj_sel(float mjjmin): mjj_min(mjjmin){}

bool mjj_sel::passes(const Event & event){
	assert(event.jets);
	if(event.jets->size() < 2) return false;
	auto mjj = (event.jets->at(0).v4()+event.jets->at(1).v4()).M();
	if(fabs(mjj) < fabs(mjj_min)) return false;		
	return true;
}



//MjjSelection1::MjjSelection1(float energy_j1, float energy_j2): energy1(energy_j1), energy2(energy_j2)({}
//
//bool MjjSelection1::passes(const Event & event){
//	assert(event.jets)
//	if(event.jets->size() < 2) return false;
//	auto energy1 = event.jets->at(0).energy()
//	auto energy2 = event.jets->at(1).energy()
//	if((energy_j1 < energy_min) && (energy_j2 > energy_max)) return false
	
	
