<?php

namespace Ann;

use \Ann\NerveCell;
use \Ann\Input;

class Synapse
{
    private $cell;
    private $weight = 0;

    public function __construct(NerveCell $cell, $weight)
    {
        $this->cell = $cell;
        $this->weight = $weight;
    }

    public function output(Input $input)
    {
        return $this->cell->output($input) * $this->weight;
    }

    public function learn($error, Input $input)
    {
        $weightChange = 0.1 * $error * $this->cell->output($input);
        $weight = $this->weight + $weightChange;
        $expected = $this->cell->output($input) * $weight;

        return new self(
            $this->cell->learn($expected - $this->output($input), $input),
            $weight
        );
    }
}
