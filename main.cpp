#include "neuron.h"
#include <iostream>
#include <climits>
#include <fstream>
#include <string>
#include <array>
#include <random>
//#include <iomanip>
//using namespace std;

//void write_membrane_pot (string file_out_, double membrane_pot);


int main()
{

	/*const*/int stop_time(2000);
	int start_step(0);
	int stop_step(0);
	int nb_step(0);
	//const double h(0.1); //ms											// interval
	
	double Iext(0.0);		//pA
	double Iext2(0.0);		//pA										// Current 
	

	constexpr int nb_neurons(12500); //12500
	constexpr int nb_exhit(4*nb_neurons/5); //10000						nb of excitatory Neurons
	constexpr int nb_inhib(1*nb_neurons/5); //2500						nb of inhibitory Neurons
	
	constexpr int exhit_conn(nb_exhit/10); //1000						nb of connections to an excitatory neuron
	constexpr int inhib_conn(nb_inhib/10); //250						nb of connections to an inhibitatory neuron
	constexpr int conn_tot(exhit_conn + inhib_conn); //1250				each neurons is connected to 1 every 10 neurons
		
		
	std::vector<std::vector<int>> neurons_targets(nb_neurons, std::vector<int>(conn_tot));	// neurons_targets : for each i neurons there is j columns of connections,
	std::vector<Neuron> neurons_(nb_neurons);												// containing each the place (int) of a random neuron it is connected to
																							// neurons_ : This vector contains the complete list of Neurons



//----------------------------------------------------------------------

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
		std::cout << "Please inserteth the stopping step (>beginning step & <=2000) :" << std::endl;	
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

/* I found thoses methods in the internet, they made it possible to check 
 * if the input corresponds to what we are expecting without having to create
 * another variable only for control purpose
 * */

//----------------------------------------------------------------------	
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> random_targets(0, nb_neurons-1);
	
	
	for (size_t i(0); i < nb_neurons; ++i) {
		for(size_t j(0); j < conn_tot; ++j) {
			neurons_targets[i][j] = random_targets(gen);
		}
	}
	
/* This code enables us to iniate the matrix with a random number in each 
 * cases, so each neurons i will be connected to randomly chosen neurons
 * */
 
	int lambda(2);
	std::random_device rd_;
	std::mt19937 generate(rd_());
	std::poisson_distribution<> poisson_distribution(lambda);
 
//----------------------------------------------------------------------

	
	std::ofstream Neurons_mem_pot;
	Neurons_mem_pot.open("potentials.txt");
	
	bool is_Inhib(false);
	Iext2 = Iext;
	
	while (nb_step < stop_time) 
	{
		/*if (nb_step < start_step or nb_step > stop_step) 
		{
			Iext2 = 0.0;
		} 
		else 
		{ 
			Iext2 = Iext; 
		}*/
		
		for (size_t i(0); i < neurons_.size(); ++i) {								
			
			if (neurons_[i].Has_now_spiked(/*h*/) and i < (neurons_.size() - 1)) 
			{
				for (size_t j(0); j < conn_tot; ++j) {
										
					if (i < nb_exhit) {
						is_Inhib = false;
					} else {
						is_Inhib = true;
					}
					
					neurons_[i].Send_spike(neurons_[neurons_targets[i][j]], nb_step, is_Inhib);
				}
			}
			if (nb_step < start_step or nb_step > stop_step) {
				neurons_[i].Update_state(Iext2, 0);
			} else {
				neurons_[i].Update_state(Iext2, poisson_distribution(generate));
			}
			Neurons_mem_pot << neurons_[i].Get_membrane_potential() << '\t';
			//std::cout << "at step " << nb_step << " : " << neurons_[i].Get_membrane_potential() << " mV" << '\t';
			};
		//std::cout << std::endl;
		Neurons_mem_pot << std::endl;
		//std::cout << std::endl;
		++nb_step;
	};

	Neurons_mem_pot.close();
	
/* 1st step : the current input is only active inside the chosen interval of time.
 * 				outside, the current input is 0.
 * 
 * 2nd step : we check if the neuron i has spiked, if yes : send spike to every 
 * 													neurons it is connected to.
 * 
 * 3rd step : we update the neuron and write its potential in the .txt file
 * 
 * */
	
	return 0;
}
