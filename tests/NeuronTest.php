<?php

require 'vendor/autoload.php';

use \Ann\Neuron;
use \Ann\Dendrite;
use \Ann\Synapse;
use \Ann\Peripheral;
use \Ann\Input;
use \Ann\BackPropagation;
use \Ann\OutputFunction\Linear;

class NeuronTest extends PHPUnit_Framework_TestCase
{
    public function testSingleNetwork()
    {
        $data = new Input();

        $input = new Peripheral();
        $output = new Neuron(
            new Dendrite(
                array(
                    new Synapse(
                        new Neuron(
                            $input,
                            new Linear()
                        ),
                        1.0
                    )
                )
            ),
            new Linear()
        );

        $data = $data->set($input, 1.0);

        $this->assertEquals(1.0, $output->output($data));
    }
}

