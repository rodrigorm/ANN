<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Trainset;
use \Ann\Delta;
use \Ann\Visitor;
use \SplObjectStorage;

class BackPropagation implements Visitor
{
    private $delta;
    private $trainset;
    private $factor;
    private $objects;

    public function __construct(Delta $delta, Trainset $trainset, $factor, SplObjectStorage $objects = null)
    {
        $this->delta = $delta;
        $this->trainset = $trainset;
        $this->factor = $factor;
        $this->objects = $objects ? $objects : new SplObjectStorage();
    }

    public function teach(Network $network)
    {
        return $network->accept($this)->get($network);
    }

    public function visitNetwork(Network $network, array $inputs, array $outputs)
    {
        $visitor = $this;

        foreach ($outputs as $neuron) {
            $visitor = $neuron->accept($this);
        }

        return $visitor->set($network, new Network($inputs, $visitor->getAll($outputs)));
    }

    public function visitNeuron(Neuron $neuron, Branch $branch, OutputFunction $function)
    {
        $visitor = $branch->accept($this);
        return $visitor->set($neuron, new Neuron($visitor->get($branch), $function));
    }

    public function visitPeripheral(Peripheral $peripheral)
    {
        return $this;
    }

    public function visitBias(Bias $bias)
    {
        return $this;
    }

    public function visitDendrite(Dendrite $dendrite, array $synapses)
    {
        $visitor = $this;

        foreach ($synapses as $synapse) {
            $visitor = $synapse->accept($visitor);
        }

        return $visitor->set($dendrite, new Dendrite($visitor->getAll($synapses)));
    }

    public function visitSynapse(Synapse $synapse, Neuron $neuron, $weight)
    {
        $visitor = $neuron->accept($this);

        $delta = $this->factor * $this->delta->delta($synapse);
        $weightChange = $delta * $visitor->trainset->output($neuron);

        $weight = $weight + $weightChange;

        return $visitor->set($synapse, new Synapse($visitor->get($neuron), $weight));
    }

    private function set($key, $value)
    {
        if ($this->objects->contains($key)) {
            return $this;
        }

        $objects = clone $this->objects;
        $objects->attach($key, $value);

        return new self($this->delta, $this->trainset, $this->factor, $objects);
    }

    private function get($key)
    {
        if ($this->objects->contains($key)) {
            return $this->objects[$key];
        }

        return $key;
    }

    private function getAll($keys)
    {
        $result = array();

        foreach ($keys as $key) {
            $result[] = $this->get($key);
        }

        return $result;
    }
}
