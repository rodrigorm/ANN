<?php

namespace Ann;

use \Ann\Network;
use \Ann\Neuron;
use \Ann\Branch;
use \Ann\OutputFunction;
use \Ann\Peripheral;
use \Ann\Bias;
use \Ann\Dendrite;
use \Ann\Synapse;

interface Visitor
{
    public function visitNetwork(Network $network, array $inputs, array $outputs);
    public function visitNeuron(Neuron $neuron, Branch $branch, OutputFunction $function);
    public function visitPeripheral(Peripheral $peripheral);
    public function visitBias(Bias $bias);
    public function visitDendrite(Dendrite $dendrite, array $synapses);
    public function visitSynapse(Synapse $synapse, Neuron $neuron, $weight);
}
