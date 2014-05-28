<?php

namespace Ann;

use \Ann\NerveCell;
use \Ann\Branch;
use \Ann\OutputFunction;
use \Ann\Input;

class Neuron implements NerveCell
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

    public function learn($error, Input $input)
    {
        return new self(
            $this->branch->learn($error, $input),
            $this->outputFunction
        );
    }
}
