<?php

namespace Ann;

use \Ann\Input;
use \Ann\BackPropagation;
use \Ann\Visitee;

interface Branch extends Visitee
{
    public function output(Input $input);
    public function learn(Input $input, BackPropagation $teacher);
}
