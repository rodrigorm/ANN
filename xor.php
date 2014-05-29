<?php

require 'vendor/autoload.php';

use \Ann\Network,
    \Ann\Neuron,
    \Ann\Dendrite,
    \Ann\Synapse,
    \Ann\Peripheral,
    \Ann\Input,
    \Ann\Trainer,
    \Ann\OutputFunction\Linear,
    \Ann\OutputFunction\Sigmoid,
    \Ann\OutputFunction\Threshold;

$neuronA = new Neuron(
    new Peripheral(),
    new Linear()
);

$neuronB = new Neuron(
    new Peripheral(),
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

$network = new Network(array($neuronA, $neuronB), array($output));
$trainer = new Trainer();

$data = array(
    array(0.0, 0.0, 0.0),
    array(0.0, 1.0, 1.0),
    array(1.0, 0.0, 1.0),
    array(1.0, 1.0, 0.0)
);

// Train
$train = 0;
$iterations = 110;

while ($train++ < $iterations) {
    echo "\r", 'Train: ', $train;
    $factor = $train / $iterations;

    foreach ($data as $tuple) {
        $input = array($tuple[0], $tuple[1]);
        $network = $network->train($trainer, $input, array($tuple[2]), $factor);
    }
}
echo "\n";

foreach ($data  as $tuple) {
    $input = array($tuple[0], $tuple[1]);
    $response = $network->calculate($input);
    echo $tuple[0], ' XOR ', $tuple[1], ' = ', $tuple[2], ', output = ', $response[0],', error = ', abs($tuple[2] - $response[0]), "\n";
}
