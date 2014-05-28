<?php

namespace Ann;

use \Ann\State;

class Input
{
    private $states = array();
    private $values = array();

    public function __construct(array $states = array(), array $values = array())
    {
        $this->states = $states;
        $this->values = $values;
    }

    public function set(State $state, $value)
    {
        $states = $this->states;
        $values = $this->values;

        $index = array_search($state, $this->states, true);

        if ($index === false) {
            $index = count($states);
        }

        $states[$index] = $state;
        $values[$index] = $value;

        return new self(
            $states,
            $values
        );
    }

    public function get(State $state)
    {
        $index = array_search($state, $this->states, true);

        if ($index === false) {
            throw new \InvalidArgumentException(sprintf('State %s not found', $state));
        }

        return $this->values[$index];
    }
}
