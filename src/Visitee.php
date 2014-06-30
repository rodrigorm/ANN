<?php

namespace Ann;

use \Ann\Visitor;

interface Visitee
{
    public function accept(Visitor $visitor);
}
