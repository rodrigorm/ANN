<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Input;
use \Ann\Tree;
use \Ann\BackPropagation;
use \Ann\TreeBuilder;

class Trainer
{
    public function train(Neuron $neuron, Input $input, $target, $factor = 0.2)
    {
        $tree = $this->buildTree($neuron, new Tree());
        $teacher = new BackPropagation($tree, $input, $target, $factor);
        return $teacher->teach($neuron);
    }

    private function buildTree(Neuron $neuron, Tree $tree)
    {
        $builder = new TreeBuilder($tree);
        return $neuron->accept($builder)->build();
    }
}
