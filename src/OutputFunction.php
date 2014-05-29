<?php

namespace Ann;

interface OutputFunction
{
    public function forward($value);
    public function derivative($value);
}
