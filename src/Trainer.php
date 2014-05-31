<?php

namespace Ann;

use \Ann\Network;
use \Ann\Neuron;
use \Ann\Input;
use \Ann\Tree;
use \Ann\BackPropagation;
use \Ann\TreeBuilder;
use \Ann\Trainset;

class Trainer
{
    public function train(Network $network, Trainset $trainset, $factor)
    {
        $tree = $this->buildTree($network, new Tree());
        $teacher = new BackPropagation($tree, $trainset, $factor);
        return $teacher->teach($network);
    }

    private function buildTree(Network $network, Tree $tree)
    {
        $builder = new TreeBuilder($tree);
        return $network->accept($builder)->build();
    }
}
