<?php

namespace Ann;

use \Ann\Visitee;

interface Branch extends Visitee
{
    public function output(Activation $activation);
}
