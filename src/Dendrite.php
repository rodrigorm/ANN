<?php

namespace Ann;

use \Ann\Branch;
use \Ann\Synapse;
use \Ann\Activation;
use \Ann\Visitor;

class Dendrite implements Branch
{
    private $synapses;

    public function __construct(array $synapses)
    {
        $this->synapses = $synapses;
    }

    public function output(Activation $activation)
    {
        foreach ($this->synapses as $synapse) {
            $activation = $synapse->output($activation);
        }

        return $activation->activate($this);
    }

    public function activate(Activation $activation)
    {
        $result = 0;

        foreach ($this->synapses as $synapse) {
            $result += $activation->output($synapse);
        }

        return $result;
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitDendrite($this, $this->synapses);
    }
}
