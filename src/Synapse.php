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

    public function learn(Input $input, BackPropagation $teacher)
    {
        $neuron = $this->neuron->learn($input, $teacher);

        $delta = $teacher->delta($this);
        $weightChange = $delta * $this->neuron->output($input);

        $weight = $this->weight + $weightChange;

        if ($neuron !== $this->neuron || $weight !== $this->weight) {
            return new self($neuron, $weight);
        }

        return $this;
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitSynapse($this, $this->neuron, $this->weight);
    }
}
