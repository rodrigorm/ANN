<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Input;
use \Ann\State;

class Peripheral implements Branch
{
    private $state;

    public function __construct(State $state)
    {
        $this->state = $state;
    }

    public function output(Input $input)
    {
        return $input->get($this->state);
    }

    public function learn($error, Input $input)
    {
        return $this;
    }
}

