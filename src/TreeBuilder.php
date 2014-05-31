<?php

namespace Ann;

use \Ann\Visitor;
use \Ann\Tree;
use \Ann\Neuron;
use \Ann\Branch;
use \Ann\OutputFunction;
use \Ann\Peripheral;
use \Ann\Bias;
use \Ann\Dendrite;
use \Ann\Synapse;

class TreeBuilder implements Visitor
{
    private $tree;
    private $neuron;

    public function __construct(Tree $tree = null, Neuron $neuron = null)
    {
        $this->tree = $tree;
        $this->neuron = $neuron;
    }

    public function build()
    {
        return $this->tree;
    }

    public function visitNeuron(Neuron $neuron, Branch $branch, OutputFunction $function)
    {
        $visitor = new self($this->tree, $neuron);
        return $branch->accept($visitor);
    }

    public function visitDendrite(Dendrite $dendrite, array $synapses)
    {
        $tree = $this->tree;

        foreach ($synapses as $synapse) {
            $tree = $tree->connect($synapse, $this->neuron);
        }

        $visitor = new self($tree);

        foreach ($synapses as $synapse) {
            $visitor = $synapse->accept($visitor);
        }

        return $visitor;
    }

    public function visitSynapse(Synapse $synapse, Neuron $neuron, $weight)
    {
        return $neuron->accept($this);
    }

    public function visitPeripheral(Peripheral $peripheral)
    {
        return $this;
    }

    public function visitBias(Bias $bias)
    {
        return $this;
    }
}
