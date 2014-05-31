<?php

namespace Ann;

use \Ann\Input;
use \Ann\Output;
use \Ann\Neuron;

class Trainset
{
    private $input;
    private $output;

    public function __construct(Input $input, Output $output)
    {
        $this->input = $input;
        $this->output = $output;
    }

    public function derivative(Neuron $neuron)
    {
        return $neuron->derivative($this->input);
    }

    public function output(Neuron $neuron)
    {
        return $neuron->output($this->input);
    }

    public function target(Neuron $neuron)
    {
        return $this->output->get($neuron);
    }
}
