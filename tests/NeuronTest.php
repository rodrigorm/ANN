<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Dendrite;
use \Ann\Synapse;
use \Ann\Peripheral;
use \Ann\Input;
use \Ann\BackPropagation;
use \Ann\OutputFunction\Linear;

class NeuronTest extends \PHPUnit_Framework_TestCase
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

        $activation = new Activation($data, new Output());
        $result = $output->output($activation);
        $this->assertEquals(1.0, $result->output($output));
    }
}
