<?php

require 'vendor/autoload.php';
require 'utils.php';

use \Ann\Network,
    \Ann\Trainer;

$network = Network::create(array(2, 3, 1));
$trainer = new Trainer();

$data = array(
    array(0.0, 0.0, 0.0),
    array(0.0, 1.0, 1.0),
    array(1.0, 0.0, 1.0),
    array(1.0, 1.0, 0.0),
);

// Train
$train = 0;
$iterations = 6000;

while ($train++ < $iterations) {
    echo "\r", 'Train: ', $train, '/', $iterations;
    $factor = $train / $iterations;

    foreach ($data as $tuple) {
        $input = array($tuple[0], $tuple[1]);
        $network = $network->train($trainer, $input, array($tuple[2]), $factor);
    }
}
echo "\n";

foreach ($data  as $tuple) {
    $input = array($tuple[0], $tuple[1]);
    $response = $network->calculate($input)->toArray();
    echo $tuple[0], ' XOR ', $tuple[1], ' = ', $tuple[2], ', output = ', $response[0],', error = ', abs($tuple[2] - $response[0]), "\n";
}
