<?php

namespace Ann;

use \Ann\Neuron;
use \SplObjectStorage;

class Output
{
    private $storage;

    public function __construct(SplObjectStorage $storage = null)
    {
        $this->storage = $storage ? $storage : new SplObjectStorage();
    }

    public function set(Neuron $key, $value)
    {
        $storage = clone $this->storage;
        $storage->attach($key, $value);
        return new self($storage);
    }

    public function get(Neuron $key)
    {
        return $this->storage[$key];
    }
}

