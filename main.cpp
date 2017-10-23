#include "neuron.h"
#include <iostream>
#include <climits>
#include <fstream>
#include <string>
//#include <iomanip>
//using namespace std;

//void write_membrane_pot (string file_out_, double membrane_pot);

int main()
{

	/*const*/int stop_time(200);
	int start_step(0);
	int stop_step(0);
	int nb_step(0);
	const double h(0.1); //ms											// interval
	
	double Iext(0.0);		//pA
	double Iext2(0.0);		//pA										// Current 

	
	while (start_step <= 0 or start_step >= stop_time) {											// This loop is to make sure the person using this program
		std::cout << "Please inserteth the beginnig step (>0 & <200) :" << std::endl;				// enters a number above 0.
		std::cin >> start_step;
		if (std::cin.fail() or start_step >= stop_time) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
	
	
	while (stop_step <= 0 or stop_step < start_step or stop_step > stop_time) {											// This loop is to make sure the person using this program
		std::cout << "Please inserteth the stopping step (>beginning step & <=200) :" << std::endl;				// enters a number above 0.
		std::cin >> stop_step;
		if (std::cin.fail() or stop_step < start_step or stop_step > stop_time) {
			std::cout << "I'm afraid i can't do that Dave!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
		
		
	while (Iext <= 0.0) {
		std::cout << "Please inserteth the current :" << std::endl;
		std::cin >> Iext;
		if (std::cin.fail()) {
			std::cout << "I'm afraid i can't do that Dave!2" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		};
	};
	
	
	//int spiked_conn(0);
	
	std::vector<Neuron> neurons_;
	Neuron unique;
	neurons_.push_back(unique);
	Neuron second(7.0, 0);
	neurons_.push_back(second);
	
	std::ofstream Neurons_mem_pot;
	Neurons_mem_pot.open("potentials.txt");
	
	while (nb_step < stop_time) 
	{
		if (nb_step < start_step or nb_step > stop_step) 
		{
			Iext2 = 0.0;
		} 
		else 
		{ 
			Iext2 = Iext; 
		}
		
		for (size_t i(0); i < neurons_.size(); ++i) {								/* At first i used a for(auto x : y) loop but it reseted   
																					 * The membrane_potential to 0 for unknown reasons */
			if (neurons_[i].Has_now_spiked(h) and i != (neurons_.size() - 1)) 
			{ 
				neurons_[i].Send_spike(neurons_[i+1], nb_step);
				/*spiked_conn = 1;*/ 
			}
			neurons_[i].Update_state(h, Iext2);
			Neurons_mem_pot << neurons_[i].Get_membrane_potential() << '\t' << '\t';
			std::cout << "at step " << nb_step << " : " << neurons_[i].Get_membrane_potential() << " mV" << '\t';
			};
		std::cout << std::endl;
		//spiked_conn = 0;
		Neurons_mem_pot << std::endl;
		std::cout << std::endl;
		++nb_step;
	};

	Neurons_mem_pot.close();
	
	
	return 0;
}






/*
void write_membrane_pot (string file_out_, double membrane_pot)
{
	ofstream output(file_out_.c_str);
	
	output << membrane_pot << " , ";
	
	output.close();
}
*/
