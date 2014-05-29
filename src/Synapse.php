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

    public function learn(Input $input, $target, $tree)
    {
        $neuron = $this->neuron->learn($input, $target, $tree);

        $factor = 0.2;
        $delta = $tree->delta($this, $input, $target);
        $weightChange = $factor * $delta * $this->neuron->output($input);

        $weight = $this->weight + $weightChange;

        if ($neuron !== $this->neuron || $weight !== $this->weight) {
            return new self($neuron, $weight);
        }

        return $this;
    }
}
