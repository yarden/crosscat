/*
 *   Copyright (c) 2010-2014, MIT Probabilistic Computing Project
 *
 *   Lead Developers: Dan Lovell and Jay Baxter
 *   Authors: Dan Lovell, Baxter Eaves, Jay Baxter, Vikash Mansinghka
 *   Research Leads: Vikash Mansinghka, Patrick Shafto
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#ifndef GUARD_cycliccomponentmodel_h
#define GUARD_cycliccomponentmodel_h

#include "ComponentModel.h"
#include "RandomNumberGenerator.h"
#include "numerics.h"
#include "utils.h"


class CyclicComponentModel : public ComponentModel {
public:
    CyclicComponentModel(std::map<std::string, double>& in_hyper_hash);
    CyclicComponentModel(std::map<std::string, double>& in_hyper_hash,
                             int COUNT, double SUM_SIN_X, double SUM_COS_X);
    virtual ~CyclicComponentModel() {};
    //
    // getters
    void get_suffstats(int& count_out, double& sum_sin_x, double& sum_cos_x_) const;
    void get_hyper_doubles(double& kappa, double& a, double& b) const;
    std::map<std::string, double> get_hypers() const;
    std::map<std::string, double> get_suffstats() const;
    std::map<std::string, double> _get_suffstats() const;
    double get_draw(int random_seed) const;
    double get_draw_constrained(int random_seed, std::vector<double> constraints) const;
    double get_predictive_cdf(double element, std::vector<double> constraints) const;
    //
    // calculators
    double calc_marginal_logp() const;
    double calc_element_predictive_logp(double element) const;
    double calc_element_predictive_logp_constrained(double element,
            std::vector<double> constraints) const;
    std::vector<double> calc_hyper_conditionals(std::string which_hyper,
            std::vector<double> hyper_grid) const;
    //
    // mutators
    double insert_element(double element);
    double remove_element(double element);
    double incorporate_hyper_update();

protected:
    void set_log_Z_0();
    void init_suffstats();
private:
    double sum_cos_x;
    double sum_sin_x;
    double hyper_kappa;         // von mises concentration
    double hyper_a;         // prior concentraion on von mises mean
    double hyper_b;         // prior mean on von mises mean [0,2*pi)
};

#endif // GUARD_cycliccomponentmodel_h
