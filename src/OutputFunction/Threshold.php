<?php

namespace Ann\OutputFunction;

use \Ann\OutputFunction;

class Threshold implements OutputFunction
{
    private $threshold;

    public function __construct($threshold)
    {
        $this->threshold = $threshold;
    }

    public function forward($value)
    {
        return ($value >= $this->threshold) ? $value : 0;
    }
}
