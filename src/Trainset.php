<?php

namespace Ann;

use \Ann\Activation;
use \Ann\Output;
use \Ann\Neuron;

class Trainset
{
    private $activation;
    private $target;

    public function __construct(Activation $activation, Output $target)
    {
        $this->activation = $activation;
        $this->target = $target;
    }

    public function derivative(Neuron $neuron)
    {
        return $neuron->derivative($this->activation);
    }

    public function output(Neuron $neuron)
    {
        return $this->activation->output($neuron);
    }

    public function target(Neuron $neuron)
    {
        return $this->target->get($neuron);
    }
}
