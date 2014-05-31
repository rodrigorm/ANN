<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Input;
use \Ann\Visitor;

class Bias implements Branch
{
    public function output(Input $input)
    {
        return 1.0;
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitBias($this);
    }
}

