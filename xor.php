<?php

require 'vendor/autoload.php';

use \Ann\Neuron,
    \Ann\Dendrite,
    \Ann\Synapse,
    \Ann\Peripheral,
    \Ann\Input,
    \Ann\Trainer,
    \Ann\OutputFunction\Linear,
    \Ann\OutputFunction\Sigmoid,
    \Ann\OutputFunction\Threshold;

$a = new Peripheral();
$b = new Peripheral();

$neuronA = new Neuron(
    $a,
    new Linear()
);

$neuronB = new Neuron(
    $b,
    new Linear()
);

$output = new Neuron(
    new Dendrite(
        array(
            new Synapse(
                new Neuron(
                    new Dendrite(
                        array(
                            new Synapse(
                                $neuronA,
                                1.0
                            )
                        )
                    ),
                    new Threshold()
                ),
                1.0
            ),
            new Synapse(
                new Neuron(
                    new Dendrite(
                        array(
                            new Synapse(
                                $neuronA,
                                1.0
                            ),
                            new Synapse(
                                $neuronB,
                                1.0
                            )
                        )
                    ),
                    new Threshold(2.0)
                ),
                -1.0
            ),
            new Synapse(
                new Neuron(
                    new Dendrite(
                        array(
                            new Synapse(
                                $neuronB,
                                1.0
                            )
                        )
                    ),
                    new Threshold()
                ),
                1.0
            ),
        )
    ),
    new Linear()
);

$input = new Input();
$trainer = new Trainer();

$data = array(
    array(0.0, 0.0, 0.0),
    array(0.0, 1.0, 1.0),
    array(1.0, 0.0, 1.0),
    array(1.0, 1.0, 0.0)
);

// Train
$train = 0;

while ($train++ < 50) {
    echo "\r", 'Train: ', $train;
    foreach ($data as $tuple) {
        $input = $input->set($a, $tuple[0]);
        $input = $input->set($b, $tuple[1]);
        $output = $trainer->train($output, $input, $tuple[2]);
    }
}
echo "\n";

foreach ($data  as $tuple) {
    $input = $input->set($a, $tuple[0]);
    $input = $input->set($b, $tuple[1]);

    echo $tuple[0], ' XOR ', $tuple[1], ' = ', $tuple[2], ', output = ', $output->output($input),', error = ', abs($tuple[2] - $output->output($input)), "\n";
}
