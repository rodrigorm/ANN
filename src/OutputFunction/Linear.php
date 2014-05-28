<?php

namespace Ann\OutputFunction;

use \Ann\OutputFunction;

class Linear implements OutputFunction
{
    public function forward($value)
    {
        return $value;
    }
}
