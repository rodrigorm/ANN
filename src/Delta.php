<?php

namespace Ann;

use \Ann\Synapse;
use \SplObjectStorage;

class Delta
{
    private $synapses;

    public function __construct(SplObjectStorage $synapses = null)
    {
        $this->synapses = $synapses ? $synapses : new SplObjectStorage();
    }

    public function set(Synapse $synapse, $delta)
    {
        $synapses = clone $this->synapses;

        if ($synapses->contains($synapse)) {
            return $this;
        }

        $synapses->attach($synapse, $delta);

        return new self($synapses);
    }

    public function delta(Synapse $synapse)
    {
        return $this->synapses[$synapse];
    }
}
