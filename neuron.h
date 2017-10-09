#include <iostream>
#include <vector>
//using namespace std;

#ifndef NEURON_H
#define NEURON_H

typedef std::vector<double> time_vector;


class Neuron {
	
	private:
		
		double membrane_potential_;
		unsigned int nb_spks_;											//spks is short for "spikes" of a neuron
		time_vector time_spks_;											// !!!ask

		static const double tau_ = 20;
		static const double threshold_ = 20;
		static const double c_ = 1;
		static const double refractory_time_ = 2;
		
		
	public:
		
		//Constructor & Destructor
		Neuron ();
		Neuron (double membrane_potential, unsigned int nb_spks, time_vector time_spks);
		/*Neuron (const Neuron& another);*/
		~Neuron ();
		
		//Getters
		double Get_membrane_potential () const;
		unsigned int Get_nb_spks () const;
		time_vector Get_time_spks () const;
		
		//Setters
		void Set_membrane_potential (double membrane_potential);
		void Set_nb_spks (unsigned int nb_spks);
		void Set_time_spks (time_vector time_spks);
		
		//Methods
		bool Is_refractory (double time1);
		void Update_state (double time1, double dT, double Iex);								// dT = n * h
		
};

#endif
