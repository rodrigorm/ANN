<?php

namespace Ann;

use \Ann\Input;

interface Branch
{
    public function output(Input $input);
    public function learn($error, Input $input);
}
