<?php

namespace Ann;

use \Ann\Neuron;
use \Ann\Dendrite;
use \Ann\Synapse;
use \Ann\Peripheral;
use \Ann\Input;
use \Ann\BackPropagation;
use \Ann\OutputFunction\Linear;
use \Ann\Delta;
use \Ann\Trainset;
use \Ann\Activation;
use \Ann\Output;
use \Ann\Network;
use \Ann\DeltaBuilder;

class BackPropagationTest extends \PHPUnit_Framework_TestCase
{
    public function testOneInputOneOutputNetwork()
    {
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
        $network = new Network(array($input), array($output));

        $data = new Input();
        $data = $data->set($input, 1.0);

        $response = new Output();
        $response = $response->set($output, 0.0);

        $activation = new Activation($data, new Output());
        $activation = $output->output($activation);

        $trainset = new Trainset($activation, $response);

        $builder = new DeltaBuilder();
        $delta = $network->accept($builder)->build($trainset);

        $teacher = new BackPropagation($delta, $trainset, 1.0);
        $result = $teacher->teach($network);

        $expected = new Network(
            array(
                new Peripheral()
            ),
            array(
                new Neuron(
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
                )
            )
        );
        $this->assertEquals($expected, $result);
    }

    public function testTwoInputsAndOneOutputNetwork()
    {
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
        $network = new Network(array($input1, $input2), array($output));

        $data = new Input();
        $data = $data->set($input1, 1.0);
        $data = $data->set($input2, 1.0);

        $response = new Output();
        $response = $response->set($output, 1.0);

        $activation = new Activation($data, new Output());
        $activation = $output->output($activation);

        $trainset = new Trainset($activation, $response);

        $builder = new DeltaBuilder();
        $delta = $network->accept($builder)->build($trainset);

        $teacher = new BackPropagation($delta, $trainset, 1.0);
        $result = $teacher->teach($network);

        $expected = new Network(
            array(
                new Peripheral(),
                new Peripheral()
            ),
            array(
                new Neuron(
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
                )
            )
        );
        $this->assertEquals($expected, $result);
    }
}
