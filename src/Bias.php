<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Activation;
use \Ann\Visitor;

class Bias implements Branch
{
    public function output(Activation $activation)
    {
        return $activation->activate($this);
    }

    public function activate(Activation $Activation)
    {
        return 1.0;
    }

    public function accept(/*Visitor*/ $visitor)
    {
        return $visitor->visitBias($this);
    }
}
