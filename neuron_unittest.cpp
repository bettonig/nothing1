#include <iostream>
#include "neuron.h"
#include "gtest/gtest.h"


	static constexpr double tau_ = 20;
	static constexpr double threshold_ = 20;
	static constexpr double c_ = 1.0;
	static constexpr double J_ = 0.1; //0.1
	static constexpr int refractory_time_ = 20;
	static constexpr int delay = 15;	
	
	double Exp_ = exp(-(0.1/tau_));
	static constexpr double c2 = tau_/c_;




TEST (NeuronTest, MembranePotential) {
	Neuron neuron;
	
	neuron.Update_state(1.0, 0);
	EXPECT_EQ(1.0 * c2 * (1 - Exp_), neuron.Get_membrane_potential());
}


TEST (NeuronTest, ) {
	Neuron neuron1;
	Neuron neuron2;
	
	neuron1.Send_spike(neuron2, 10, false);
	EXPECT_EQ(neuron2.Get_buffer(9), 1);
	
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
