<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Synapse;
use \Ann\Input;

class Dendrite implements Branch
{
    private $synapses;

    public function __construct(array $synapses)
    {
        $this->synapses = $synapses;
    }

    public function synapses()
    {
        return $this->synapses;
    }

    public function output(Input $input)
    {
        $result = 0;

        foreach ($this->synapses as $synapse) {
            $result += $synapse->output($input);
        }

        return $result;
    }

    public function learn(Input $input, BackPropagation $teacher)
    {
        $synapses = array();

        foreach ($this->synapses as $synapse) {
            $synapses[] = $synapse->learn($input, $teacher);
        }

        foreach ($this->synapses as $index => $synapse) {
            if ($synapses[$index] !== $synapse) {
                return new self($synapses);
            }
        }

        return $this;
    }
}
