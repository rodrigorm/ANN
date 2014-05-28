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

    public function output(Input $input)
    {
        $result = 0;

        foreach ($this->synapses as $synapse) {
            $result += $synapse->output($input);
        }

        return $result;
    }

    public function learn($error, Input $input)
    {
        $synapses = array();

        foreach ($this->synapses as $synapse) {
            $synapses[] = $synapse->learn($error, $input);
        }

        return new self($synapses);
    }
}
