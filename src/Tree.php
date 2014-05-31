<?php

namespace Ann;

use \Ann\Trainset;

class Tree
{
    private $neurons = array();
    private $synapses = array();
    private $connections = array();

    public function __construct(array $neurons = array(), array $synapses = array(), array $connections = array())
    {
        $this->neurons = $neurons;
        $this->synapses = $synapses;
        $this->connections = $connections;
    }

    public function connect(Synapse $synapse, Neuron $neuron)
    {
        $neurons = $this->neurons;
        $synapses = $this->synapses;
        $connections = $this->connections;

        $i = array_search($synapse->neuron(), $neurons, true);

        if ($i === false) {
            $i = count($neurons);
            $neurons[$i] = $synapse->neuron();
            $synapses[$i] = array();
            $connections[$i] = array();
        }

        $j = array_search($synapse, $synapses[$i], true);

        if ($j === false) {
            $j = count($synapses[$i]);
            $synapses[$i][$j] = $synapse;
        }

        $connections[$i][$j] = $neuron;

        return new self($neurons, $synapses, $connections);
    }

    public function delta(Synapse $synapse, Trainset $trainset)
    {
        $i = array_search($synapse->neuron(), $this->neurons, true);
        $j = array_search($synapse, $this->synapses[$i], true);

        $neuron = $this->connections[$i][$j];
        return $trainset->derivative($neuron) * $this->error($neuron, $trainset);
    }

    public function error(Neuron $neuron, Trainset $trainset)
    {
        $i = array_search($neuron, $this->neurons, true);

        if ($i === false) {
            return $trainset->target($neuron) - $trainset->output($neuron);
        }

        $downstream = 0;

        foreach ($this->synapses[$i] as $j => $synapse) {
            $downstream += $synapse->weight() * $this->error($this->connections[$i][$j], $trainset);
        }

        return $downstream;
    }
}
