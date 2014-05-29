<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Input;
use \Ann\Tree;
use \Ann\BackPropagation;

class Trainer
{
    public function train(Neuron $neuron, Input $input, $target, $factor = 0.2)
    {
        $tree = $this->reverse($neuron, new Tree());
        $teacher = new BackPropagation($tree, $input, $target, $factor);
        return $teacher->teach($neuron);
    }

    private function reverse(Neuron $neuron, Tree $tree)
    {
        foreach ($neuron->branch()->synapses() as $synapse) {
            $tree = $tree->connect($synapse, $neuron);
            $tree = $this->reverse($synapse->neuron(), $tree);
        }

        return $tree;
    }
}
