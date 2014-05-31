<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Synapse;
use \Ann\Input;
use \Ann\Visitor;

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

    public function accept(Visitor $visitor)
    {
        return $visitor->visitDendrite($this, $this->synapses);
    }
}
