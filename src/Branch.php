<?php

namespace Ann;

use \Ann\Input;

interface Branch
{
    public function synapses();
    public function output(Input $input);
    public function learn(Input $input, $target, $tree);
}
