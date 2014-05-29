<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Input;

class Peripheral implements Branch
{
    public function synapses()
    {
        return array();
    }

    public function output(Input $input)
    {
        return $input->get($this);
    }

    public function learn(Input $input, BackPropagation $teacher)
    {
        return $this;
    }
}

