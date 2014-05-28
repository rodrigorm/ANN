<?php

namespace Ann\OutputFunction;

use \Ann\OutputFunction;

class Sigmoid implements OutputFunction
{
    public function forward($value)
    {
        return 1 / (1 + pow(M_EULER, -$value));
    }
}

