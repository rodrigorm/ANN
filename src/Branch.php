<?php

namespace Ann;

use \Ann\Activation;
use \Ann\Visitee;

interface Branch extends Visitee
{
    public function output(Activation $activation);
}
