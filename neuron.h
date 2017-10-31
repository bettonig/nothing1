#include <iostream>
#include <vector>
#include <cmath>
//using namespace std;

#ifndef NEURON_H
#define NEURON_H

//typedef std::vector<int> time_vector;
typedef std::vector<int> int_vector;


class Neuron {
	
	private:
		
		double membrane_potential_;
		unsigned int nb_spks_;											//spks is short for "spikes" of a neuron
		int_vector time_spks_;											//time_spks_ : Its actually a vector of the steps at which the spikes occured
		
		int steps_intern_;
		int_vector delay_buffer;
		
		
		static constexpr double tau_ = 20;
		static constexpr double threshold_ = 20;
		static constexpr double c_ = 1.0;
		static constexpr double J_ = 0.1; //0.1
		static constexpr int refractory_time_ = 20;
		static constexpr int delay = 15;	
		
		double Exp_ = exp(-(0.1/tau_));
		static constexpr double c2 = tau_/c_;
		
	public:
		
	//Constructor & Destructor :
		Neuron ();
		Neuron (double membrane_potential, unsigned int nb_spks);
		/*Neuron (const Neuron& another);*/
		~Neuron ();

//----------------------------------------------------------------------
		
	//Getters :
		double Get_membrane_potential () const;
		unsigned int Get_nb_spks () const;
		int_vector Get_time_spks () const;
		int Get_buffer(size_t place) const;
		
//----------------------------------------------------------------------		
		
	//Setters :
		void Set_membrane_potential (double membrane_potential);
		void Set_nb_spks (unsigned int nb_spks);
		void Set_time_spks (int_vector time_spks);
		
//----------------------------------------------------------------------
		
	//Methods :
		bool Is_refractory (/*double dT*/);
		bool Has_now_spiked (/*double dT*/);
		
		void Update_state (double Iext2, int poisson);					// dT = time interval (0.1)
		void Send_spike(Neuron& neuron, int step, bool Is_inhib);
		void Store_spike(int step, bool is_Inhib);
		
};

#endif
