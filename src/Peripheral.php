<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Input;
use \Ann\Visitor;

class Peripheral implements Branch
{
    public function output(Input $input)
    {
        return $input->get($this);
    }

    public function learn(Input $input, BackPropagation $teacher)
    {
        return $this;
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitPeripheral($this);
    }
}

