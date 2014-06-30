<?php

namespace Ann;

use \Ann\Visitor;
use \Ann\Network;
use \Ann\Neuron;
use \Ann\Branch;
use \Ann\OutputFunction;
use \Ann\Peripheral;
use \Ann\Bias;
use \Ann\Dendrite;
use \Ann\Synapse;
use \Ann\Delta;
use \SplObjectStorage;

class DeltaBuilder implements Visitor
{
    private $neurons = array();
    private $synapses = array();
    private $connections = array();
    private $stack = array();

    public function __construct(array $neurons = array(), array $synapses = array(), array $connections = array(), array $stack = array())
    {
        $this->neurons = $neurons;
        $this->synapses = $synapses;
        $this->connections = $connections;
        $this->stack = $stack;
    }

    public function build(Trainset $trainset)
    {
        $delta = new Delta();

        foreach ($this->synapses as $i => $synapses) {
            foreach ($synapses as $synapse) {
                $delta = $delta->set($synapse, $this->delta($synapse, $trainset));
            }
        }

        return $delta;
    }

    public function visitNetwork(Network $network, array $inputs, array $outputs)
    {
        $visitor = $this;

        foreach ($outputs as $neuron) {
            $visitor = $neuron->accept($this);
        }

        return $visitor;
    }

    public function visitNeuron(Neuron $neuron, Branch $branch, OutputFunction $function)
    {
        return $branch->accept($this->push($neuron))->pop();
    }

    public function visitDendrite(Dendrite $dendrite, array $synapses)
    {
        $visitor = $this;

        foreach ($synapses as $synapse) {
            $visitor = $synapse->accept($visitor);
        }

        return $visitor;
    }

    public function visitSynapse(Synapse $synapse, Neuron $neuron, $weight)
    {
        return $neuron->accept($this->connect($neuron, $synapse));
    }

    public function visitPeripheral(Peripheral $peripheral)
    {
        return $this;
    }

    public function visitBias(Bias $bias)
    {
        return $this;
    }

    private function push(Neuron $neuron)
    {
        $stack = $this->stack;
        $stack[] = $neuron;
        return new self($this->neurons, $this->synapses, $this->connections, $stack);
    }

    private function pop()
    {
        $stack = $this->stack;
        array_pop($stack);
        return new self($this->neurons, $this->synapses, $this->connections, $stack);
    }

    private function connect(Neuron $neuron, Synapse $synapse)
    {
        $neurons = $this->neurons;
        $synapses = $this->synapses;
        $connections = $this->connections;

        $i = array_search($neuron, $neurons, true);

        if ($i === false) {
            $i = count($neurons);
            $neurons[$i] = $neuron;
            $synapses[$i] = array();
            $connections[$i] = array();
        }

        $j = array_search($synapse, $synapses[$i], true);

        if ($j === false) {
            $j = count($synapses[$i]);
            $synapses[$i][$j] = $synapse;
        }

        $connections[$i][$j] = end($this->stack);

        return new self($neurons, $synapses, $connections, $this->stack);
    }

    private function delta(Synapse $synapse, Trainset $trainset)
    {
        $i = array_search($synapse->neuron(), $this->neurons, true);
        $j = array_search($synapse, $this->synapses[$i], true);

        $neuron = $this->connections[$i][$j];
        return $trainset->derivative($neuron) * $this->error($neuron, $trainset);
    }

    private function error(Neuron $neuron, Trainset $trainset)
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
