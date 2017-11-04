#include "network.h"


///Network Constructor
Network::Network ()
:neurons_targets(nb_neurons, std::vector<int>(conn_tot)), neurons_(nb_neurons)										// containing each the place (int) of a random neuron it is connected to
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> random_targets(0, nb_neurons-1);
	
	
	for (size_t i(0); i < nb_neurons; ++i) {
		for(size_t j(0); j < conn_tot; ++j) {
			neurons_targets[i][j] = random_targets(gen);
		}
	}
/** This code enables us to iniate the matrix with a random number in each 
 * cases corresponding to a neuron number, so each neurons i will be 
 * connected to randomly chosen neurons.
 */
}																			


///---------------------------------------------------------------------
///---------------------------------------------------------------------




///Network ask method
void Network::ask_display() {

	while (start_step <= 0 or start_step >= stop_time) {											
		std::cout << "Please inserteth the beginnig step (>0 & <2000) :" << std::endl;			
		std::cin >> start_step;
		if (std::cin.fail() or start_step >= stop_time) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
	
	
	while (stop_step <= 0 or stop_step < start_step or stop_step > stop_time) {						
		std::cout << "Please inserteth the stopping step (>beginning step & <=5000) :" << std::endl;	
		std::cin >> stop_step;
		if (std::cin.fail() or stop_step < start_step or stop_step > stop_time) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
		
		
	do {
		std::cout << "Please inserteth the current :" << std::endl;
		std::cin >> Iext;
		if (std::cin.fail()) {
			std::cout << "I'm afraid i can't do that Dave!2" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	} while (Iext < 0.0);

/** I found thoses methods on the internet, they made it possible to check 
 * if the input corresponds to what we are expecting without having to create
 * another variable only for control purpose
 * */

}



///----------------------------------------------------------------------
///----------------------------------------------------------------------



///Network running method
void Network::rum_rum() 
{		
	
	int lambda(2);
	std::random_device rd_;
	std::mt19937 generate(rd_());
	std::poisson_distribution<> poisson_distribution(lambda);
	
/** Here we generate a random poisson distribution to simulate 
 *  the external input of neurons outside of our simulation
 * */
 
//----------------------------------------------------------------------

	
//	std::ofstream Neurons_mem_pot;
//	Neurons_mem_pot.open("potentials.txt");
	
	std::ofstream Spikes;
	Spikes.open("Spikes_plot.txt");
	
	bool is_Inhib(false);
	Iext2 = Iext;
	
	while (nb_step < stop_time) 
	{	
		for (size_t i(0); i < neurons_.size(); ++i) 
		{									
			if (neurons_[i].Has_now_spiked(/*h*/) and i < (neurons_.size() - 1)) 
			{
				for (size_t j(0); j < conn_tot; ++j) 
				{						
					if (i < nb_exhit) 
					{
						is_Inhib = false;
					} 
					else 
					{
						is_Inhib = true;
					}
					neurons_[i].Send_spike(neurons_[neurons_targets[i][j]], (nb_step-1), is_Inhib);
				}
					Spikes << nb_step << '\t' << i << std::endl;
			}
			if (nb_step < start_step or nb_step > stop_step) 
			{
				neurons_[i].Update_state(Iext2, 0);
			} 
			else 
			{
				neurons_[i].Update_state(Iext2, poisson_distribution(generate));
			}
//			Neurons_mem_pot << neurons_[i].Get_membrane_potential() << '\t';
			};
//		Neurons_mem_pot << std::endl;
		++nb_step;
	};
	
//	Neurons_mem_pot.close();
	Spikes.close();
	
/** 1st step : the current input is only active inside the chosen interval of time.
 * 				outside, the current input is 0.
 * 
 * 2nd step : we check if the neuron i has spiked, if yes : send spike to every 
 * 													neurons it is connected to.
 * 
 * 3rd step : we update the neuron and write its potential in the .txt file
 * 
 * */
 }
