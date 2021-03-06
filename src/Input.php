<?php

namespace Ann;

use \Ann\Peripheral;
use \SplObjectStorage;

class Input
{
    private $storage;

    public function __construct(SplObjectStorage $storage = null)
    {
        $this->storage = $storage ? $storage : new SplObjectStorage();
    }

    public function set(Peripheral $key, $value)
    {
        $storage = clone $this->storage;
        $storage->attach($key, $value);
        return new self($storage);
    }

    public function get(Peripheral $key)
    {
        return $this->storage[$key];
    }
}
