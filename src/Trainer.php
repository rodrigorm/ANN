<?php

namespace Ann;

use \Ann\Network;
use \Ann\BackPropagation;
use \Ann\Trainset;

class Trainer
{
    public function train(Network $network, Trainset $trainset, $factor)
    {
        $delta = $this->buildDelta($network, $trainset);
        $teacher = new BackPropagation($delta, $trainset, $factor);
        return $teacher->teach($network);
    }

    private function buildDelta(Network $network, Trainset $trainset)
    {
        $builder = new DeltaBuilder();
        return $network->accept($builder)->build($trainset);
    }
}
