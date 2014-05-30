<?php

namespace Ann;

use \Ann\Branch;
use \Ann\OutputFunction;
use \Ann\Input;

class Neuron
{
    private $branch;
    private $outputFunction;

    public function __construct(Branch $branch, OutputFunction $outputFunction)
    {
        $this->branch = $branch;
        $this->outputFunction = $outputFunction;
    }

    public function branch()
    {
        return $this->branch;
    }

    public function outputFunction()
    {
        return $this->outputFunction;
    }

    public function output(Input $input)
    {
        return $this->outputFunction->forward($this->branch->output($input));
    }

    public function derivative(Input $input)
    {
        return $this->outputFunction->derivative($this->branch->output($input));
    }

    public function learn(Input $input, BackPropagation $teacher)
    {
        $branch = $this->branch->learn($input, $teacher);

        if ($branch !== $this->branch) {
            return new self($branch, $this->outputFunction);
        }

        return $this;
    }
}
