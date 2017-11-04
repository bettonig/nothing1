#include "neuron.h"
#include <climits>
#include <fstream>
#include <string>
#include <random>

#ifndef NETWORK_H
#define NETWORK_H

class Network {
	
	private:
	
		std::vector<std::vector<int>> neurons_targets;					// neurons_targets : for each i neurons there is j columns of connections,
		std::vector<Neuron> neurons_;									// containing each the place (int) of a random neuron it is connected to
																		// neurons_ : This vector contains the complete list of Neurons
	
		int stop_time = 10000;
		int start_step = 0;
		int stop_step = 0;
		int nb_step = 0;
		//const double h(0.1); //ms										// interval
	
		double Iext = 0.0;		//pA
		double Iext2 = 0.0;		//pA									// Current 
	

		static constexpr int nb_neurons = 12500; 
		static constexpr int nb_exhit = (4*nb_neurons/5); //10000				nb of excitatory Neurons
		static constexpr int nb_inhib = (1*nb_neurons/5); //2500				nb of inhibitory Neurons
	
		static constexpr int exhit_conn = (nb_exhit/10); //1000					nb of connections to an excitatory neuron
		static constexpr int inhib_conn = (nb_inhib/10); //250					nb of connections to an inhibitatory neuron
		static constexpr int conn_tot = (exhit_conn + inhib_conn); //1250	
	
	public:
		
		Network();
	
		void ask_display();
		void rum_rum();
};

#endif
