<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Input;
use \Ann\BackPropagation\Node;
use \Ann\Tree;

class BackPropagation
{
    private $tree;
    private $input;
    private $target;
    private $factor;

    public function __construct(Tree $tree, Input $input, $target, $factor)
    {
        $this->tree = $tree;
        $this->input = $input;
        $this->target = $target;
        $this->factor = $factor;
    }

    public function teach(Neuron $neuron)
    {
        return $neuron->learn($this->input, $this);
    }

    public function delta(Synapse $synapse)
    {
        return $this->factor * $this->tree->delta($synapse, $this->input, $this->target);
    }
}
