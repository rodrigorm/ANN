<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Input;

class Synapse
{
    private $neuron;
    private $weight = 0;

    public function __construct(Neuron $neuron, $weight)
    {
        $this->neuron = $neuron;
        $this->weight = $weight;
    }

    public function output(Input $input)
    {
        return $this->neuron->output($input) * $this->weight;
    }

    public function learn($error, Input $input)
    {
        $weightChange = 0.1 * $error * $this->neuron->output($input);
        $weight = $this->weight + $weightChange;
        $expected = $this->neuron->output($input) * $weight;

        return new self(
            $this->neuron->learn($expected - $this->output($input), $input),
            $weight
        );
    }
}
