#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"

namespace uhh2examples {
    
/* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
 * below 20% of the average of the leading two jets, where the minimum deltaphi and
 * maximum third jet pt fraction can be changed in the constructor.
 * The jets are assumed to be sorted in pt.
 */
class DijetSelection: public uhh2::Selection {
public:
    DijetSelection(float dphi_min = 2.7f, float third_frac_max = 0.2f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float dphi_min, third_frac_max;
};


}


//class DijetSelection2: public uhh2::Selection {
//public:
//    DijetSelection2(float rapi0_max = 2.5, float rapi1_max = 2.5, float pt_min=200, float yboost_min = 1.1, float chi_min = 1, float chi_max = 16);
//    virtual bool passes(const uhh2::Event & event) override;
//private:
//    float rapi0_max, rapi1_max, pt_min, yboost_min, chi_min, chi_max;
//};

class Rapidity_sel: public uhh2::Selection {
public:
    Rapidity_sel(float rapi0_max = 2.5, float rapi1_max = 2.5);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float rapi0_max, rapi1_max;
};


class pT_sel: public uhh2::Selection {
public:
    pT_sel(float pt_min=200);														// not 550
    virtual bool passes(const uhh2::Event & event) override;
private:
    float  pt_min;
};

class chi_sel: public uhh2::Selection {
public:
    chi_sel(float chi_min = 1, float chi_max = 16);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float chi_min, chi_max;
};

class yboost_sel: public uhh2::Selection {
public:
    yboost_sel(float yboost_min = 1.1);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float yboost_min;
};

class mjj_sel: public uhh2::Selection {
public:
    mjj_sel(float mjj_min = 2400);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float mjj_min;
};




//class MjjSelection1: public uhh2::Selection {
//public:
//    MjjSelection1(float energy_min = 1.9, energy_max = 2.4);
//    virtual bool passes(const uhh2::Event & event) override;
//private:
//    float energy_min, energy_max;
//};
