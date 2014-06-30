<?php

namespace Ann;

use \SplObjectStorage;

class Output
{
    private $storage;

    public function __construct(SplObjectStorage $storage = null)
    {
        $this->storage = $storage ? $storage : new SplObjectStorage();
    }

    public function set($key, $value)
    {
        $storage = clone $this->storage;
        $storage->attach($key, $value);
        return new self($storage);
    }

    public function get($key)
    {
        return $this->storage[$key];
    }

    public function toArray()
    {
        $result = array();

        foreach ($this->storage as $key) {
            $result[] = $this->storage[$key];
        }

        return $result;
    }

    public function contains($key)
    {
        return $this->storage->contains($key);
    }
}

