#include "neuron.h"


//Constructor & Destructor::

Neuron::Neuron ()
:membrane_potential_(0.0), nb_spks_(0), time_spks_()
{
	time_spks_.push_back(0);
	for (size_t i(0); i <= delay + 1; ++i) 
	{
		delay_buffer.push_back(0);
	}
}


Neuron::Neuron (double membrane_potential, unsigned int nb_spks)
:membrane_potential_(membrane_potential), nb_spks_(nb_spks), time_spks_()
{
	time_spks_.push_back(0);
	for (size_t i(0); i <= delay + 1; ++i)
	{
		delay_buffer.push_back(0);
	}
}

/*Neuron::Neuron (const Neuron& another)
:
{}*/


Neuron::~Neuron ()
{/*std::cout << "NEURON TERMINATED" << std::endl;*/}



//----------------------------------------------------------------------



// Getters::

double Neuron::Get_membrane_potential () const
{return membrane_potential_;}

unsigned int Neuron::Get_nb_spks () const
{return nb_spks_;}

int_vector Neuron::Get_time_spks () const
{return time_spks_;}

int Neuron::Get_buffer(size_t place) const
{return delay_buffer[place];}



//----------------------------------------------------------------------




//Setters::

void Neuron::Set_membrane_potential (double membrane_potential)
{membrane_potential_ = membrane_potential;}

void Neuron::Set_nb_spks (unsigned int nb_spks)
{nb_spks_ = nb_spks;}

void Neuron::Set_time_spks (int_vector time_spks)
{time_spks_ = time_spks;}



//----------------------------------------------------------------------




///Methods::

bool Neuron::Is_refractory(/*double dT*/)
{
	if (steps_intern_ >= refractory_time_ and steps_intern_ - time_spks_.back() < refractory_time_)
	{
		return true;
	}
	return false;
}
///Is_Refractory : return true if the neuron has just spiked (steps < 20)


bool Neuron::Has_now_spiked (/*double dT*/)
{
	if (time_spks_.size() < 2)
	{
		return false;
	} 
	else 
	{
		if (steps_intern_ == time_spks_.back())
		{
			//std::cout << "WOLOLO" << std::endl;
			return true;
		} else {
			return false;
		};
	};
}
///Has_now_Spiked : return true only if a spike just occured 


void Neuron::Update_state(double Iext2, int poisson)
{
	if (Is_refractory(/*dT*/))
	{
		membrane_potential_ = 0.0;
	} else {
		membrane_potential_ = Exp_ * membrane_potential_ + Iext2 * c2 * (1 - Exp_) + ((delay_buffer[(steps_intern_ + delay) % (delay + 1)] + poisson) * J_) ;
		delay_buffer[(steps_intern_ + delay) % (delay + 1)] = 0;
		if (membrane_potential_ >= threshold_)
		{
			time_spks_.push_back(steps_intern_ + 1);
			nb_spks_ = nb_spks_ + 1;								
		};
	};
	steps_intern_ += 1;
}
/**Update_state : 	if the neuron is refractory, its membrane is zero.
 * 					otherwise, its new membrane potential will be calculated & its buffer at delay + step is set to 0
 * */


void Neuron::Send_spike(Neuron& neuron, int step, bool is_Inhib)
{
	neuron.Store_spike(step, is_Inhib);
	//std::cout<<"spike send"<<std::endl;
}
/** n1.Send_spike(n2, step, T/F) : n1 will call Store_spike of n2 and give as 
 *  arguments the time (step) n1 has spiked and wether it is excitatory or inhibitory
 * */


void Neuron::Store_spike(int step, bool is_Inhib)
{
	int modulo = (step + delay) % (delay + 1);
	if (is_Inhib) {
		delay_buffer[modulo] -= 5;
		//std::cout<<"  inhib"<<std::endl;
	} else {
		delay_buffer[modulo] += 1;
		//std::cout<<"excit"<<std::endl;
	};
}
/** n2.Store_spike(step, T/F) : n2 will insert in its buffer that 
 *  delay-steps later, it will receive the information sent by n1
 * */

