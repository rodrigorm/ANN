<?php

require 'vendor/autoload.php';

use \Ann\Neuron,
    \Ann\Dendrite,
    \Ann\Synapse,
    \Ann\Peripheral,
    \Ann\Input,
    \Ann\Trainer,
    \Ann\OutputFunction\Linear,
    \Ann\OutputFunction\Threshold;

$a = new Peripheral();
$b = new Peripheral();

$output = new Neuron(
    new Dendrite(
        array(
            new Synapse(
                new Neuron(
                    $a,
                    new Linear()
                ),
                rand(0, 100) / 50.0
            ),
            new Synapse(
                new Neuron(
                    $b,
                    new Linear()
                ),
                rand(0, 100) / 50.0
            )
        )
    ),
    new Linear()
);

$input = new Input();
$input = $input->set($a, 1.0);
$input = $input->set($b, 1.0);
$trainer = new Trainer();

$target = 1.0;
$epoch = 0;
$iterations = 30;

while ($epoch++ < $iterations) {
    $factor = $epoch / $iterations;
    $error = $target - $output->output($input);
    echo 'Epoch ', $epoch, ': ', $output->output($input), "\t", ' (Error: ', $error, ')', "\n";
    $output = $trainer->train($output, $input, $target, $factor);
}
