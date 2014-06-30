<?php

namespace Ann\OutputFunction;

use \Ann\OutputFunction;

class Sigmoid implements OutputFunction
{
    public function forward($value)
    {
        return 1.0 / (1.0 + exp(-$value));
    }

    public function derivative($value)
    {
        return $this->forward($value) * (1.0 - $this->forward($value));
    }
}
