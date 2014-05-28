<?php

require 'vendor/autoload.php';

use \Ann\Neuron,
    \Ann\Dendrite,
    \Ann\Synapse,
    \Ann\Peripheral,
    \Ann\Input,
    \Ann\State,
    \Ann\OutputFunction\Linear,
    \Ann\OutputFunction\Sigmoid;

$a = new State('a');
$b = new State('b');

$neuronA = new Neuron(
    new Peripheral($a),
    new Linear()
);

$neuronB = new Neuron(
    new Peripheral($b),
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
                            ),
                            new Synapse(
                                $neuronB,
                                1.0
                            )
                        )
                    ),
                    new Sigmoid()
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
                    new Sigmoid()
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
                    new Sigmoid()
                ),
                1.0
            )
        )
    ),
    new Linear()
);

$input = new Input();

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
        $expected = $tuple[2];
        $delta = $expected - $output->output($input);
        $error = $delta * $delta;
        $output = $output->learn($error, $input);
    }
}
echo "\n";

$epoch = 0;
while ($epoch++ < 10) {
    shuffle($data);
    $tuple = $data[0];

    $input = $input->set($a, $tuple[0]);
    $input = $input->set($b, $tuple[1]);

    echo 'a = ', $tuple[0], ', b = ', $tuple[1], ', output = ', $output->output($input), "\n";
}
