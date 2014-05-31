<?php

namespace Ann;

use \Ann\Branch;
use \Ann\OutputFunction;
use \Ann\Input;
use \Ann\Visitor;
use \Ann\Visitee;

class Neuron implements Visitee
{
    private $branch;
    private $outputFunction;

    public function __construct(Branch $branch, OutputFunction $outputFunction)
    {
        $this->branch = $branch;
        $this->outputFunction = $outputFunction;
    }

    public function output(Input $input)
    {
        return $this->outputFunction->forward($this->branch->output($input));
    }

    public function derivative(Input $input)
    {
        return $this->outputFunction->derivative($this->branch->output($input));
    }

    public function accept(Visitor $visitor)
    {
        return $visitor->visitNeuron($this, $this->branch, $this->outputFunction);
    }
}
