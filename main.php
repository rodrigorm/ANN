<?php

require 'vendor/autoload.php';

use \Ann\Neuron,
    \Ann\Dendrite,
    \Ann\Synapse,
    \Ann\Peripheral,
    \Ann\Input,
    \Ann\State,
    \Ann\OutputFunction\Linear,
    \Ann\OutputFunction\Threshold;

$a = new State('a');
$b = new State('b');

$output = new Neuron(
    new Dendrite(
        array(
            new Synapse(
                new Neuron(
                    new Peripheral($a),
                    new Linear()
                ),
                0.3
            ),
            new Synapse(
                new Neuron(
                    new Peripheral($b),
                    new Linear()
                ),
                0.3
            )
        )
    ),
    new Threshold(1.0)
);

$expected = 1.0;
$epoch = 0;
$input = new Input();
$input = $input->set($a, 1.0);
$input = $input->set($b, 1.0);

while ($epoch++ <= 10) {
    $error = $expected - $output->output($input);
    echo 'Epoch ', $epoch, ': ', $output->output($input), "\t", ' (Error: ', $error, ')', "\n";
    $output = $output->learn($error, $input);
}
