<?php

require 'vendor/autoload.php';

use \Ann\Neuron;
use \Ann\Dendrite;
use \Ann\Synapse;
use \Ann\Peripheral;
use \Ann\Input;
use \Ann\BackPropagation;
use \Ann\OutputFunction\Linear;

class BackPropagationTest extends PHPUnit_Framework_TestCase
{
    public function testOneInputOneOutputNetwork()
    {
        $teacher = new BackPropagation();
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
        $result = $teacher->teach($output, $data, -1.0);

        $expected = new Neuron(
            new Dendrite(
                array(
                    new Synapse(
                        new Neuron(
                            $input,
                            new Linear()
                        ),
                        0.0
                    )
                )
            ),
            new Linear()
        );
        $this->assertEquals($expected, $result);
    }

    public function testTwoInputsAndOneOutputNetwork()
    {
        $teacher = new BackPropagation();
        $data = new Input();

        $input1 = new Peripheral();
        $input2 = new Peripheral();
        $output = new Neuron(
            new Dendrite(
                array(
                    new Synapse(
                        new Neuron(
                            $input1,
                            new Linear()
                        ),
                        1.0
                    ),
                    new Synapse(
                        new Neuron(
                            $input2,
                            new Linear()
                        ),
                        1.0
                    )
                )
            ),
            new Linear()
        );

        $data = $data->set($input1, 1.0);
        $data = $data->set($input2, 1.0);
        $result = $teacher->teach($output, $data, -1.0);

        $expected = new Neuron(
            new Dendrite(
                array(
                    new Synapse(
                        new Neuron(
                            $input1,
                            new Linear()
                        ),
                        0.0
                    ),
                    new Synapse(
                        new Neuron(
                            $input1,
                            new Linear()
                        ),
                        0.0
                    )
                )
            ),
            new Linear()
        );
        $this->assertEquals($expected, $result);
    }
}
