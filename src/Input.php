<?php

namespace Ann;

use \Ann\Peripheral;

class Input
{
    private $keys = array();
    private $values = array();

    public function __construct(array $keys = array(), array $values = array())
    {
        $this->keys = $keys;
        $this->values = $values;
    }

    public function set(Peripheral $key, $value)
    {
        $keys = $this->keys;
        $values = $this->values;

        $index = array_search($key, $this->keys, true);

        if ($index === false) {
            $index = count($keys);
        }

        $keys[$index] = $key;
        $values[$index] = $value;

        return new self(
            $keys,
            $values
        );
    }

    public function get(Peripheral $key)
    {
        $index = array_search($key, $this->keys, true);

        if ($index === false) {
            throw new \InvalidArgumentException(sprintf('Peripheral not found'));
        }

        return $this->values[$index];
    }
}
