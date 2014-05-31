<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Input;
use \Ann\Visitee;
use \Ann\Visitor;

class Synapse implements Visitee
{
    private $neuron;
    private $weight = 0;

    public function __construct(Neuron $neuron, $weight)
    {
        $this->neuron = $neuron;
        $this->weight = $weight;
    }

    public function neuron()
    {
        return $this->neuron;
    }

    public function weight()
    {
        return $this->weight;
    }

    public function output(Input $input)
    {
        return $this->neuron->output($input) * $this->weight;
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitSynapse($this, $this->neuron, $this->weight);
    }
}
