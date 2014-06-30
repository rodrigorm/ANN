<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Activation;
use \Ann\Visitor;

class Peripheral implements Branch
{
    public function output(Activation $activation)
    {
        return $activation->activate($this);
    }

    public function activate(Activation $activation)
    {
        return $activation->input($this);
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitPeripheral($this);
    }
}
