#pragma once

#include "UHH2/core/include/Hists.h"
//~ std::vector<float> ptBins_={0,400,500,600,800,1000,1200,1400,1700,2000,2500,3000,3500,4000,4500};     
std::vector<float> ptBins_={0,400,500,600,800,1000,1200,1400,1700,2000,2500,3000,3500};     
std::vector<float> yBins_={0.5,1,1.5,1.8,2.1,2.5};

namespace uhh2examples {

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class DijetAngularAnalysisHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    DijetAngularAnalysisHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~DijetAngularAnalysisHists();
    
	bool is_mc;
	
	std::vector<float> ptBins=ptBins_;     
	
	std::vector<float> yBins=yBins_;
};


}
