<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Input;
use \Ann\BackPropagation\Node;
use \Ann\Tree;

class BackPropagation
{
    private $tree;

    public function __construct(Tree $tree)
    {
        $this->tree = $tree;
    }

    public function teach(Neuron $neuron, Input $input, $target)
    {
        return $neuron->learn($input, $target, $this->tree);
    }
}
