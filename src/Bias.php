<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Input;

class Bias implements Branch
{
    public function synapses()
    {
        return array();
    }

    public function output(Input $input)
    {
        return 1.0;
    }

    public function learn(Input $input, BackPropagation $teacher)
    {
        return $this;
    }
}

